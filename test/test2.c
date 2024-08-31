#include "../inc/postcard.h"
#include "Unity/src/unity.h"

void setUp(void) {}

void tearDown(void) {
  // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) { int c = sum(5, 7); }

void test_function_should_doAlsoDoBlah(void) {
  // more test stuff
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_function_should_doBlahAndBlah);
  RUN_TEST(test_function_should_doAlsoDoBlah);
  return UNITY_END();
}