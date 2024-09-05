#ifndef _POSTCARD_ERRORS_H
#define _POSTCARD_ERRORS_H

typedef enum postcard_return {
  // For any function that can fail, indicates success
  POSTCARD_SUCCESS = 0,
  // Returned when cobs_decoder byte read finds a 0
  POSTCARD_COBS_EOF,
  // If first byte in buffer is a 0
  POSTCARD_COBS_DECODE_LEADING_ZERO,
  // Returned when cobs_decode_end_frame finds an unexpected 0,
  POSTCARD_COBS_DECODE_INVALID_ZERO,
  // Try to read a byte beyond the data in the buffer
  POSTCARD_COBS_DECODE_DATA_END,
  // Next points to end of buffer
  POSTCARD_COBS_DECODE_BUFFER_END,
  // Try to write beyond buffer during decoding
  POSTCARD_COBS_DECODE_OVERFLOW,
  // Try to write beyond cobs_decoder buffer
  POSTCARD_COBS_ENCODE_OVERFLOW,
  // Written too much data to buffer
  POSTCARD_COBS_DECODE_WRITTEN_OVERFLOW,
  // Written data over start of previous or current frame
  POSTCARD_COBS_DECODE_FRAME_OVERFLOW,
  // Written data over start of unprocessed data
  POSTCARD_COBS_DECODE_DATA_OVERFLOW,
} postcard_return_t;
#endif