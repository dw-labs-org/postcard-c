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

void wikipedia_examples_encode_sequential(void) {
  uint8_t buf[300];
  struct cobs_encoder cobs_encoder;
  cobs_encoder_init(&cobs_encoder, buf, 300);
  uint32_t encode_index = 0;
  for (uint8_t example = 1; example <= 11; example++) {
    uint8_t unencoded[300];
    uint8_t encoded[300];

    uint32_t encoded_length_expected = example_encoded(example, encoded);
    uint32_t decoded_length = example_unencoded(example, unencoded);
    // check for space
    uint32_t space = cobs_encoder_free_space(&cobs_encoder);
    if (space < encoded_length_expected) {
      cobs_encoder_data_read(&cobs_encoder, encoded_length_expected - space);
      TEST_ASSERT(cobs_encoder_free_space(&cobs_encoder) ==
                  encoded_length_expected);
    }
    encode_index = cobs_encoder.next - cobs_encoder.buf;
    cobs_encoder_start_frame(&cobs_encoder);
    for (uint32_t i = 0; i < decoded_length; i++) {
      TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                        cobs_encoder_write_byte(&cobs_encoder, unencoded[i]));
    }
    cobs_encoder_end_frame(&cobs_encoder);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(encoded, buf + encode_index,
                                  encoded_length_expected);
  }
  return;
}

void wikipedia_examples_decode_circular(void) {
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
        cobs_decoder_frame_circular(&cobs_decoder, out, 300, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, out, decoded_length);
  }
}

void wikipedia_examples_decode_short(void) {
  for (uint8_t example = 1; example <= 7; example++) {
    uint8_t unencoded[300];
    uint8_t encoded[300];
    uint32_t encoded_length = example_encoded(example, encoded);
    uint32_t decoded_length_expected = example_unencoded(example, unencoded);
    uint8_t buf[256];
    struct cobs_decoder cobs_decoder;
    cobs_decoder_init(&cobs_decoder, buf, 256, 0);
    // write the encoded data to the buffer
    uint8_t *ptr;
    TEST_ASSERT_EQUAL(256, cobs_decoder_get_data_ptr(&cobs_decoder, &ptr));
    memcpy(ptr, encoded, encoded_length);
    // inform decoder of data written
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                      cobs_decoder_data_written(&cobs_decoder, encoded_length));
    // decode the cobs frame
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                      cobs_decoder_frame_in_place_short(&cobs_decoder));

    // get pointers to decode frame
    uint8_t *start;
    uint8_t *end;
    cobs_decoder_frame_ptrs(&cobs_decoder, &start, &end);
    // check length
    TEST_ASSERT_EQUAL(decoded_length_expected, end - start);
    // check adata
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, start, end - start);
  }
}

void wikipedia_examples_decode_short_sequential(void) {
  uint8_t buf[256];
  struct cobs_decoder cobs_decoder;
  cobs_decoder_init(&cobs_decoder, buf, 256, 0);

  for (uint8_t example = 1; example <= 7; example++) {
    uint8_t unencoded[300];
    uint8_t encoded[300];
    uint32_t encoded_length = example_encoded(example, encoded);
    uint32_t decoded_length_expected = example_unencoded(example, unencoded);

    // write the encoded data to the buffer
    uint8_t *ptr;

    uint32_t space = cobs_decoder_get_data_ptr(&cobs_decoder, &ptr);
    if (space < encoded_length) {
      TEST_ASSERT(cobs_decoder_shift_data(&cobs_decoder) != 0);
      TEST_ASSERT(cobs_decoder_get_data_ptr(&cobs_decoder, &ptr) >=
                  encoded_length);
    }
    memcpy(ptr, encoded, encoded_length);
    // inform decoder of data written
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                      cobs_decoder_data_written(&cobs_decoder, encoded_length));
    // decode the cobs frame
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                      cobs_decoder_frame_in_place_short(&cobs_decoder));

    // get pointers to decode frame
    uint8_t *start;
    uint8_t *end;
    cobs_decoder_frame_ptrs(&cobs_decoder, &start, &end);
    // check length
    TEST_ASSERT_EQUAL(decoded_length_expected, end - start);
    // check adata
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, start, end - start);
  }
}

void wikipedia_examples_decode_in_place_circular(void) {
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
    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS, cobs_decoder_frame_in_place_circular(
                                            &cobs_decoder, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, encoded + 1, decoded_length);
  }
}

void wikipedia_examples_decode_sequential_circular(void) {
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
    TEST_ASSERT_EQUAL(encoded_length, cobs_decoder_place_bytes_circular(
                                          &cobs_decoder, buf, encoded_length));

    TEST_ASSERT_EQUAL(
        POSTCARD_SUCCESS,
        cobs_decoder_frame_circular(&cobs_decoder, buf, 300, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, buf, decoded_length);
  }
}

