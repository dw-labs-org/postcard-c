#ifndef _COBS_H
#define _COBS_H
#include "stdint.h"

// struct that contains buffer and info for writing cobs encoded bytes
struct cobs {
  // Buffer being written in to
  uint8_t *buf;
  // Length of buffer
  uint32_t length;
  // Pointer to next byte location
  uint8_t *next;
  // Number of bytes since previous zero
  uint8_t bytes_since_zero;
};

// initialise the cobs struct
void cobs_init(struct cobs *cobs, uint8_t *buf, uint32_t size);
// insert framing and first marker 0
void cobs_start_frame(struct cobs *cobs);
// Reset for next frame
void cobs_reset(struct cobs *cobs);
// Insert the final 0, buffer is in sendable state
void cobs_end_frame(struct cobs *cobs);

// Write a byte to the buffer in cobs struct
void cobs_write_byte(struct cobs *cobs, uint8_t byte);
// Write a byte array to the buffer in the cobs struct
void cobs_write_bytes(struct cobs *cobs, uint8_t *bytes, uint32_t size);

#endif