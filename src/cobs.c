#include "cobs.h"

#include "memory.h"
#include "stdio.h"

// declaration
postcard_return_t cobs_encoder_insert_zero(struct cobs_encoder *cobs_encoder);

// ============================= Encoder ================================
// assign buffer and length
void cobs_encoder_init(struct cobs_encoder *cobs_encoder, uint8_t *buf,
                       uint32_t size) {
  cobs_encoder->buf = buf;
  cobs_encoder->next = buf;
  cobs_encoder->end = buf + size;
  cobs_encoder->zero = 0;
}

void cobs_encoder_reset(struct cobs_encoder *cobs_encoder) {
  cobs_encoder->next = cobs_encoder->buf;
  cobs_encoder->zero = 0;
}

// Inserts the framing 0 and the first marker byte
void cobs_encoder_start_frame(struct cobs_encoder *cobs_encoder) {
  // marker zero
  *(cobs_encoder->next) = 0;
  cobs_encoder->next++;
  cobs_encoder->zero = 1;
}

postcard_return_t cobs_encoder_end_frame(struct cobs_encoder *cobs_encoder) {
  return cobs_encoder_insert_zero(cobs_encoder);
}

postcard_return_t cobs_encoder_frame(struct cobs_encoder *cobs_encoder,
                                     uint8_t *buf, uint32_t size,
                                     uint32_t *written) {
  cobs_encoder_start_frame(cobs_encoder);
  postcard_return_t result = cobs_encoder_write_bytes(cobs_encoder, buf, size);
  if (result != POSTCARD_SUCCESS) {
    *written = cobs_encoder->next - cobs_encoder->buf;
    return result;
  }
  result = cobs_encoder_end_frame(cobs_encoder);
  *written = cobs_encoder->next - cobs_encoder->buf;
  return result;
}

postcard_return_t cobs_encoder_write_byte(struct cobs_encoder *cobs_encoder,
                                          uint8_t byte) {
  // check for buffer overflow
  if (cobs_encoder->next >= cobs_encoder->end) {
    return POSTCARD_COBS_ENCODE_OVERFLOW;
  }
  // if been no 0 for 255 bytes, insert byte and reset counter
  if (cobs_encoder->zero == 255) {
    cobs_encoder_insert_zero(cobs_encoder);
    if (cobs_encoder->next >= cobs_encoder->end) {
      return POSTCARD_COBS_ENCODE_OVERFLOW;
    }
  }

  // If byte is zero, insert marker
  if (byte == 0) {
    return cobs_encoder_insert_zero(cobs_encoder);
  } else {
    // otherwise insert byte
    *(cobs_encoder->next) = byte;
    cobs_encoder->next++;
    cobs_encoder->zero++;
    return POSTCARD_SUCCESS;
  }
}

void cobs_encoder_write_byte_unchecked(struct cobs_encoder *cobs_encoder,
                                       uint8_t byte) {
  // if been no 0 for 255 bytes, insert byte and reset counter
  if (cobs_encoder->zero == 255) {
    cobs_encoder_insert_zero(cobs_encoder);
  }

  // If byte is zero, insert marker
  if (byte == 0) {
    cobs_encoder_insert_zero(cobs_encoder);
  } else {
    // otherwise insert byte
    *(cobs_encoder->next) = byte;
    cobs_encoder->next++;
    cobs_encoder->zero++;
  }
}

void cobs_encoder_write_byte_unchecked_no_overhead(
    struct cobs_encoder *cobs_encoder, uint8_t byte) {
  // If byte is zero, insert marker
  if (byte == 0) {
    cobs_encoder_insert_zero(cobs_encoder);
  } else {
    // otherwise insert byte
    *(cobs_encoder->next) = byte;
    cobs_encoder->next++;
    cobs_encoder->zero++;
  }
}

// Write an array of bytes to the buffer with cobs encoding
postcard_return_t cobs_encoder_write_bytes(struct cobs_encoder *cobs_encoder,
                                           uint8_t *bytes, uint32_t size) {
  // calc max size of encoded bytes
  // size + 1 for possible overhead byte + 1 for each 256 bytes in data
  uint32_t max_bytes = size + 1 + (size >> 8);
  uint32_t space_left = cobs_encoder->end - cobs_encoder->next;
  // printf("size: %d, max: %d, left: %d\n", size, max_bytes, space_left);
  // check if enough space in buffer
  if (space_left >= max_bytes) {
    // can used unchecked write
    if (max_bytes <= (255 - cobs_encoder->zero)) {
      // dont need to insert any overhead bytes
      for (uint32_t i = 0; i < size; i++) {
        cobs_encoder_write_byte_unchecked_no_overhead(cobs_encoder, bytes[i]);
      }
      return POSTCARD_SUCCESS;
    } else {
      for (uint32_t i = 0; i < size; i++) {
        cobs_encoder_write_byte_unchecked(cobs_encoder, bytes[i]);
      }
      return POSTCARD_SUCCESS;
    }
  } else {
    return POSTCARD_COBS_ENCODE_OVERFLOW;
  }
}

