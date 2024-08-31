#include "postcard-cobs.h"

void cobs_postcard_encode_u8(struct cobs *cobs, uint8_t value) {
  cobs_write_byte(cobs, value);
}

void cobs_postcard_encode_u16(struct cobs *cobs, uint16_t value) {
  if (value <= ((1 << 6) - 1)) {
    cobs_write_byte(cobs, 0xFF & value);
  } else if (value <= ((1 << 13) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, value >> 7);
  } else {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, value >> 14);
  }
}

void cobs_postcard_encode_u32(struct cobs *cobs, uint32_t value) {
  if (value <= ((1 << 6) - 1)) {
    cobs_write_byte(cobs, 0xFF & value);
  } else if (value <= ((1 << 13) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, value >> 7);
  } else if (value <= ((1 << 20) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, value >> 14);
  } else if (value <= ((1 << 27) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, value >> 21);
  } else {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 21)) | (1 << 7));
    cobs_write_byte(cobs, value >> 28);
  }
}

void cobs_postcard_encode_float(struct cobs *cobs, float value) {
  cobs_write_bytes(cobs, (uint8_t *)&value, 4);
}