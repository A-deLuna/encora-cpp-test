#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <limits>
#include <stdexcept>
#include "definitions.h"

// Adds two integers using bitwise operators.
// Throws overflow_error on overflows.
//
// Assumes that negative integers use two's complement. This is not guaranteed
// by the standard.
// Assumes that bytes are 8 bits long, also not guaranteed by the standard.
int add(int a, int b) {
  uint8_t bitCount = sizeof(int) * 8;
  int result = 0;

  uint8_t carry = 0;

  for (uint8_t i = 0; i < bitCount; i++) {
    uint8_t addition = carry + ((a>>i) & 1) + ((b>>i) & 1);
    carry = (addition & 0b10) >> 1;
    result |= ((addition & 1) << i);
  }

  // Overflow is not possible when first bit is different in arguments.
  if ((a >> (bitCount-1)) != (b >> (bitCount-1))) {
    return result;
  }

  // Overflow occurs when first bit is different in result and arguments.
  if ((a >> (bitCount-1)) != (result  >> (bitCount-1))) {
    throw std::overflow_error{"Addition overflow"};
  }

  return result;
}
