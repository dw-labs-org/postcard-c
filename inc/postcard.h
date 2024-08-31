// Encoding datatypes using the postcard format to a buffer
#ifndef POSTCARD_H
#define POSTCARD_H
#include "stdint.h"

// Append the value to the buffer
uint32_t encode_u8(uint8_t *buf, uint8_t value);

uint32_t encode_u16(uint8_t *buf, uint16_t value);

uint32_t encode_float(uint8_t *buf, float value);

#endif