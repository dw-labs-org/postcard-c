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

uint32_t example_encoded_all(uint8_t *buf) {
  uint32_t size = 0;
  for (uint8_t i = 1; i <= 11; i++) {
    size += example_encoded(i, buf + size);
  }
  return size;
}

uint32_t example_unencoded_all(uint8_t *buf) {
  uint32_t size = 0;
  for (uint8_t i = 1; i <= 11; i++) {
    size += example_unencoded(i, buf + size);
  }
  return size;
}

void wikipedia_examples_encode(void) {
  for (uint8_t example = 1; example <= 11; example++) {
    uint8_t unencoded[300];
    uint8_t encoded[300];
    uint8_t buf[300];
    uint32_t encoded_length_expected = example_encoded(example, encoded);
    uint32_t decoded_length = example_unencoded(example, unencoded);
    struct cobs_encoder cobs_encoder;
    cobs_encoder_init(&cobs_encoder, buf, 300);

    uint32_t encoded_length;
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                      cobs_encoder_frame(&cobs_encoder, unencoded,
                                         decoded_length, &encoded_length));

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
    struct cobs_decoder cobs_decoder;
    cobs_decoder_init(&cobs_decoder, encoded, 300, encoded_length);
    uint32_t decoded_length;
    uint8_t out[300];
    TEST_ASSERT_EQUAL(
        POSTCARD_SUCCESS,
        cobs_decoder_frame(&cobs_decoder, out, 300, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, out, decoded_length);
  }
}

void wikipedia_examples_decode_in_place(void) {
  for (uint8_t example = 1; example <= 11; example++) {
    uint8_t unencoded[300];
    uint8_t encoded[300];
    uint32_t encoded_length = example_encoded(example, encoded);
    uint32_t decoded_length_expected = example_unencoded(example, unencoded);
    struct cobs_decoder cobs_decoder;
    TEST_ASSERT_EQUAL(
        POSTCARD_SUCCESS,
        cobs_decoder_init(&cobs_decoder, encoded, 300, encoded_length));
    uint32_t decoded_length;
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS, cobs_decoder_frame_in_place(
                                            &cobs_decoder, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, encoded + 1, decoded_length);
  }
}

void wikipedia_examples_decode_sequential(void) {
  uint8_t unencoded[300];
  uint8_t encoded[300];
  struct cobs_decoder cobs_decoder;
  TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                    cobs_decoder_init(&cobs_decoder, encoded, 300, 0));

  for (uint8_t example = 1; example <= 11; example++) {
    uint8_t buf[300];
    uint32_t encoded_length = example_encoded(example, buf);
    uint32_t decoded_length_expected = example_unencoded(example, unencoded);
    uint32_t decoded_length;
    TEST_ASSERT_EQUAL(encoded_length, cobs_decoder_place_bytes(
                                          &cobs_decoder, buf, encoded_length));

    TEST_ASSERT_EQUAL(
        POSTCARD_SUCCESS,
        cobs_decoder_frame(&cobs_decoder, buf, 300, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, buf, decoded_length);
  }
}

void wikipedia_examples_decode_sequential_partial(void) {
  uint8_t unencoded[2500];
  uint8_t encoded[2500];
  uint8_t dest[2500];
  uint8_t buf[100];
  uint32_t encoded_length = example_encoded_all(encoded);
  uint32_t decoded_length_expected = example_unencoded_all(unencoded);

  struct cobs_decoder cobs_decoder;
  TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                    cobs_decoder_init(&cobs_decoder, buf, 100, 0));
  uint8_t *src_ptr = encoded;
  uint8_t *dest_ptr = dest;
  uint8_t frames = 0;
  uint32_t loop_count = 0;
  char msg[40];
  while (true) {
    loop_count++;
    // try decode
    uint32_t written = 0;
    postcard_return_t result =
        cobs_decoder_frame(&cobs_decoder, dest_ptr, 2500, &written);
    dest_ptr += written;
    if (result == POSTCARD_SUCCESS) {
      // found a frame
      frames++;

      if (frames == 11) {
        break;
      }
    } else if (result == POSTCARD_COBS_DECODE_DATA_END) {
      // needs more data for frame
      uint32_t written = cobs_decoder_place_bytes(&cobs_decoder, src_ptr, 10);
      if (written == 0) {
        TEST_ABORT();
      }
      src_ptr += written;
      continue;
    } else {
      TEST_ASSERT_EQUAL(POSTCARD_SUCCESS, result);
    }
  }

  TEST_ASSERT_EQUAL(11, frames);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, dest, decoded_length_expected);
}

