#ifndef _COBS_H
#define _COBS_H
#include "stdbool.h"
#include "stdint.h"
// struct that contains buffer and info for writing cobs encoded bytes
struct cobs {
  // Buffer being written in to
  uint8_t *buf;
  // Length of buffer
  uint32_t length;
  // Pointer to next byte location
  uint8_t *next;
  // Number of bytes since previous zero for encoding,
  // or bytes to next zero for decoding
  uint8_t zero;
  // next zero is an overhead byte. decode only
  bool overhead;
};

// initialise the cobs struct
void cobs_init(struct cobs *cobs, uint8_t *buf, uint32_t size);
// Reset for next frame
void cobs_reset(struct cobs *cobs);

// insert framing and first marker 0
void cobs_start_frame_encode(struct cobs *cobs);
// Insert the final 0, buffer is in sendable state
void cobs_end_frame_encode(struct cobs *cobs);

// Write a byte to the buffer in cobs struct
void cobs_write_byte(struct cobs *cobs, uint8_t byte);
// Write a byte array to the buffer in the cobs struct
void cobs_write_bytes(struct cobs *cobs, uint8_t *bytes, uint32_t size);

// Get the index of the next zero from first byte and setup cobs for decode
void cobs_start_frame_decode(struct cobs *cobs);
void cobs_end_frame_decode(struct cobs *cobs);

// Decode the cobs frame into a buffer
void cobs_decode(struct cobs *cobs, uint8_t *buf);
// Decode the cobs frame in place
void cobs_decode_in_place(struct cobs *cobs);

// Read a cobs encoded byte from the buffer, write it to value
void cobs_read_byte(struct cobs *cobs, uint8_t *value);

#endif