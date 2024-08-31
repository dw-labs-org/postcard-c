#include "../inc/postcard.h"
#include "Unity/src/unity.h"
#include "stdint.h"

void setUp(void) {}

void tearDown(void) {
  // clean stuff up here
}

void u8_encoding(void) {
  uint8_t buf[4];
  uint32_t written;
  // u8
  written = encode_u8(buf, 5);
  TEST_ASSERT(written == 1);
  TEST_ASSERT(buf[0] == 5);
}

void u16_encoding(void) {
  uint8_t buf[4];
  uint32_t written;
  // u16
  written = encode_u16(buf, 0);
  TEST_ASSERT(written == 1);
  TEST_ASSERT(buf[0] == 0);
  written = encode_u16(buf, 127);
  TEST_ASSERT(written == 1);
  TEST_ASSERT(buf[0] == 0x7F);
  written = encode_u16(buf, 128);
  TEST_ASSERT(written == 2);
  TEST_ASSERT(buf[0] == 0x80);
  TEST_ASSERT(buf[1] == 0x01);
  written = encode_u16(buf, 16383);
  TEST_ASSERT(written == 2);
  TEST_ASSERT(buf[0] == 0xFF);
  TEST_ASSERT(buf[1] == 0x7F);
  written = encode_u16(buf, 16384);
  TEST_ASSERT(written == 3);
  TEST_ASSERT(buf[0] == 0x80);
  TEST_ASSERT(buf[1] == 0x80);
  TEST_ASSERT(buf[2] == 0x01);
  written = encode_u16(buf, 16385);
  TEST_ASSERT(written == 3);
  TEST_ASSERT(buf[0] == 0x81);
  TEST_ASSERT(buf[1] == 0x80);
  TEST_ASSERT(buf[2] == 0x01);
  written = encode_u16(buf, 65535);
  TEST_ASSERT(written == 3);
  TEST_ASSERT(buf[0] == 0xFF);
  TEST_ASSERT(buf[1] == 0xFF);
  TEST_ASSERT(buf[2] == 0x03);
}

void f32_encoding(void) {
  uint8_t buf[4];
  uint32_t written = encode_float(buf, 5.632);
  TEST_ASSERT(written == 4);
  TEST_ASSERT_EQUAL_FLOAT(5.632, *((float *)&buf));
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(u8_encoding);
  RUN_TEST(u16_encoding);
  RUN_TEST(f32_encoding);
  return UNITY_END();
}