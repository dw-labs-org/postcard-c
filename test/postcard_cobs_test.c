#include "Unity/src/unity.h"
#include "postcard-cobs.h"
#include "stdint.h"

void setUp(void) {}

void tearDown(void) {
  // clean stuff up here
}

void u8_encoding(void) {
  struct cobs cobs;
  uint8_t buf[10];
  cobs_init(&cobs, buf, 10);
  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 0);
  cobs_end_frame(&cobs);
  // u8
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(u8_encoding);
  return UNITY_END();
}