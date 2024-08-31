#include "Unity/src/unity.h"
#include "postcard-cobs.h"
#include "stdint.h"

void setUp(void) {}

void tearDown(void) {
  // clean stuff up here
}

void u16_encoding(void) {
  struct cobs cobs;
  uint8_t buf[10];
  cobs_init(&cobs, buf, 10);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 0);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 127);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 128);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(3, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 16383);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(3, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 16384);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(4, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 16385);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(4, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x81, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u16(&cobs, 65535);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(4, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);
}

void u32_encoding(void) {
  struct cobs cobs;
  uint8_t buf[10];
  cobs_init(&cobs, buf, 10);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u32(&cobs, 0);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u32(&cobs, 127);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u32(&cobs, 128);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(3, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u32(&cobs, 16383);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(3, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u32(&cobs, 16384);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(4, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u32(&cobs, 16385);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(4, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x81, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);

  cobs_start_frame(&cobs);
  postcard_cobs_encode_u32(&cobs, 65535);
  cobs_end_frame(&cobs);
  TEST_ASSERT_EQUAL_UINT8(0, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(4, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(u16_encoding);
  RUN_TEST(u32_encoding);
  return UNITY_END();
}