postcard_return_t cobs_encoder_insert_zero(struct cobs_encoder *cobs_encoder) {
  // Go back and set marker
  *(cobs_encoder->next - cobs_encoder->zero) = cobs_encoder->zero;
  // Add a byte
  *(cobs_encoder->next) = 0;
  cobs_encoder->next++;
  cobs_encoder->zero = 1;
  return POSTCARD_SUCCESS;
}

// ============================== Decoder ===============================
// Helper functions
postcard_return_t cobs_decoder_check_next(struct cobs_decoder *cobs_decoder) {
  if (cobs_decoder->next == cobs_decoder->end) {
    // wrap around
    cobs_decoder->next = cobs_decoder->buf;
  }
  if (cobs_decoder->next == cobs_decoder->data_end) {
    return POSTCARD_COBS_DECODE_DATA_END;
  } else
    return POSTCARD_SUCCESS;
}

// assign buffer and length
postcard_return_t cobs_decoder_init(struct cobs_decoder *cobs_decoder,
                                    uint8_t *buf, uint32_t size,
                                    uint32_t data_size) {
  cobs_decoder->buf = buf;
  cobs_decoder->next = buf;
  cobs_decoder->end = buf + size;
  cobs_decoder->data_end = buf;
  cobs_decoder->frame_start = 0;
  cobs_decoder->frame_end = 0;
  cobs_decoder->zero = 0;
  cobs_decoder->overhead = false;
  cobs_decoder->full = false;
  cobs_decoder->partial_decode = false;
  return cobs_decoder_data_written_circular(cobs_decoder, data_size);
}

void cobs_decoder_reset(struct cobs_decoder *cobs_decoder) {
  cobs_decoder->next = cobs_decoder->buf;
  cobs_decoder->data_end = cobs_decoder->buf;
  cobs_decoder->frame_start = 0;
  cobs_decoder->frame_end = 0;
  cobs_decoder->zero = 0;
  cobs_decoder->overhead = false;
  cobs_decoder->full = false;
  cobs_decoder->partial_decode = false;
}

void cobs_decoder_reset_circular(struct cobs_decoder *cobs_decoder) {
  cobs_decoder->next = cobs_decoder->buf;
  cobs_decoder->full = false;
  cobs_decoder->data_end = cobs_decoder->buf;
  cobs_decoder->frame_start = cobs_decoder->end;
  cobs_decoder->frame_end = cobs_decoder->end;
  cobs_decoder->zero = 0;
  cobs_decoder->partial_decode = false;
}

bool cobs_decoder_go_to_zero(struct cobs_decoder *cobs_decoder) {
  while (cobs_decoder->next != cobs_decoder->data_end) {
    if (*(cobs_decoder->next++) == 0) {
      return true;
    }
  }
  return false;
}

uint32_t cobs_decoder_get_data_ptr(struct cobs_decoder *cobs_decoder,
                                   uint8_t **ptr) {
  *ptr = cobs_decoder->data_end;
  return cobs_decoder->end - cobs_decoder->data_end;
}

postcard_return_t cobs_decoder_data_written(struct cobs_decoder *cobs_decoder,
                                            uint32_t size) {
  uint8_t *end = cobs_decoder->data_end + size;
  if (end > cobs_decoder->end) {
    // too much data written to buffer
    return POSTCARD_COBS_DECODE_WRITTEN_OVERFLOW;
  } else {
    cobs_decoder->data_end = end;
    return POSTCARD_SUCCESS;
  }
}

postcard_return_t cobs_decoder_start_frame(struct cobs_decoder *cobs_decoder) {
  // check if next is not pointing to data end or buffer end
  if (cobs_decoder->next == cobs_decoder->end) {
    return POSTCARD_COBS_DECODE_BUFFER_END;
  } else if (cobs_decoder->next == cobs_decoder->data_end) {
    return POSTCARD_COBS_DECODE_DATA_END;
  }
  uint8_t byte = *(cobs_decoder->next);
  if (byte == 0) {
    return POSTCARD_COBS_DECODE_LEADING_ZERO;
  }
  // First byte marks position of next zero
  cobs_decoder->zero = byte;
  cobs_decoder->next++;
  cobs_decoder->frame_start = cobs_decoder->next;
  cobs_decoder->overhead = cobs_decoder->zero == 0xFF;
  cobs_decoder->partial_decode = true;
  return POSTCARD_SUCCESS;
}

