#include "cobs.h"

#include "Unity/src/unity.h"
#include "memory.h"
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
    if (start == 0xFF) {
      break;
    }
    start++;
  }
  return i;
}

uint32_t example_1_encoded(uint8_t *buf) {
  uint8_t data[] = {1, 1, 0};
  memcpy(buf, data, 3);
  return 3;
}

uint32_t example_2_encoded(uint8_t *buf) {
  uint8_t data[] = {1, 1, 1, 0};
  memcpy(buf, data, 4);
  return 4;
}

uint32_t example_3_encoded(uint8_t *buf) {
  uint8_t data[] = {1, 2, 0x11, 1, 0};
  memcpy(buf, data, 5);
  return 5;
}

uint32_t example_4_encoded(uint8_t *buf) {
  uint8_t data[] = {3, 0x11, 0x22, 2, 0x33, 0};
  memcpy(buf, data, 6);
  return 6;
}

uint32_t example_5_encoded(uint8_t *buf) {
  uint8_t data[] = {5, 0x11, 0x22, 0x33, 0x44, 0};
  memcpy(buf, data, 6);
  return 6;
}

uint32_t example_6_encoded(uint8_t *buf) {
  uint8_t data[] = {2, 0x11, 1, 1, 1, 0};
  memcpy(buf, data, 6);
  return 6;
}

uint32_t example_7_encoded(uint8_t *buf) {
  buf[0] = 0xFF;
  uint32_t n = write_seq(buf + 1, 0x01, 0xFE);
  buf[n + 1] = 0;
  return 256;
}

uint32_t example_8_encoded(uint8_t *buf) {
  buf[0] = 0x1;
  buf[1] = 0xFF;
  uint32_t n = write_seq(buf + 2, 0x01, 0xFE);
  buf[n + 2] = 0;
  return n + 3;
}

uint32_t example_9_encoded(uint8_t *buf) {
  buf[0] = 0xFF;
  uint32_t n = write_seq(buf + 1, 0x01, 0xFE);
  buf[n + 1] = 2;
  buf[n + 2] = 0xFF;
  buf[n + 3] = 0x00;
  return n + 4;
}

uint32_t example_10_encoded(uint8_t *buf) {
  buf[0] = 0xFF;
  uint32_t n = write_seq(buf + 1, 0x02, 0xFF);
  buf[n + 1] = 1;
  buf[n + 2] = 0x1;
  buf[n + 3] = 0x00;
  return n + 4;
}

uint32_t example_11_encoded(uint8_t *buf) {
  buf[0] = 0xFE;
  uint32_t n = write_seq(buf + 1, 0x03, 0xFF);
  buf[n + 1] = 2;
  buf[n + 2] = 0x1;
  buf[n + 3] = 0x00;
  return n + 4;
}

uint32_t example_1_unencoded(uint8_t *buf) {
  uint8_t data[] = {0};
  memcpy(buf, data, 1);
  return 1;
}

uint32_t example_2_unencoded(uint8_t *buf) {
  uint8_t data[] = {0, 0};
  memcpy(buf, data, 2);
  return 2;
}
uint32_t example_3_unencoded(uint8_t *buf) {
  uint8_t data[] = {0, 0x11, 0};
  memcpy(buf, data, 3);
  return 3;
}

uint32_t example_4_unencoded(uint8_t *buf) {
  uint8_t data[] = {0x11, 0x22, 0, 0x33};
  memcpy(buf, data, 4);
  return 4;
}

uint32_t example_5_unencoded(uint8_t *buf) {
  uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
  memcpy(buf, data, 4);
  return 4;
}

uint32_t example_6_unencoded(uint8_t *buf) {
  uint8_t data[] = {0x11, 0, 0, 0};
  memcpy(buf, data, 4);
  return 4;
}

uint32_t example_7_unencoded(uint8_t *buf) {
  return write_seq(buf, 0x01, 0xFE);
}

uint32_t example_8_unencoded(uint8_t *buf) {
  return write_seq(buf, 0x00, 0xFE);
}

uint32_t example_9_unencoded(uint8_t *buf) {
  return write_seq(buf, 0x01, 0xFF);
}

