#include "postcard-cobs.h"

void postcard_cobs_encode_bool(struct cobs *cobs, bool value) {
  cobs_write_byte(cobs, value);
}

void postcard_cobs_encode_u8(struct cobs *cobs, uint8_t value) {
  cobs_write_byte(cobs, value);
}

void postcard_cobs_encode_u16(struct cobs *cobs, uint16_t value) {
  if (value <= ((1 << 7) - 1)) {
    cobs_write_byte(cobs, 0xFF & value);
  } else if (value <= ((1 << 14) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, value >> 7);
  } else {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, value >> 14);
  }
}

void postcard_cobs_encode_u32(struct cobs *cobs, uint32_t value) {
  if (value <= ((1 << 7) - 1)) {
    cobs_write_byte(cobs, 0xFF & value);
  } else if (value <= ((1 << 14) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, value >> 7);
  } else if (value <= ((1 << 21) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, value >> 14);
  } else if (value <= ((1 << 28) - 1)) {
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

void postcard_cobs_encode_u64(struct cobs *cobs, uint64_t value) {
  if (value <= ((1 << 7) - 1)) {
    cobs_write_byte(cobs, 0xFF & value);
  } else if (value <= ((1 << 14) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, value >> 7);
  } else if (value <= ((1 << 21) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, value >> 14);
  } else if (value <= ((1 << 28) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, value >> 21);
  } else if (value <= ((1UL << 35) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 21)) | (1 << 7));
    cobs_write_byte(cobs, value >> 28);
  } else if (value <= ((1UL << 42) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 21)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 28)) | (1 << 7));
    cobs_write_byte(cobs, value >> 35);
  } else if (value <= ((1UL << 49) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 21)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 28)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 35)) | (1 << 7));
    cobs_write_byte(cobs, value >> 42);
  } else if (value <= ((1UL << 56) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 21)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 28)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 35)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 42)) | (1 << 7));
    cobs_write_byte(cobs, value >> 49);
  } else if (value <= ((1UL << 63) - 1)) {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 21)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 28)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 35)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 42)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 49)) | (1 << 7));
    cobs_write_byte(cobs, value >> 56);
  } else {
    cobs_write_byte(cobs, (0x7F & value) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 7)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 14)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 21)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 28)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 35)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 42)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 49)) | (1 << 7));
    cobs_write_byte(cobs, (0x7F & (value >> 56)) | (1 << 7));
    cobs_write_byte(cobs, value >> 63);
  }
}

void postcard_cobs_encode_i8(struct cobs *cobs, int8_t value) {
  cobs_write_byte(cobs, (uint8_t)value);
}

void postcard_cobs_encode_i16(struct cobs *cobs, int16_t value) {
  // zigzag encode
  uint16_t zz = (value << 1) ^ (value >> 15);
  postcard_cobs_encode_u16(cobs, zz);
}

void postcard_cobs_encode_i32(struct cobs *cobs, int32_t value) {
  // zigzag encode
  uint32_t zz = (value << 1) ^ (value >> 31);
  postcard_cobs_encode_u32(cobs, zz);
}

void postcard_cobs_encode_i64(struct cobs *cobs, int64_t value) {
  // zigzag encode
  uint64_t zz = (value << 1) ^ (value >> 63);
  postcard_cobs_encode_u64(cobs, zz);
}

void postcard_cobs_encode_float(struct cobs *cobs, float value) {
  cobs_write_bytes(cobs, (uint8_t *)&value, 4);
}

void postcard_cobs_encode_double(struct cobs *cobs, double value) {
  cobs_write_bytes(cobs, (uint8_t *)&value, 8);
}

void postcard_cobs_encode_discriminant(struct cobs *cobs, uint32_t value) {
  postcard_cobs_encode_u32(cobs, value);
}

void postcard_cobs_encode_length(struct cobs *cobs, uint32_t length) {
  postcard_cobs_encode_u32(cobs, length);
}

void postcard_cobs_encode_byte_array(struct cobs *cobs, uint8_t *arr,
                                     uint32_t length) {
  postcard_cobs_encode_length(cobs, length);
  cobs_write_bytes(cobs, arr, length);
}