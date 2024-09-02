#include "cobs.h"

void cobs_insert_zero(struct cobs *cobs);

// assign buffer and length
void cobs_init(struct cobs *cobs, uint8_t *buf, uint32_t length) {
  cobs->buf = buf;
  cobs->next = buf;
  cobs->length = length;
  cobs->zero = 0;
  cobs->overhead = false;
}

void cobs_reset(struct cobs *cobs) {
  cobs->next = cobs->buf;
  cobs->zero = 0;
}

// Inserts the framing 0 and the first marker byte
void cobs_start_frame_encode(struct cobs *cobs) {
  // marker zero
  *(cobs->next) = 0;
  cobs->next++;
  cobs->zero = 1;
}
void cobs_end_frame_encode(struct cobs *cobs) { cobs_insert_zero(cobs); }

void cobs_write_byte(struct cobs *cobs, uint8_t byte) {
  // if been no 0 for 255 bytes, insert byte and reset counter
  if (cobs->zero == 255) {
    cobs_insert_zero(cobs);
  }

  // If byte is zero, insert marker
  if (byte == 0) {
    cobs_insert_zero(cobs);
  } else {
    // otherwise insert byte
    *(cobs->next) = byte;
    cobs->next++;
    cobs->zero++;
  }
}

// Write an array of bytes to the buffer with cobs encoding
void cobs_write_bytes(struct cobs *cobs, uint8_t *bytes, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    cobs_write_byte(cobs, bytes[i]);
  }
}

void cobs_insert_zero(struct cobs *cobs) {
  // Go back and set marker
  *(cobs->next - cobs->zero) = cobs->zero;
  // Add a byte
  *(cobs->next) = 0;
  cobs->next++;
  cobs->zero = 1;
}

void cobs_start_frame_decode(struct cobs *cobs) {
  // First byte marks position of next zero
  cobs->zero = *(cobs->buf);
  cobs->next = cobs->buf + 1;
  cobs->overhead = false;
}

void cobs_end_frame_decode(struct cobs *cobs) {}

void cobs_read_byte(struct cobs *cobs, uint8_t *value) {
  // decrement next zero counter
  cobs->zero--;
  if (cobs->zero == 0) {
    // This byte is a marker
    cobs->zero = *(cobs->next);
    // if previous marker was 0xFF, this is an overhead byte
    if (cobs->overhead) {
      cobs->overhead = cobs->zero == 0xFF;
      cobs->next++;
      cobs_read_byte(cobs, value);
    } else {
      cobs->overhead = cobs->zero == 0xFF;
      *value = 0;
    }
  } else {
    *value = *(cobs->next);
  }
  cobs->next++;
}

void cobs_decode(struct cobs *cobs, uint8_t *buf) {
  cobs_start_frame_decode(cobs);
  while (*cobs->next != 0) {
    cobs_read_byte(cobs, buf++);
  }
}

void cobs_decode_in_place(struct cobs *cobs) {
  uint8_t *buf_ptr = cobs->buf;
  cobs_decode(cobs, buf_ptr);
}