void wikipedia_examples_decode_in_place_sequential(void) {
  uint8_t unencoded[300];
  uint8_t encoded[300];
  struct cobs_decoder cobs_decoder;
  TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                    cobs_decoder_init(&cobs_decoder, encoded, 300, 0));

  for (uint8_t example = 1; example <= 11; example++) {
    uint8_t buf[300];
    uint32_t encoded_length = example_encoded(example, buf);
    uint32_t decoded_length_expected = example_unencoded(example, unencoded);
    uint32_t decoded_length;
    TEST_ASSERT_EQUAL(encoded_length, cobs_decoder_place_bytes(
                                          &cobs_decoder, buf, encoded_length));

    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS, cobs_decoder_frame_in_place(
                                            &cobs_decoder, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    uint8_t frame[300];
    TEST_ASSERT_EQUAL_UINT32(
        decoded_length_expected,
        cobs_decoder_fetch_frame(&cobs_decoder, frame, 300));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, frame, decoded_length);
  }
}

void encode_overflow(void) {
  uint8_t unencoded[300];
  uint8_t encoded[300];
  uint8_t buf[300];
  example_encoded(7, encoded);
  uint32_t decoded_length = example_unencoded(7, unencoded);
  struct cobs_encoder cobs_encoder;
  cobs_encoder_init(&cobs_encoder, buf, 200);

  uint32_t encoded_length;
  TEST_ASSERT_EQUAL(POSTCARD_COBS_ENCODE_OVERFLOW,
                    cobs_encoder_frame(&cobs_encoder, unencoded, decoded_length,
                                       &encoded_length));
  // Should be 1 as write_bytes shortcircuits overflows after writing initial 0
  TEST_ASSERT_EQUAL_UINT32(1, encoded_length);
}

void decode_overread(void) {
  // uint8_t unencoded[300];
  uint8_t encoded[300];
  uint32_t encoded_length = example_encoded(8, encoded);
  struct cobs_decoder cobs_decoder;
  TEST_ASSERT_EQUAL(POSTCARD_COBS_DECODE_WRITTEN_OVERFLOW,
                    cobs_decoder_init(&cobs_decoder, encoded,
                                      encoded_length - 50, encoded_length));

  // uint32_t written;
  // TEST_ASSERT_EQUAL(
  //     POSTCARD_COBS_DECODE_DATA_END,
  //     cobs_decoder_frame(&cobs_decoder, unencoded, 300, &written));
  // TEST_ASSERT_EQUAL(encoded_length - 50, cobs_decoder.next -
  // cobs_decoder.buf);
}

void decode_overflow(void) {
  uint8_t unencoded[300];
  uint8_t encoded[300];
  uint32_t encoded_length = example_encoded(8, encoded);
  struct cobs_decoder cobs_decoder;
  cobs_decoder_init(&cobs_decoder, encoded, 300, encoded_length);

  uint32_t written;
  TEST_ASSERT_EQUAL(
      POSTCARD_COBS_DECODE_OVERFLOW,
      cobs_decoder_frame(&cobs_decoder, unencoded, 200, &written));
  TEST_ASSERT_EQUAL(200, written);
}

void decode_invalid_zero(void) {
  uint8_t unencoded[300];
  uint8_t encoded[300];
  uint32_t encoded_length = example_encoded(4, encoded);
  struct cobs_decoder cobs_decoder;
  cobs_decoder_init(&cobs_decoder, encoded, 300, encoded_length);
  encoded[4] = 0;
  uint32_t written;
  TEST_ASSERT_EQUAL(
      POSTCARD_COBS_DECODE_INVALID_ZERO,
      cobs_decoder_frame(&cobs_decoder, unencoded, 300, &written));
  TEST_ASSERT_EQUAL(3, written);
}

void decode_leading_zero(void) {
  uint8_t unencoded[300];
  uint8_t encoded[300];
  uint32_t encoded_length = example_encoded(4, encoded);
  struct cobs_decoder cobs_decoder;
  cobs_decoder_init(&cobs_decoder, encoded, 300, encoded_length);
  encoded[0] = 0;
  uint32_t written;
  TEST_ASSERT_EQUAL(
      POSTCARD_COBS_DECODE_LEADING_ZERO,
      cobs_decoder_frame(&cobs_decoder, unencoded, 300, &written));
  TEST_ASSERT_EQUAL(0, written);
}
// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(wikipedia_examples_encode);
  RUN_TEST(wikipedia_examples_decode);
  RUN_TEST(wikipedia_examples_decode_in_place);
  RUN_TEST(wikipedia_examples_decode_sequential);
  RUN_TEST(wikipedia_examples_decode_sequential_partial);
  RUN_TEST(wikipedia_examples_decode_in_place_sequential);
  RUN_TEST(encode_overflow);
  RUN_TEST(decode_overread);
  RUN_TEST(decode_overflow);
  RUN_TEST(decode_invalid_zero);
  RUN_TEST(decode_leading_zero);
  return UNITY_END();
}