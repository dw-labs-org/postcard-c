#include "postcard.h"

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

postcard_return_t postcard_decode_u8(uint8_t *buf, uint8_t *end,
                                     uint8_t *value) {
  if (buf == end) {
    return POSTCARD_EOF;
  }
  *value = *buf++;
  return POSTCARD_SUCCESS;
}

postcard_return_t postcard_decode_u16(uint8_t *buf, uint8_t *end,
                                      uint16_t *value) {
  uint16_t result = 0;
  for (uint8_t i = 0; i < 3; i++) {
    if (buf == end) {
      return POSTCARD_EOF;
    }
    uint8_t byte = *(buf++);
    if (byte < (1 << 7)) {
      // final byte
      result |= (byte << (7 * i));
      *value = result;
      return POSTCARD_SUCCESS;
    } else {
      result |= ((byte & 0x7F) << (7 * i));
    }
  }
  *value = result;
  return POSTCARD_SUCCESS;
}

postcard_return_t postcard_decode_u32(uint8_t *buf, uint8_t *end,
                                      uint32_t *value) {
  uint32_t result = 0;
  for (uint8_t i = 0; i < 5; i++) {
    if (buf == end) {
      return POSTCARD_EOF;
    }
    uint8_t byte = *(buf++);
    if (byte < (1 << 7)) {
      // final byte
      result |= (byte << (7 * i));
      *value = result;
      return POSTCARD_SUCCESS;
    } else {
      result |= ((byte & 0x7F) << (7 * i));
    }
  }
  *value = result;
  return POSTCARD_SUCCESS;
}

postcard_return_t postcard_decode_u64(uint8_t *buf, uint8_t *end,
                                      uint64_t *value);

postcard_return_t postcard_decode_float(uint8_t *buf, uint8_t *end,
                                        float *value) {
  if (end - buf >= 4) {
    memcpy(value, buf, 4);
    buf += 4;
    return POSTCARD_SUCCESS;
  } else {
    return POSTCARD_EOF;
  }
}

postcard_return_t postcard_decode_double(uint8_t *buf, uint8_t *end,
                                         double *value) {
  if (end - buf >= 8) {
    memcpy(value, buf, 8);
    buf += 8;
    return POSTCARD_SUCCESS;
  } else {
    return POSTCARD_EOF;
  }
}

postcard_return_t postcard_decode_discriminant(uint8_t *buf, uint8_t *end,
                                               uint32_t *value) {
  return postcard_decode_u32(buf, end, value);
}