postcard_return_t cobs_decoder_end_frame(struct cobs_decoder *cobs_decoder) {
  cobs_decoder->partial_decode = false;
  if (cobs_decoder->zero == 0) {
    // mark frame end
    cobs_decoder->frame_end = cobs_decoder->next;
    // go to first byte of next frame
    cobs_decoder->next++;
    cobs_decoder->zero = 0;

    return POSTCARD_SUCCESS;
  } else {
    return POSTCARD_COBS_DECODE_INVALID_ZERO;
  }
}

postcard_return_t cobs_decoder_decode_byte_in_place_short(
    struct cobs_decoder *cobs_decoder) {
  if (cobs_decoder->next == cobs_decoder->end) {
    return POSTCARD_COBS_DECODE_BUFFER_END;
  } else if (cobs_decoder->next == cobs_decoder->data_end) {
    return POSTCARD_COBS_DECODE_DATA_END;
  }
  cobs_decoder->zero--;
  if (*(cobs_decoder->next) == 0) {
    return POSTCARD_COBS_EOF;
  }

  if (cobs_decoder->zero == 0) {
    // This byte is a marker
    cobs_decoder->zero = *(cobs_decoder->next);
    *(cobs_decoder->next) = 0;
  }
  // otherwise leave byte as is
  cobs_decoder->next++;
  return POSTCARD_SUCCESS;
}

postcard_return_t cobs_decoder_decode_bytes_in_place_short(
    struct cobs_decoder *cobs_decoder) {
  // check how many bytes can be decoded
  uint32_t count = cobs_decoder->data_end - cobs_decoder->next;
  if (count == 0) {
    if (cobs_decoder->next == cobs_decoder->end) {
      return POSTCARD_COBS_DECODE_BUFFER_END;
    } else {
      return POSTCARD_COBS_DECODE_DATA_END;
    }
  }
  // decode all remaining bytes
  for (uint32_t i = 0; i < count; i++) {
    cobs_decoder->zero--;
    if (*(cobs_decoder->next) == 0) {
      return POSTCARD_COBS_EOF;
    }

    if (cobs_decoder->zero == 0) {
      // This byte is a marker
      cobs_decoder->zero = *(cobs_decoder->next);
      *(cobs_decoder->next) = 0;
    }
    // otherwise leave byte as is
    cobs_decoder->next++;
  }
  return POSTCARD_COBS_DECODE_DATA_END;
}

postcard_return_t cobs_decoder_frame_in_place_short(
    struct cobs_decoder *cobs_decoder) {
  if (!cobs_decoder->partial_decode) {
    postcard_return_t result = cobs_decoder_start_frame(cobs_decoder);
    if (result != POSTCARD_SUCCESS) {
      return result;
    }
  }
  // try to decode up to the end of data
  postcard_return_t result =
      cobs_decoder_decode_bytes_in_place_short(cobs_decoder);
  // returns early when 0 is reached
  if (result == POSTCARD_COBS_EOF) {
    // try to end frame
    return cobs_decoder_end_frame(cobs_decoder);
  } else {
    return result;
  }
}

bool cobs_decoder_pending_frame(struct cobs_decoder *cobs_decoder) {
  return cobs_decoder->frame_start != 0 && cobs_decoder->frame_end != 0;
}

void cobs_decoder_frame_ptrs(struct cobs_decoder *cobs_decoder, uint8_t **start,
                             uint8_t **end) {
  *start = cobs_decoder->frame_start;
  *end = cobs_decoder->frame_end;
  cobs_decoder->frame_start = 0;
  cobs_decoder->frame_end = 0;
}

uint32_t cobs_decoder_shift_data(struct cobs_decoder *cobs_decoder) {
  uint8_t *start;
  if (cobs_decoder->frame_start != 0) {
    // frame start is the oldest valid data (because a frame start has
    // successfully been called)
    start = cobs_decoder->frame_start;
  } else {
    // no active frame decode in process, next is first valid data
    start = cobs_decoder->next;
  };
  // number of bytes to shift
  uint32_t size = start - cobs_decoder->buf;
  memcpy(cobs_decoder->buf, start, size);
  // update pointers
  cobs_decoder->next -= size;
  cobs_decoder->data_end -= size;
  if (cobs_decoder->frame_start != 0) {
    cobs_decoder->frame_start -= size;
  }
  if (cobs_decoder->frame_end != 0) {
    cobs_decoder->frame_end -= size;
  }
  return size;
}

