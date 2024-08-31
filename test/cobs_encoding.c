#include "Unity/src/unity.h"
#include "cobs.h"
#include "stdint.h"

void setUp(void) {}

void tearDown(void) {
  // clean stuff up here
}

void wikipedia_examples(void) {
  // init buffer and cobs struct
  uint8_t buf[8];
  struct cobs cobs;
  cobs_init(&cobs, buf, 8);
  // wiki example 1
  cobs_start_frame(&cobs);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_reset(&cobs);
  // wiki example 2
  cobs_start_frame(&cobs);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_reset(&cobs);
  // wiki example 3
  cobs_start_frame(&cobs);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);
  // wiki example 4
  cobs_start_frame(&cobs);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0x22);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0x33);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(3, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x22, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0x33, buf[5]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[6]);
  cobs_reset(&cobs);
  // wiki example 5
  cobs_start_frame(&cobs);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0x22);
  cobs_write_byte(&cobs, 0x33);
  cobs_write_byte(&cobs, 0x44);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(5, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x22, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x33, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0x44, buf[5]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[6]);
  cobs_reset(&cobs);
  // wiki example 6
  cobs_start_frame(&cobs);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[5]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[6]);
  cobs_reset(&cobs);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(wikipedia_examples);
  return UNITY_END();
}