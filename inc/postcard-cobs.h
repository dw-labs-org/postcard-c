// Encoding datatypes using the postcard format to a cobs buffers
#ifndef _POSTCARD_COBS_H
#define _POSTCARD_COBS_H
#include "../inc/cobs.h"
#include "stdint.h"

void cobs_postcard_encode_u8(struct cobs *cobs, uint8_t value);

void cobs_postcard_encode_u16(struct cobs *cobs, uint16_t value);

void cobs_postcard_encode_u32(struct cobs *cobs, uint32_t value);

void cobs_postcard_encode_i8(struct cobs *cobs, int8_t value);

void cobs_postcard_encode_i16(struct cobs *cobs, int16_t value);

void cobs_postcard_encode_float(struct cobs *cobs, float value);
#endif