// ============================== Circular ====================================

uint32_t cobs_decoder_get_data_ptr_circular(struct cobs_decoder *cobs_decoder,
                                            uint8_t **ptr) {
  // start of where data can be placed
  *ptr = cobs_decoder->data_end;
  // get next blocker
  uint8_t *end = cobs_decoder->end - 1;
  if (cobs_decoder->next >= *ptr) {
    end = cobs_decoder->next;
  }
  if (cobs_decoder->frame_start < end && cobs_decoder->frame_start >= *ptr) {
    end = cobs_decoder->frame_start;
  }
  return end - *ptr;
}

postcard_return_t cobs_decoder_data_written_circular(
    struct cobs_decoder *cobs_decoder, uint32_t size) {
  uint8_t *data_end = cobs_decoder->data_end;
  // check if size is bigger than buffer
  if (size > cobs_decoder->end - cobs_decoder->buf) {
    return POSTCARD_COBS_DECODE_WRITTEN_OVERFLOW;
  }
  data_end += size;
  if (cobs_decoder->frame_start < cobs_decoder->end &&
      cobs_decoder->frame_start > cobs_decoder->data_end &&
      data_end > cobs_decoder->frame_start) {
    return POSTCARD_COBS_DECODE_FRAME_OVERFLOW;
  }

  if (cobs_decoder->next > cobs_decoder->data_end &&
      data_end > cobs_decoder->next) {
    return POSTCARD_COBS_DECODE_DATA_OVERFLOW;
  }

  // Check if fits in before end of buffer
  if (data_end < cobs_decoder->end) {
    cobs_decoder->data_end = data_end;
    return POSTCARD_SUCCESS;
  } else {
    // must wrap around to start
    data_end = cobs_decoder->buf + (data_end - cobs_decoder->end);
    // check for frame overwrite
    if (data_end >= cobs_decoder->frame_start) {
      return POSTCARD_COBS_DECODE_FRAME_OVERFLOW;
      // check for data overwrite
    } else if (data_end >= cobs_decoder->next) {
      return POSTCARD_COBS_DECODE_DATA_OVERFLOW;
    } else {
      cobs_decoder->data_end = data_end;
      return POSTCARD_SUCCESS;
    }
  }
}

postcard_return_t cobs_decoder_start_frame_circular(
    struct cobs_decoder *cobs_decoder) {
  // chech if at data end and perform wrap around
  postcard_return_t result = cobs_decoder_check_next(cobs_decoder);
  if (result != POSTCARD_SUCCESS) {
    // printf("No start frame\n");
    return result;
  }
  uint8_t byte = *(cobs_decoder->next);
  if (byte == 0) {
    return POSTCARD_COBS_DECODE_LEADING_ZERO;
  }
  // First byte marks position of next zero
  cobs_decoder->zero = byte;
  cobs_decoder->next++;
  cobs_decoder->overhead = cobs_decoder->zero == 0xFF;
  cobs_decoder->partial_decode = true;
  // printf("Frame start\n");
  return POSTCARD_SUCCESS;
}

// Checks that end of frame zero is as expected
postcard_return_t cobs_decoder_end_frame_circular(
    struct cobs_decoder *cobs_decoder) {
  cobs_decoder->partial_decode = false;
  if (cobs_decoder->zero == 0) {
    cobs_decoder->next++;
    cobs_decoder->zero = 0;
    return POSTCARD_SUCCESS;
  } else {
    return POSTCARD_COBS_DECODE_INVALID_ZERO;
  }
}

postcard_return_t cobs_decoder_read_byte_circular(
    struct cobs_decoder *cobs_decoder, uint8_t *value) {
  // check if at data end and perform wrap around
  postcard_return_t result = cobs_decoder_check_next(cobs_decoder);
  if (result != POSTCARD_SUCCESS) {
    return result;
  }
  // decrement next zero counter
  cobs_decoder->zero--;
  // check if end of cobs_decoder frame
  if (*(cobs_decoder->next) == 0) {
    return POSTCARD_COBS_EOF;
  }

  if (cobs_decoder->zero == 0) {
    // This byte is a marker
    cobs_decoder->zero = *(cobs_decoder->next);
    // if previous marker was 0xFF, this is an overhead byte
    if (cobs_decoder->overhead) {
      cobs_decoder->overhead = cobs_decoder->zero == 0xFF;
      cobs_decoder->next++;
      return cobs_decoder_read_byte_circular(cobs_decoder, value);
    } else {
      cobs_decoder->overhead = cobs_decoder->zero == 0xFF;
      *value = 0;
    }
  } else {
    *value = *(cobs_decoder->next);
  }
  cobs_decoder->next++;
  return POSTCARD_SUCCESS;
}

