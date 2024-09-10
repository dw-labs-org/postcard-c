// Decoding and encoding datatypes using the postcard format to a buffer
#ifndef POSTCARD_H
#define POSTCARD_H
#include "postcard-errors.h"
#include "stdbool.h"
#include "stdint.h"

// Append the value to the buffer
uint32_t encode_u8(uint8_t *buf, uint8_t value);

uint32_t encode_u16(uint8_t *buf, uint16_t value);

uint32_t encode_float(uint8_t *buf, float value);

// all decode function increment the buffer pointer passed to them on success
// They also check if buf == end before accessing bytes

bool postcard_decode_u8(uint8_t **buf, uint8_t *end, uint8_t *value);

bool postcard_decode_u16(uint8_t **buf, uint8_t *end, uint16_t *value);

bool postcard_decode_u32(uint8_t **buf, uint8_t *end, uint32_t *value);

bool postcard_decode_u64(uint8_t **buf, uint8_t *end, uint64_t *value);

bool postcard_decode_float(uint8_t **buf, uint8_t *end, float *value);

bool postcard_decode_double(uint8_t **buf, uint8_t *end, double *value);

bool postcard_decode_discriminant(uint8_t **buf, uint8_t *end, uint32_t *value);

#endif