#include "cobs.h"

void cobs_insert_zero(struct cobs *cobs);

// assign buffer and length
void cobs_init(struct cobs *cobs, uint8_t *buf, uint32_t length) {
  cobs->buf = buf;
  cobs->next = buf;
  cobs->length = length;
  cobs->bytes_since_zero = 1;
}

void cobs_reset(struct cobs *cobs) {
  cobs->next = cobs->buf;
  cobs->bytes_since_zero;
}

// Inserts the framing 0 and the first marker byte
void cobs_start_frame(struct cobs *cobs) {
  // framing zero
  *(cobs->next) = 0;
  cobs->next++;
  // marker zero
  *(cobs->next) = 0;
  cobs->next++;
  cobs->bytes_since_zero = 1;
}
void cobs_end_frame(struct cobs *cobs) { cobs_insert_zero(cobs); }

void cobs_write_byte(struct cobs *cobs, uint8_t byte) {
  // if been no 0 for 255 bytes, insert byte and reset counter
  if (cobs->bytes_since_zero == 255) {
    cobs_insert_zero(cobs);
  }

  // If byte is zero, insert marker
  if (byte == 0) {
    cobs_insert_zero(cobs);
  } else {
    // otherwise insert byte
    *(cobs->next) = byte;
    cobs->next++;
    cobs->bytes_since_zero++;
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
  *(cobs->next - cobs->bytes_since_zero) = cobs->bytes_since_zero;
  // Add a byte
  *(cobs->next) = 0;
  cobs->next++;
  cobs->bytes_since_zero = 1;
}