postcard_return_t cobs_decoder_read_bytes_circular(
    struct cobs_decoder *cobs_decoder, uint8_t *buf, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    postcard_return_t result =
        cobs_decoder_read_byte_circular(cobs_decoder, buf + i);
    if (result != POSTCARD_SUCCESS) {
      return result;
    }
  }
  return POSTCARD_SUCCESS;
}

postcard_return_t cobs_decoder_frame_circular(struct cobs_decoder *cobs_decoder,
                                              uint8_t *buf, uint32_t size,
                                              uint32_t *written) {
  uint8_t *buf_ptr = buf;
  uint8_t *end = buf + size;
  if (!cobs_decoder->partial_decode) {
    postcard_return_t result = cobs_decoder_start_frame_circular(cobs_decoder);
    if (result == POSTCARD_COBS_DECODE_LEADING_ZERO ||
        result == POSTCARD_COBS_DECODE_DATA_END) {
      *written = 0;
      return result;
    }
  }
  while (true) {
    postcard_return_t result =
        cobs_decoder_read_byte_circular(cobs_decoder, buf_ptr++);
    if (result != POSTCARD_SUCCESS) {
      *written = buf_ptr - buf - 1;
      if (result == POSTCARD_COBS_EOF) {
        return cobs_decoder_end_frame_circular(cobs_decoder);
      } else if (result == POSTCARD_COBS_DECODE_DATA_END) {
        return POSTCARD_COBS_DECODE_DATA_END;
      }
    } else if (buf_ptr >= end) {
      *written = buf_ptr - buf;
      return POSTCARD_COBS_DECODE_OVERFLOW;
    }
  }
}

postcard_return_t cobs_decoder_frame_in_place_circular(
    struct cobs_decoder *cobs_decoder, uint32_t *written) {
  if (!cobs_decoder->partial_decode) {
    postcard_return_t result = cobs_decoder_start_frame_circular(cobs_decoder);
    if (result == POSTCARD_COBS_DECODE_LEADING_ZERO ||
        result == POSTCARD_COBS_DECODE_DATA_END) {
      return result;
    } else {
      // frame decode has started
      if (cobs_decoder->next != cobs_decoder->end) {
        cobs_decoder->frame_start = cobs_decoder->next;
      } else {
        cobs_decoder->frame_start = cobs_decoder->buf;
      }
      cobs_decoder->frame_end = cobs_decoder->frame_start;
    }
  }
  *written = 0;
  while (true) {
    if (cobs_decoder->frame_end == cobs_decoder->end) {
      cobs_decoder->frame_end = cobs_decoder->buf;
    }
    postcard_return_t result = cobs_decoder_read_byte_circular(
        cobs_decoder, cobs_decoder->frame_end++);

    if (result != POSTCARD_SUCCESS) {
      cobs_decoder->frame_end--;
      if (result == POSTCARD_COBS_EOF) {
        return cobs_decoder_end_frame_circular(cobs_decoder);
      } else {
        return result;
      }
    } else {
      (*written)++;
    }
  }
}

uint32_t cobs_decoder_place_bytes_circular(struct cobs_decoder *cobs_decoder,
                                           uint8_t *buf, uint32_t size) {
  if (cobs_decoder->full) {
    return 0;
  }
  uint32_t written;
  for (written = 0; written < size; written++) {
    *(cobs_decoder->data_end++) = buf[written];
    // check if at end of buffer
    if (cobs_decoder->data_end == cobs_decoder->end) {
      cobs_decoder->data_end = cobs_decoder->buf;
    }
    // check if wrapped around to data start
    if (cobs_decoder->data_end == cobs_decoder->next) {
      cobs_decoder->full = true;
      break;
    }
    // check if at frame start for decode in place operations
    if (cobs_decoder->data_end == cobs_decoder->frame_start) {
      cobs_decoder->full = true;
      break;
    }
  }
  return written;
}

uint32_t cobs_decoder_fetch_frame_circular(struct cobs_decoder *cobs_decoder,
                                           uint8_t *buf, uint32_t size) {
  uint32_t count = 0;
  while (cobs_decoder->frame_start != cobs_decoder->frame_end) {
    *(buf++) = *(cobs_decoder->frame_start++);
    if (cobs_decoder->frame_start == cobs_decoder->end) {
      cobs_decoder->frame_start = cobs_decoder->buf;
    }
    count++;
  }
  return count;
}