void wikipedia_examples_decode_sequential_partial_circular(void) {
  uint8_t unencoded[2500];
  uint8_t encoded[2500];
  uint8_t dest[2500];
  uint8_t buf[100];
  example_encoded_all(encoded);
  uint32_t decoded_length_expected = example_unencoded_all(unencoded);

  struct cobs_decoder cobs_decoder;
  TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                    cobs_decoder_init(&cobs_decoder, buf, 100, 0));
  uint8_t *src_ptr = encoded;
  uint8_t *dest_ptr = dest;
  uint8_t frames = 0;
  uint32_t loop_count = 0;

  while (true) {
    loop_count++;
    // try decode
    uint32_t written = 0;
    postcard_return_t result =
        cobs_decoder_frame_circular(&cobs_decoder, dest_ptr, 2500, &written);
    dest_ptr += written;
    if (result == POSTCARD_SUCCESS) {
      // found a frame
      frames++;

      if (frames == 11) {
        break;
      }
    } else if (result == POSTCARD_COBS_DECODE_DATA_END) {
      // needs more data for frame
      uint32_t written =
          cobs_decoder_place_bytes_circular(&cobs_decoder, src_ptr, 10);
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

void wikipedia_examples_decode_in_place_sequential_circular(void) {
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
    TEST_ASSERT_EQUAL(encoded_length, cobs_decoder_place_bytes_circular(
                                          &cobs_decoder, buf, encoded_length));

    TEST_ASSERT_EQUAL(POSTCARD_SUCCESS, cobs_decoder_frame_in_place_circular(
                                            &cobs_decoder, &decoded_length));
    TEST_ASSERT_EQUAL_UINT32(decoded_length_expected, decoded_length);
    uint8_t frame[300];
    TEST_ASSERT_EQUAL_UINT32(
        decoded_length_expected,
        cobs_decoder_fetch_frame_circular(&cobs_decoder, frame, 300));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(unencoded, frame, decoded_length);
  }
}

void wikipedia_examples_decode_in_place_sequential_partial_circular(void) {
  uint8_t unencoded[2500];
  uint8_t encoded[2500];
  uint8_t dest[2500];
  uint8_t buf[300];
  example_encoded_all(encoded);
  uint32_t decoded_length_expected = example_unencoded_all(unencoded);

  struct cobs_decoder cobs_decoder;
  TEST_ASSERT_EQUAL(POSTCARD_SUCCESS,
                    cobs_decoder_init(&cobs_decoder, buf, 300, 0));
  uint8_t *src_ptr = encoded;
  uint8_t *dest_ptr = dest;
  uint8_t frames = 0;
  uint32_t loop_count = 0;

  while (true) {
    loop_count++;
    // try decode
    uint32_t written = 0;
    postcard_return_t result =
        cobs_decoder_frame_in_place_circular(&cobs_decoder, &written);
    if (result == POSTCARD_SUCCESS) {
      // found a frame
      frames++;
      // dump to dest
      dest_ptr +=
          cobs_decoder_fetch_frame_circular(&cobs_decoder, dest_ptr, 2500);

      if (frames == 11) {
        break;
      }
    } else if (result == POSTCARD_COBS_DECODE_DATA_END) {
      // needs more data for frame
      uint32_t written =
          cobs_decoder_place_bytes_circular(&cobs_decoder, src_ptr, 10);
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
      cobs_decoder_frame_circular(&cobs_decoder, unencoded, 200, &written));
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
      cobs_decoder_frame_circular(&cobs_decoder, unencoded, 300, &written));
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
      cobs_decoder_frame_circular(&cobs_decoder, unencoded, 300, &written));
  TEST_ASSERT_EQUAL(0, written);
}

void data_length(void) {
  uint8_t buf[100];
  struct cobs_decoder cobs_decoder;
  cobs_decoder_init(&cobs_decoder, buf, 100, 0);

  TEST_ASSERT_EQUAL(20,
                    cobs_decoder_place_bytes_circular(&cobs_decoder, buf, 20));
  uint8_t *ptr;
  TEST_ASSERT_EQUAL(79,
                    cobs_decoder_get_data_ptr_circular(&cobs_decoder, &ptr));
  TEST_ASSERT_EQUAL(20,
                    cobs_decoder_place_bytes_circular(&cobs_decoder, buf, 20));
  TEST_ASSERT_EQUAL(59,
                    cobs_decoder_get_data_ptr_circular(&cobs_decoder, &ptr));
  TEST_ASSERT_EQUAL(59,
                    cobs_decoder_place_bytes_circular(&cobs_decoder, buf, 60));
  TEST_ASSERT_EQUAL(0, cobs_decoder_get_data_ptr_circular(&cobs_decoder, &ptr));

  cobs_decoder_init(&cobs_decoder, buf, 100, 0);
  // grab test
  uint32_t encoded_length = example_1_encoded(buf);
  TEST_ASSERT_EQUAL(POSTCARD_SUCCESS, cobs_decoder_data_written_circular(
                                          &cobs_decoder, encoded_length));
  TEST_ASSERT_EQUAL(100 - 1 - encoded_length,
                    cobs_decoder_get_data_ptr_circular(&cobs_decoder, &ptr));
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(wikipedia_examples_encode);
  RUN_TEST(wikipedia_examples_encode_sequential);
  RUN_TEST(wikipedia_examples_decode_circular);
  RUN_TEST(wikipedia_examples_decode_short);
  RUN_TEST(wikipedia_examples_decode_short_sequential);
  RUN_TEST(wikipedia_examples_decode_in_place_circular);
  RUN_TEST(wikipedia_examples_decode_sequential_circular);
  RUN_TEST(wikipedia_examples_decode_sequential_partial_circular);
  RUN_TEST(wikipedia_examples_decode_in_place_sequential_circular);
  RUN_TEST(wikipedia_examples_decode_in_place_sequential_partial_circular);
  RUN_TEST(encode_overflow);
  RUN_TEST(decode_overread);
  RUN_TEST(decode_overflow);
  RUN_TEST(decode_invalid_zero);
  RUN_TEST(decode_leading_zero);
  RUN_TEST(data_length);
  return UNITY_END();
}