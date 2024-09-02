#ifndef _POSTCARD_ERRORS_H
#define _POSTCARD_ERRORS_H

typedef enum postcard_return {
  // For any function that can fail, indicates success
  POSTCARD_SUCCESS = 0,
  // Returned when cobs byte read finds a 0
  POSTCARD_COBS_EOF,
  // If first byte in buffer is a 0
  POSTCARD_COBS_DECODE_LEADING_ZERO,
  // Returned when cobs_decode_end_frame finds an unexpected 0,
  POSTCARD_COBS_DECODE_INVALID_ZERO,
  // Try to read cobs byte beyond the buffer
  POSTCARD_COBS_DECODE_BUFFER_END,
  // Try to write beyond buffer during decoding
  POSTCARD_COBS_DECODE_OVERFLOW,
  // Try to write beyond cobs buffer
  POSTCARD_COBS_ENCODE_OVERFLOW,
} postcard_return_t;
#endif