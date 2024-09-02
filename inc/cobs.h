#ifndef _COBS_H
#define _COBS_H
#include "postcard-errors.h"
#include "stdbool.h"
#include "stdint.h"
// struct that contains buffer and info for writing cobs encoded bytes
struct cobs {
  // Buffer being written in to or read from
  uint8_t *buf;
  // End of buffer
  uint8_t *end;
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
postcard_return_t cobs_end_frame_encode(struct cobs *cobs);

// encodes size number of bytes in buf into cobs buf, written is number of bytes
// in cobs buf (including trailing 0)
postcard_return_t cobs_encode(struct cobs *cobs, uint8_t *buf, uint32_t size,
                              uint32_t *written);

// Write a byte to the buffer in cobs struct
postcard_return_t cobs_write_byte(struct cobs *cobs, uint8_t byte);
// Write a byte array to the buffer in the cobs struct
postcard_return_t cobs_write_bytes(struct cobs *cobs, uint8_t *bytes,
                                   uint32_t size);

// Get the index of the next zero from first byte and setup cobs for decode
void cobs_start_frame_decode(struct cobs *cobs);
postcard_return_t cobs_end_frame_decode(struct cobs *cobs);

// Decode the cobs frame into a buffer. Write number of bytes to length
postcard_return_t cobs_decode(struct cobs *cobs, uint8_t *buf,
                              uint32_t *length);
// Decode the cobs frame in place
postcard_return_t cobs_decode_in_place(struct cobs *cobs, uint32_t *length);

// Read a cobs encoded byte from the buffer, write it to value
postcard_return_t cobs_read_byte(struct cobs *cobs, uint8_t *value);
// Read cobs encoded bytes from the cobs buffer, write it to buf
postcard_return_t cobs_read_bytes(struct cobs *cobs, uint8_t *buf,
                                  uint32_t size);

#endif