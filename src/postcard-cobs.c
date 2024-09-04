#include "postcard-cobs.h"

void postcard_cobs_encode_bool(struct cobs_encoder *cobs_encoder, bool value) {
  cobs_encoder_write_byte(cobs_encoder, value);
}

void postcard_cobs_encode_u8(struct cobs_encoder *cobs_encoder, uint8_t value) {
  cobs_encoder_write_byte(cobs_encoder, value);
}

void postcard_cobs_encode_u16(struct cobs_encoder *cobs_encoder,
                              uint16_t value) {
  if (value <= ((1 << 7) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, 0xFF & value);
  } else if (value <= ((1 << 14) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 7);
  } else {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 14);
  }
}

void postcard_cobs_encode_u32(struct cobs_encoder *cobs_encoder,
                              uint32_t value) {
  if (value <= ((1 << 7) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, 0xFF & value);
  } else if (value <= ((1 << 14) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 7);
  } else if (value <= ((1 << 21) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 14);
  } else if (value <= ((1 << 28) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 21);
  } else {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 21)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 28);
  }
}

void postcard_cobs_encode_u64(struct cobs_encoder *cobs_encoder,
                              uint64_t value) {
  if (value <= ((1 << 7) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, 0xFF & value);
  } else if (value <= ((1 << 14) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 7);
  } else if (value <= ((1 << 21) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 14);
  } else if (value <= ((1 << 28) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 21);
  } else if (value <= ((1UL << 35) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 21)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 28);
  } else if (value <= ((1UL << 42) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 21)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 28)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 35);
  } else if (value <= ((1UL << 49) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 21)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 28)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 35)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 42);
  } else if (value <= ((1UL << 56) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 21)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 28)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 35)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 42)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 49);
  } else if (value <= ((1UL << 63) - 1)) {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 21)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 28)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 35)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 42)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 49)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 56);
  } else {
    cobs_encoder_write_byte(cobs_encoder, (0x7F & value) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 7)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 14)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 21)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 28)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 35)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 42)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 49)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, (0x7F & (value >> 56)) | (1 << 7));
    cobs_encoder_write_byte(cobs_encoder, value >> 63);
  }
}

void postcard_cobs_encode_i8(struct cobs_encoder *cobs_encoder, int8_t value) {
  cobs_encoder_write_byte(cobs_encoder, (uint8_t)value);
}

void postcard_cobs_encode_i16(struct cobs_encoder *cobs_encoder,
                              int16_t value) {
  // zigzag encode
  uint16_t zz = (value << 1) ^ (value >> 15);
  postcard_cobs_encode_u16(cobs_encoder, zz);
}

void postcard_cobs_encode_i32(struct cobs_encoder *cobs_encoder,
                              int32_t value) {
  // zigzag encode
  uint32_t zz = (value << 1) ^ (value >> 31);
  postcard_cobs_encode_u32(cobs_encoder, zz);
}

void postcard_cobs_encode_i64(struct cobs_encoder *cobs_encoder,
                              int64_t value) {
  // zigzag encode
  uint64_t zz = (value << 1) ^ (value >> 63);
  postcard_cobs_encode_u64(cobs_encoder, zz);
}

void postcard_cobs_encode_float(struct cobs_encoder *cobs_encoder,
                                float value) {
  cobs_encoder_write_bytes(cobs_encoder, (uint8_t *)&value, 4);
}

void postcard_cobs_encode_double(struct cobs_encoder *cobs_encoder,
                                 double value) {
  cobs_encoder_write_bytes(cobs_encoder, (uint8_t *)&value, 8);
}

void postcard_cobs_encode_discriminant(struct cobs_encoder *cobs_encoder,
                                       uint32_t value) {
  postcard_cobs_encode_u32(cobs_encoder, value);
}

void postcard_cobs_encode_length(struct cobs_encoder *cobs_encoder,
                                 uint32_t length) {
  postcard_cobs_encode_u32(cobs_encoder, length);
}

void postcard_cobs_encode_byte_array(struct cobs_encoder *cobs_encoder,
                                     uint8_t *arr, uint32_t length) {
  postcard_cobs_encode_length(cobs_encoder, length);
  cobs_encoder_write_bytes(cobs_encoder, arr, length);
}