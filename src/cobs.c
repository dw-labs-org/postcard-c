#include "cobs.h"

#include "stdio.h"

// declration
postcard_return_t cobs_insert_zero(struct cobs *cobs);

// assign buffer and length
void cobs_init(struct cobs *cobs, uint8_t *buf, uint32_t length) {
  cobs->buf = buf;
  cobs->next = buf;
  cobs->end = buf + length;
  cobs->zero = 0;
  cobs->overhead = false;
}

void cobs_reset(struct cobs *cobs) {
  cobs->next = cobs->buf;
  cobs->zero = 0;
}

// Inserts the framing 0 and the first marker byte
void cobs_encode_start_frame(struct cobs *cobs) {
  // marker zero
  *(cobs->next) = 0;
  cobs->next++;
  cobs->zero = 1;
}
postcard_return_t cobs_encode_end_frame(struct cobs *cobs) {
  return cobs_insert_zero(cobs);
}

postcard_return_t cobs_encode_frame(struct cobs *cobs, uint8_t *buf,
                                    uint32_t size, uint32_t *written) {
  cobs_encode_start_frame(cobs);
  postcard_return_t result = cobs_write_bytes(cobs, buf, size);
  if (result != POSTCARD_SUCCESS) {
    *written = cobs->next - cobs->buf;
    return result;
  }
  result = cobs_encode_end_frame(cobs);
  *written = cobs->next - cobs->buf;
  return result;
}

postcard_return_t cobs_write_byte(struct cobs *cobs, uint8_t byte) {
  // check for buffer overflow
  if (cobs->next >= cobs->end) {
    return POSTCARD_COBS_ENCODE_OVERFLOW;
  }
  // if been no 0 for 255 bytes, insert byte and reset counter
  if (cobs->zero == 255) {
    cobs_insert_zero(cobs);
    if (cobs->next >= cobs->end) {
      return POSTCARD_COBS_ENCODE_OVERFLOW;
    }
  }

  // If byte is zero, insert marker
  if (byte == 0) {
    return cobs_insert_zero(cobs);
  } else {
    // otherwise insert byte
    *(cobs->next) = byte;
    cobs->next++;
    cobs->zero++;
    return POSTCARD_SUCCESS;
  }
}

void cobs_write_byte_unchecked(struct cobs *cobs, uint8_t byte) {
  // if been no 0 for 255 bytes, insert byte and reset counter
  if (cobs->zero == 255) {
    cobs_insert_zero(cobs);
  }

  // If byte is zero, insert marker
  if (byte == 0) {
    return cobs_insert_zero(cobs);
  } else {
    // otherwise insert byte
    *(cobs->next) = byte;
    cobs->next++;
    cobs->zero++;
  }
}

void cobs_write_byte_unchecked_no_overhead(struct cobs *cobs, uint8_t byte) {
  // If byte is zero, insert marker
  if (byte == 0) {
    return cobs_insert_zero(cobs);
  } else {
    // otherwise insert byte
    *(cobs->next) = byte;
    cobs->next++;
    cobs->zero++;
  }
}

// Write an array of bytes to the buffer with cobs encoding
postcard_return_t cobs_write_bytes(struct cobs *cobs, uint8_t *bytes,
                                   uint32_t size) {
  // calc max size of encoded bytes
  // size + 1 for possible overhead byte + 1 for each 256 bytes in data
  uint32_t max_bytes = size + 1 + (size >> 8);
  uint32_t space_left = cobs->end - cobs->next;
  // printf("size: %d, max: %d, left: %d\n", size, max_bytes, space_left);
  // check if enough space in buffer
  if (space_left >= max_bytes) {
    // can used unchecked write
    if (max_bytes <= (255 - cobs->zero)) {
      // dont need to insert any overhead bytes
      for (uint32_t i = 0; i < size; i++) {
        cobs_write_byte_unchecked_no_overhead(cobs, bytes[i]);
      }
      return POSTCARD_SUCCESS;
    } else {
      for (uint32_t i = 0; i < size; i++) {
        cobs_write_byte_unchecked(cobs, bytes[i]);
      }
      return POSTCARD_SUCCESS;
    }
  } else {
    return POSTCARD_COBS_ENCODE_OVERFLOW;
  }
}

