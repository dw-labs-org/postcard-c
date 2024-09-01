// Encoding datatypes using the postcard format to a cobs buffers
#ifndef _POSTCARD_COBS_H
#define _POSTCARD_COBS_H
#include "cobs.h"
#include "stdbool.h"
#include "stdint.h"

void postcard_cobs_encode_bool(struct cobs *cobs, bool value);

void postcard_cobs_encode_u8(struct cobs *cobs, uint8_t value);

void postcard_cobs_encode_u16(struct cobs *cobs, uint16_t value);

void postcard_cobs_encode_u32(struct cobs *cobs, uint32_t value);

void postcard_cobs_encode_u64(struct cobs *cobs, uint64_t value);

void postcard_cobs_encode_i8(struct cobs *cobs, int8_t value);

void postcard_cobs_encode_i16(struct cobs *cobs, int16_t value);

void postcard_cobs_encode_i32(struct cobs *cobs, int32_t value);

void postcard_cobs_encode_i64(struct cobs *cobs, int64_t value);

void postcard_cobs_encode_float(struct cobs *cobs, float value);

void postcard_cobs_encode_double(struct cobs *cobs, double value);

void postcard_cobs_encode_discriminant(struct cobs *cobs, uint32_t value);

void postcard_cobs_encode_length(struct cobs *cobs, uint32_t length);

void postcard_cobs_encode_byte_array(struct cobs *cobs, uint8_t *arr,
                                     uint32_t length);
#endif