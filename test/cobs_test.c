#include "cobs.h"

#include "Unity/src/unity.h"
#include "stdint.h"

void setUp(void) {}

void tearDown(void) {
  // clean stuff up here
}
uint32_t write_seq(uint8_t *buf, uint8_t start, uint8_t end) {
  uint32_t i = 0;
  while (start <= end) {
    buf[i] = start;
    i++;
    start++;
  }
  return i;
}

void example_7_unencoded(uint8_t *buf) { write_seq(buf, 0x01, 0xFE); }
void example_7_encoded(uint8_t *buf) {
  buf[0] = 0xFF;
  uint32_t n = write_seq(buf + 1, 0x01, 0xFE);
  buf[n + 1] = 0;
}

void wikipedia_examples_encode(void) {
  // init buffer and cobs struct
  uint8_t buf[8];
  struct cobs cobs;
  cobs_init(&cobs, buf, 8);
  // wiki example 1
  cobs_start_frame_encode(&cobs);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame_encode(&cobs);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[2]);
  cobs_reset(&cobs);
  // wiki example 2
  cobs_start_frame_encode(&cobs);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame_encode(&cobs);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[3]);
  cobs_reset(&cobs);
  // wiki example 3
  cobs_start_frame_encode(&cobs);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame_encode(&cobs);
  TEST_ASSERT_EQUAL_UINT8(1, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[4]);
  cobs_reset(&cobs);
  // wiki example 4
  cobs_start_frame_encode(&cobs);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0x22);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0x33);
  cobs_end_frame_encode(&cobs);
  TEST_ASSERT_EQUAL_UINT8(3, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x22, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(2, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x33, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);
  // wiki example 5
  cobs_start_frame_encode(&cobs);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0x22);
  cobs_write_byte(&cobs, 0x33);
  cobs_write_byte(&cobs, 0x44);
  cobs_end_frame_encode(&cobs);
  TEST_ASSERT_EQUAL_UINT8(5, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(0x22, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(0x33, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(0x44, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);
  // wiki example 6
  cobs_start_frame_encode(&cobs);
  cobs_write_byte(&cobs, 0x11);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0);
  cobs_write_byte(&cobs, 0);
  cobs_end_frame_encode(&cobs);
  TEST_ASSERT_EQUAL_UINT8(2, buf[0]);
  TEST_ASSERT_EQUAL_UINT8(0x11, buf[1]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[2]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[3]);
  TEST_ASSERT_EQUAL_UINT8(1, buf[4]);
  TEST_ASSERT_EQUAL_UINT8(0, buf[5]);
  cobs_reset(&cobs);
}

void wikipedia_examples_decode(void) {
  {
    // wiki example 1
    uint8_t buf[] = {1, 1, 0};
    uint8_t expected[] = {0};
    struct cobs cobs;
    cobs_init(&cobs, buf, 3);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, 1);
  }

  {
    // wiki example 2
    uint8_t buf[] = {1, 1, 1, 0};
    uint8_t expected[] = {0, 0};
    struct cobs cobs;
    cobs_init(&cobs, buf, 4);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, 2);
  }

  {
    // wiki example 3
    uint8_t buf[] = {1, 2, 0x11, 1, 0};
    uint8_t expected[] = {0, 0x11, 0};
    struct cobs cobs;
    cobs_init(&cobs, buf, 5);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, 3);
  }
  {
    // wiki example 4
    uint8_t buf[] = {3, 0x11, 0x22, 0x2, 0x33, 0};
    uint8_t expected[] = {0x11, 0x22, 0, 0x33};
    struct cobs cobs;
    cobs_init(&cobs, buf, 6);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, 4);
  }
  {
    // wiki example 5
    uint8_t buf[] = {5, 0x11, 0x22, 0x33, 0x44, 0};
    uint8_t expected[] = {0x11, 0x22, 0x33, 0x44};
    struct cobs cobs;
    cobs_init(&cobs, buf, 6);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, 4);
  }
  {
    // wiki example 6
    uint8_t buf[] = {2, 0x11, 1, 1, 1, 0};
    uint8_t expected[] = {0x11, 0, 0, 0};
    struct cobs cobs;
    cobs_init(&cobs, buf, 6);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, 4);
  }
  {
    // wiki example 6
    uint8_t buf[] = {2, 0x11, 1, 1, 1, 0};
    uint8_t expected[] = {0x11, 0, 0, 0};
    struct cobs cobs;
    cobs_init(&cobs, buf, 6);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buf, 4);
  }
  {
    // wiki example 7
    uint32_t size = 270;
    uint8_t encoded[size];
    example_7_encoded(encoded);
    uint8_t unencoded[size];
    example_7_unencoded(unencoded);
    struct cobs cobs;
    cobs_init(&cobs, encoded, size);
    cobs_decode_in_place(&cobs);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, encoded, 254);
  }
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(wikipedia_examples_encode);
  RUN_TEST(wikipedia_examples_decode);
  return UNITY_END();
}