#include "definitions.h"
#include <limits>
#include <stdexcept>
#include <iostream>


void testBitwiseAdd() {
  struct TestCase {
    int a;
    int b;
    int result;
    bool overflow;
  };
  // I know designated initializers are not part of the standard yet...
  // but I feel they make the code a lot better and they're supported by 
  // clang and gcc.
  TestCase cases[] = {
    {.a =   0, .b =  0, .result =  0, .overflow = false},
    {.a =   1, .b =  1, .result =  2, .overflow = false},
    {.a =  -1, .b = -1, .result = -2, .overflow = false},
    {.a =  -1, .b =  1, .result =  0, .overflow = false},
    {.a = -10, .b =  5, .result = -5, .overflow = false},
    {.a =  10, .b = -5, .result =  5, .overflow = false},

    {.a = std::numeric_limits<int>::max(), .b = 1, .overflow = true},
    {.a = std::numeric_limits<int>::min(), .b = -1, .overflow = true},
  };

  int failedCases = 0;
  for (const TestCase& c: cases) {
    bool threw = false;
    int result = 0;
    try {
      result = add(c.a, c.b);
    }
    catch(const std::overflow_error& e) {
      threw = true;
    }
    if (c.overflow && !threw) {
      std::cout << "error on test case add(" << c.a << ", " << c.b << ");\n";
      std::cout << "expected exception and did not throw.\n";
      failedCases++;
      continue;
    }
    if (!c.overflow && threw) {
      std::cout << "error on test case add(" << c.a << ", " << c.b << ");\n";
      std::cout << "received exception but did not expect any.\n";
      failedCases++;
      continue;
    }

    if (result != c.result) {
      std::cout << "result of add(" << c.a << ", " << c.b << ") was " << result << "\n";
      std::cout << "but expected " << c.result << "\n";
      failedCases++;
      continue;
    }
  }
  if (failedCases == 0) {
    std::cout << "bitwise add: All cases succeeded\n";
  }
  else {
    std::cout << "bitwise add: failed a total of " << failedCases << " cases\n";
  }
}

void testFindSum() {
  struct TestCase {
    uint32_t T;
    std::vector<uint32_t> I;
    bool emptySet;
    uint32_t S;
  };

  std::vector<uint32_t> thousandOnes(1000, 1);
  std::vector<TestCase> cases = {
    {.T = 11, .I = {1,2,3,4,5,6,7}, .emptySet = false , .S= 11},
    {.T = 7, .I = {2,  9, 1, 5}, .emptySet = false , .S= 7}, 
    {.T = 5, .I = {10,20}, .emptySet = true , .S= 0},
    {.T = 40, .I = {10,20}, .emptySet = false , .S= 30}, 
    {.T = 10, .I = {1,1,1,1,1,1,1,1,1,1}, .emptySet = false , .S= 10}, 
    {.T = 0, .I = {1,1,1,1,1,1,1,1,1,1}, .emptySet = true , .S= 0}, 
    {.T = 10, .I = {}, .emptySet = true , .S= 0}, 
    {.T = 10, .I = {0,0,0}, .emptySet = true , .S= 0}, 
    {.T = 1000, .I = std::move(thousandOnes), .emptySet = false , .S= 1000}, 
  };
  int failedCases = 0;

  std::vector<uint32_t> M;
  uint32_t S;
  for (size_t i =0 ; i < cases.size(); i++) {
    const TestCase& c = cases[i];
    find_largest_sum(c.T, c.I, M, S);
    
    if (S != c.S) {
      std::cout << "Error in case " << i << " expected S to be " << c.S << "\n";
      std::cout << "but got " << S << "\n";
      failedCases++;
      continue;
    }
    uint32_t sum = 0;
    for (auto i : M) sum += i;

    if (sum != c.S) {
      std::cout << "Error in case " << i << " expected M sum to be " << c.S << "\n";
      std::cout << "but got " << sum << "\n";
      failedCases++;
      continue;
    }

    if (M.empty() && !c.emptySet) {
      std::cout << "Error in case " << i << " M is empty but was not expected\n";
      failedCases++;
      continue;
    }
    if (!M.empty() && c.emptySet) {
      std::cout << "Error in case " << i << " M is not but was expected to be\n";
      failedCases++;
      continue;
    }
  }
  if (failedCases == 0) {
    std::cout << "find_largest_sum: All cases succeeded\n";
  }
  else {
    std::cout << "find_largest_sum: failed a total of " << failedCases << " cases\n";
  }
}

int main() {
  testBitwiseAdd();
  testFindSum();
}
