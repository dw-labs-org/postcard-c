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

// initialise the cobs struct for either encoding or decoding
void cobs_init(struct cobs *cobs, uint8_t *buf, uint32_t size);
// Reset for next frame
void cobs_reset(struct cobs *cobs);

// insert framing and first marker 0
void cobs_encode_start_frame(struct cobs *cobs);
// Insert the final 0, buffer is in sendable state if returns POSTCARD_SUCCESS
postcard_return_t cobs_encode_end_frame(struct cobs *cobs);

// encodes size number of bytes in buf into cobs buf, written is number of bytes
// in cobs buf (including trailing 0)
postcard_return_t cobs_encode_frame(struct cobs *cobs, uint8_t *buf,
                                    uint32_t size, uint32_t *written);

// Write a byte to the buffer in cobs struct
postcard_return_t cobs_write_byte(struct cobs *cobs, uint8_t byte);
// Write a byte array to the buffer in the cobs struct
postcard_return_t cobs_write_bytes(struct cobs *cobs, uint8_t *bytes,
                                   uint32_t size);

// Get the index of the next zero from first byte and setup cobs for decode
void cobs_decode_start_frame(struct cobs *cobs);
// Checks that the end of the frame is valid (last marker points to framing 0)
postcard_return_t cobs_decode_end_frame(struct cobs *cobs);

// Decode the cobs frame into a buffer. Write number of bytes to written. size
// is buf size;
// Will return an error if the frame is invalid, cobs buffer end is reached or
// buf end is reached.
postcard_return_t cobs_decode(struct cobs *cobs, uint8_t *buf, uint32_t size,
                              uint32_t *written);
// Decode the cobs frame in place.
// Will return an error if the frame is invalid or cobs buffer end is reached
postcard_return_t cobs_decode_in_place(struct cobs *cobs, uint32_t *written);

// Read a cobs encoded byte from the buffer, write it to value
postcard_return_t cobs_read_byte(struct cobs *cobs, uint8_t *value);
// Read cobs encoded bytes from the cobs buffer, write it to buf
postcard_return_t cobs_read_bytes(struct cobs *cobs, uint8_t *buf,
                                  uint32_t size);

#endif