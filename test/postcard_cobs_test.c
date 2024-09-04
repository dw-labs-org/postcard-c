#include "Unity/src/unity.h"
#include "postcard-cobs.h"
#include "stdint.h"

void setUp(void) {}

void tearDown(void) {
  // clean stuff up here
}

void u16_encoding(void) {
  struct cobs_encoder cobs_encoder;
  uint8_t buf[10];
  cobs_encoder_init(&cobs_encoder, buf, 10);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u16(&cobs_encoder, 0);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u16(&cobs_encoder, 127);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u16(&cobs_encoder, 128);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u16(&cobs_encoder, 16383);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u16(&cobs_encoder, 16384);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u16(&cobs_encoder, 16385);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x81, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u16(&cobs_encoder, 65535);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);
}

void u32_encoding(void) {
  struct cobs_encoder cobs_encoder;
  uint8_t buf[10];
  cobs_encoder_init(&cobs_encoder, buf, 10);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u32(&cobs_encoder, 0);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u32(&cobs_encoder, 127);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u32(&cobs_encoder, 128);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u32(&cobs_encoder, 16383);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u32(&cobs_encoder, 16384);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u32(&cobs_encoder, 16385);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x81, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_u32(&cobs_encoder, 65535);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);
}

void i16_encoding(void) {
  struct cobs_encoder cobs_encoder;
  uint8_t buf[10];
  cobs_encoder_init(&cobs_encoder, buf, 10);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, 0);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, -1);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, 1);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, 63);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7E, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, -64);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, 64);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, -65);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x81, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, 32767);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFE, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i16(&cobs_encoder, -32768);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);
}

void i32_encoding(void) {
  struct cobs_encoder cobs_encoder;
  uint8_t buf[10];
  cobs_encoder_init(&cobs_encoder, buf, 10);
  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 0);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -1);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 1);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 63);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7E, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -64);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 64);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -65);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x81, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 32767);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFE, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -32768);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 0);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -1);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 1);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 63);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7E, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -64);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x7F, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 64);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x80, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -65);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x81, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x01, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, 32767);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFE, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);

  cobs_encoder_start_frame(&cobs_encoder);
  postcard_cobs_encode_i32(&cobs_encoder, -32768);
  cobs_encoder_end_frame(&cobs_encoder);
  TEST_ASSERT_EQUAL_UINT8(4, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0xFF, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x03, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_encoder_reset(&cobs_encoder);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(u16_encoding);
  RUN_TEST(u32_encoding);
  RUN_TEST(i16_encoding);
  RUN_TEST(i32_encoding);
  return UNITY_END();
}