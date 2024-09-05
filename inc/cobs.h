#ifndef _COBS_H
#define _COBS_H
#include "postcard-errors.h"
#include "stdbool.h"
#include "stdint.h"

// struct that contains buffer and info for writing cobs encoded bytes
struct cobs_encoder {
  // Buffer being written in to
  uint8_t *buf;
  // End of buffer
  uint8_t *end;
  // Pointer to next byte location
  uint8_t *next;
  // Number of bytes since previous zero for encoding,
  uint8_t zero;
};

// struct that contains buffer and info for decoding cobs frame
struct cobs_decoder {
  // Buffer being written in to or read from
  uint8_t *buf;
  // End of buffer
  uint8_t *end;
  // Pointer to next byte location for decoding
  uint8_t *next;
  // Pointer to last valid byte in buffer + 1
  // if data_start == data_end then buffer is empty
  uint8_t *data_end;
  // Pointer to start of the decoded (or partially decoded) frame
  uint8_t *frame_start;
  // Pointer to end of the decoded (or partially decoded) frame
  uint8_t *frame_end;
  // Number of bytes since previous zero for encoding,
  // or bytes to next zero for decoding
  uint8_t zero;
  // next zero is an overhead byte. decode only
  bool overhead;
  // true if buffer is full
  bool full;
  // true if a successful cobs_decoder_frame_start call has been made
  bool partial_decode;
};

// ========================= Encoder ====================================

// initialise the cobs_encoder struct for encoding
void cobs_encoder_init(struct cobs_encoder *cobs_encoder, uint8_t *buf,
                       uint32_t size);

// reset encoder state ready for call to cobs_encode_start_frame
void cobs_encoder_reset(struct cobs_encoder *cobs_encoder);

// insert framing and first marker 0
void cobs_encoder_start_frame(struct cobs_encoder *cobs_encoder);

// Insert the final 0, buffer is in sendable state if returns POSTCARD_SUCCESS
postcard_return_t cobs_encoder_end_frame(struct cobs_encoder *cobs_encoder);

// encodes size number of bytes in buf into cobs_decoder buf, written is number
// of bytes in cobs_decoder buf (including trailing 0)
postcard_return_t cobs_encoder_frame(struct cobs_encoder *cobs_encoder,
                                     uint8_t *buf, uint32_t size,
                                     uint32_t *written);

// Write a byte to the buffer in cobs_decoder struct
postcard_return_t cobs_encoder_write_byte(struct cobs_encoder *cobs_encoder,
                                          uint8_t byte);
// Write a byte array to the buffer in the cobs_decoder struct
postcard_return_t cobs_encoder_write_bytes(struct cobs_encoder *cobs_encoder,
                                           uint8_t *bytes, uint32_t size);

// ========================== Decoder ===================================
// data_size is size of data already in buf to be decoded
postcard_return_t cobs_decoder_init(struct cobs_decoder *cobs_decoder,
                                    uint8_t *buf, uint32_t size,
                                    uint32_t data_size);
// Reset for next frame
void cobs_decoder_reset(struct cobs_decoder *cobs_decoder);

// Get a pointer to the next place to place data bytes and space left
uint32_t cobs_decoder_get_data_ptr(struct cobs_decoder *cobs_decoder,
                                   uint8_t **ptr);

// Inform the encoder about data written to the buffer
postcard_return_t cobs_decoder_data_written(struct cobs_decoder *cobs_decoder,
                                            uint32_t size);

// Start the decoding process
postcard_return_t cobs_decoder_start_frame(struct cobs_decoder *cobs_decoder);

// End the frame decoding process
postcard_return_t cobs_decoder_end_frame(struct cobs_decoder *cobs_decoder);

// if byte should be 0, sets as 0, otherwise leaves as is
// Only used for messages < 255 bytes
postcard_return_t cobs_decoder_decode_byte_in_place_short(
    struct cobs_decoder *cobs_decoder);

// Faster version than looping over cobs_decoder_decode_byte_in_place_short
postcard_return_t cobs_decoder_decode_bytes_in_place_short(
    struct cobs_decoder *cobs_decoder);

// Keeps decoding remaining bytes in buffer until a frame is found
postcard_return_t cobs_decoder_frame_in_place_short(
    struct cobs_decoder *cobs_decoder);

// get pointers to the start and end of the frame
// marks the frame as "read" so data can be moved over it
void cobs_decoder_frame_ptrs(struct cobs_decoder *cobs_decoder, uint8_t **start,
                             uint8_t **end);

// Shift valid data to start of buffer to allow space for more data
uint32_t cobs_decoder_shift_data(struct cobs_decoder *cobs_decoder);

// ========================= Decoder circular buffer ======================
// Get a pointer to the next place to place data bytes and space left
uint32_t cobs_decoder_get_data_ptr_circular(struct cobs_decoder *cobs_decoder,
                                            uint8_t **ptr);

// Inform the encoder about data written to the buffer
postcard_return_t cobs_decoder_data_written_circular(
    struct cobs_decoder *cobs_decoder, uint32_t size);

// Get the index of the next zero from first byte and setup cobs_decoder for
// decode
postcard_return_t cobs_decoder_start_frame_circular(
    struct cobs_decoder *cobs_decoder);
// Checks that the end of the frame is valid (last marker points to framing 0)
postcard_return_t cobs_decoder_end_frame_circular(
    struct cobs_decoder *cobs_decoder);

// Decode the cobs_decoder frame into a buffer. Write number of bytes to
// written. size is buf size; Will return an error if the frame is invalid,
// cobs_decoder buffer end is reached or buf end is reached.
postcard_return_t cobs_decoder_frame_circular(struct cobs_decoder *cobs_decoder,
                                              uint8_t *buf, uint32_t size,
                                              uint32_t *written);
// Decode the cobs_decoder frame in place.
// Will return an error if the frame is invalid or cobs_decoder buffer end is
// reached
postcard_return_t cobs_decoder_frame_in_place_circular(
    struct cobs_decoder *cobs_decoder, uint32_t *written);

// Read a cobs_decoder encoded byte from the buffer, write it to value
postcard_return_t cobs_decoder_read_byte_circular(
    struct cobs_decoder *cobs_decoder, uint8_t *value);
// Read cobs_decoder encoded bytes from the cobs_decoder buffer, write it to buf
postcard_return_t cobs_decoder_read_bytes_circular(
    struct cobs_decoder *cobs_decoder, uint8_t *buf, uint32_t size);

// Place up to size bytes from buf into the decoding circular buffer
uint32_t cobs_decoder_place_bytes_circular(struct cobs_decoder *cobs_decoder,
                                           uint8_t *buf, uint32_t size);

// Pull a frame out of the decoded in place buffer.
uint32_t cobs_decoder_fetch_frame_circular(struct cobs_decoder *cobs_decoder,
                                           uint8_t *buf, uint32_t size);

#endif