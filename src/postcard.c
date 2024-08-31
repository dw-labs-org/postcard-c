#include "../inc/postcard.h"

#include "memory.h"

uint32_t encode_u8(uint8_t *buf, uint8_t value) {
  *buf = value;
  return 1;
}

uint32_t encode_i8(uint8_t *buf, int8_t value) {
  *buf = value;
  return 1;
}

// varint encoded u16
uint32_t encode_u16(uint8_t *buf, uint16_t value) {
  //
  if (value <= 127) {
    *buf = 0xFF & value;
    return 1;
  } else if (value <= 16383) {
    // First 7 bits + continue bit
    *buf = (0x7F & value) | (1 << 7);
    // Next 7 bits
    *(buf + 1) = (value >> 7);
    return 2;
  } else {
    *buf = (0x7F & value) | (1 << 7);
    *(buf + 1) = (0x7F & (value >> 7)) | (1 << 7);
    *(buf + 2) = (value >> 14);
    return 3;
  }
}

uint32_t encode_i16(uint8_t *buf, int8_t value) {
  *buf = (uint8_t)((value << 1) ^ (value >> 7));
  return 1;
}

uint32_t encode_float(uint8_t *buf, float value) {
  memcpy(buf, &value, 4);
  return 4;
}