postcard_return_t cobs_insert_zero(struct cobs *cobs) {
  // Go back and set marker
  *(cobs->next - cobs->zero) = cobs->zero;
  // Add a byte
  *(cobs->next) = 0;
  cobs->next++;
  cobs->zero = 1;
  return POSTCARD_SUCCESS;
}

postcard_return_t cobs_decode_start_frame(struct cobs *cobs) {
  uint8_t byte = *(cobs->buf);
  if (byte == 0) {
    return POSTCARD_COBS_DECODE_LEADING_ZERO;
  }
  // First byte marks position of next zero
  cobs->zero = byte;
  cobs->next = cobs->buf + 1;
  cobs->overhead = cobs->zero == 0xFF;
  return POSTCARD_SUCCESS;
}

// Checks that end of frame zero is as expected
postcard_return_t cobs_decode_end_frame(struct cobs *cobs) {
  if (cobs->zero == 0) {
    return POSTCARD_SUCCESS;
  } else {
    return POSTCARD_COBS_DECODE_INVALID_ZERO;
  }
}

postcard_return_t cobs_read_byte(struct cobs *cobs, uint8_t *value) {
  // check if exceeded buffer bounds
  if (cobs->next >= cobs->end) {
    return POSTCARD_COBS_DECODE_BUFFER_END;
  }
  // decrement next zero counter
  cobs->zero--;
  // check if end of cobs frame
  if (*(cobs->next) == 0) {
    return POSTCARD_COBS_EOF;
  }

  if (cobs->zero == 0) {
    // This byte is a marker
    cobs->zero = *(cobs->next);
    // if previous marker was 0xFF, this is an overhead byte
    if (cobs->overhead) {
      cobs->overhead = cobs->zero == 0xFF;
      cobs->next++;
      return cobs_read_byte(cobs, value);
    } else {
      cobs->overhead = cobs->zero == 0xFF;
      *value = 0;
    }
  } else {
    *value = *(cobs->next);
  }
  cobs->next++;
  return POSTCARD_SUCCESS;
}

postcard_return_t cobs_read_bytes(struct cobs *cobs, uint8_t *buf,
                                  uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    postcard_return_t result = cobs_read_byte(cobs, buf + i);
    if (result != POSTCARD_SUCCESS) {
      return result;
    }
  }
  return POSTCARD_SUCCESS;
}

postcard_return_t cobs_decode(struct cobs *cobs, uint8_t *buf, uint32_t size,
                              uint32_t *written) {
  uint8_t *buf_ptr = buf;
  uint8_t *end = buf + size;
  if (cobs_decode_start_frame(cobs) == POSTCARD_COBS_DECODE_LEADING_ZERO) {
    *written = 0;
    return POSTCARD_COBS_DECODE_LEADING_ZERO;
  }
  while (true) {
    postcard_return_t result = cobs_read_byte(cobs, buf_ptr++);
    if (result != POSTCARD_SUCCESS) {
      *written = buf_ptr - buf - 1;
      if (result == POSTCARD_COBS_EOF) {
        return cobs_decode_end_frame(cobs);
      } else if (result == POSTCARD_COBS_DECODE_BUFFER_END) {
        return POSTCARD_COBS_DECODE_BUFFER_END;
      }
    } else if (buf_ptr >= end) {
      *written = buf_ptr - buf;
      return POSTCARD_COBS_DECODE_OVERFLOW;
    }
  }
}

postcard_return_t cobs_decode_in_place(struct cobs *cobs, uint32_t *written) {
  uint8_t *buf_ptr = cobs->buf;
  return cobs_decode(cobs, buf_ptr, cobs->end - cobs->buf, written);
}
