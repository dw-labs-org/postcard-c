// Encoding datatypes using the postcard format to a cobs_encoder buffers
#ifndef _POSTCARD_COBS_H
#define _POSTCARD_COBS_H
#include "cobs.h"
#include "stdbool.h"
#include "stdint.h"

void postcard_cobs_encode_bool(struct cobs_encoder *cobs_encoder, bool value);

void postcard_cobs_encode_u8(struct cobs_encoder *cobs_encoder, uint8_t value);

void postcard_cobs_encode_u16(struct cobs_encoder *cobs_encoder, uint16_t value);

void postcard_cobs_encode_u32(struct cobs_encoder *cobs_encoder, uint32_t value);

void postcard_cobs_encode_u64(struct cobs_encoder *cobs_encoder, uint64_t value);

void postcard_cobs_encode_i8(struct cobs_encoder *cobs_encoder, int8_t value);

void postcard_cobs_encode_i16(struct cobs_encoder *cobs_encoder, int16_t value);

void postcard_cobs_encode_i32(struct cobs_encoder *cobs_encoder, int32_t value);

void postcard_cobs_encode_i64(struct cobs_encoder *cobs_encoder, int64_t value);

void postcard_cobs_encode_float(struct cobs_encoder *cobs_encoder, float value);

void postcard_cobs_encode_double(struct cobs_encoder *cobs_encoder, double value);

void postcard_cobs_encode_discriminant(struct cobs_encoder *cobs_encoder, uint32_t value);

void postcard_cobs_encode_length(struct cobs_encoder *cobs_encoder, uint32_t length);

void postcard_cobs_encode_byte_array(struct cobs_encoder *cobs_encoder, uint8_t *arr,
                                     uint32_t length);
#endif