uint32_t example_10_unencoded(uint8_t *buf) {
  uint32_t n = write_seq(buf, 0x02, 0xFF);
  buf[n] = 0;
  return n + 1;
}

uint32_t example_11_unencoded(uint8_t *buf) {
  uint32_t n = write_seq(buf, 0x03, 0xFF);
  buf[n] = 0;
  buf[n + 1] = 1;
  return n + 2;
}

// Picks the example, writes to buf, returns the number of bytes written
uint32_t example_unencoded(uint8_t example, uint8_t *buf) {
  switch (example) {
    case 1:
      return example_1_unencoded(buf);
      break;
    case 2:
      return example_2_unencoded(buf);
      break;
    case 3:
      return example_3_unencoded(buf);
      break;
    case 4:
      return example_4_unencoded(buf);
      break;
    case 5:
      return example_5_unencoded(buf);
      break;
    case 6:
      return example_6_unencoded(buf);
      break;
    case 7:
      return example_7_unencoded(buf);
      break;
    case 8:
      return example_8_unencoded(buf);
      break;
    case 9:
      return example_9_unencoded(buf);
      break;
    case 10:
      return example_10_unencoded(buf);
      break;
    case 11:
      return example_11_unencoded(buf);
      break;
    default:
      return 0;
  }
}

// Picks the example, writes to buf, returns the number of bytes written
uint32_t example_encoded(uint8_t example, uint8_t *buf) {
  switch (example) {
    case 1:
      return example_1_encoded(buf);
      break;
    case 2:
      return example_2_encoded(buf);
      break;
    case 3:
      return example_3_encoded(buf);
      break;
    case 4:
      return example_4_encoded(buf);
      break;
    case 5:
      return example_5_encoded(buf);
      break;
    case 6:
      return example_6_encoded(buf);
      break;
    case 7:
      return example_7_encoded(buf);
      break;
    case 8:
      return example_8_encoded(buf);
      break;
    case 9:
      return example_9_encoded(buf);
      break;
    case 10:
      return example_10_encoded(buf);
      break;
    case 11:
      return example_11_encoded(buf);
      break;

    default:
      return 0;
  }
}

void wikipedia_examples_encode(void) {
  for (uint8_t example = 1; example <= 11; example++) {
    uint8_t unencoded[300];
    uint8_t encoded[300];
    uint8_t buf[300];
    uint32_t encoded_length_expected = example_encoded(example, encoded);
    uint32_t decoded_length = example_unencoded(example, unencoded);
    struct cobs cobs;
    cobs_init(&cobs, buf, 300);

    uint32_t encoded_length;
    TEST_ASSERT_EQUAL(
        POSTCARD_SUCCESS,
        cobs_encode(&cobs, unencoded, decoded_length, &encoded_length));

    TEST_ASSERT_EQUAL_UINT32(encoded_length_expected, encoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(encoded, buf, encoded_length);
  }
  return;
}

void wikipedia_examples_decode(void) {
  for (uint8_t example = 1; example <= 11; example++) {
    uint8_t unencoded[300];
    uint8_t encoded[300];
    uint32_t encoded_length = example_encoded(example, encoded);
    uint32_t decoded_length_expected = example_unencoded(example, unencoded);
    struct cobs cobs;
    cobs_init(&cobs, encoded, encoded_length);
    uint32_t decoded_length;
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                      cobs_decode_in_place(&cobs, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, encoded, decoded_length);
  }
}

void encode_overflow(void) {
  uint8_t unencoded[300];
  uint8_t encoded[300];
  uint8_t buf[300];
  example_encoded(7, encoded);
  uint32_t decoded_length = example_unencoded(7, unencoded);
  struct cobs cobs;
  cobs_init(&cobs, buf, 200);

  uint32_t encoded_length;
  TEST_ASSERT_EQUAL(
      POSTCARD_COBS_ENCODE_OVERFLOW,
      cobs_encode(&cobs, unencoded, decoded_length, &encoded_length));

  TEST_ASSERT_EQUAL_UINT32(200, encoded_length);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(wikipedia_examples_encode);
  RUN_TEST(wikipedia_examples_decode);
  RUN_TEST(encode_overflow);
  return UNITY_END();
}