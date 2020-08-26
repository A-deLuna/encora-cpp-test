#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdio.h>
#include <optional>


// Finds a subset of I with maximum sum that is less than or equal to T.
//
// param T in:  Target for maximum sum of subset elements.
// param I in:  Initial set of elements.
// param M out: Subset of elements in answer. Empty if no answer found or I == 0
//              (empty subset is the answer).
// param S out: Total sum of elements in M. Zero when no answer found. or I == 0.
//
// Problem is known in CS literature as the 'subset sum' problem.
//
// Solution uses dynamic programming. For all integers j from 1 to T, compute 
// whether the subset I[0..i] contains a sum equal to j.
void find_largest_sum(const uint32_t T, const std::vector<uint32_t> &I,
    std::vector<uint32_t>& M, uint32_t& S) {
  M.clear();
  std::vector<std::vector<bool>> dp(I.size()+1, std::vector<bool>(T+1, false));

  // Base case, we can always take an empty set to sum up to zero.
  for (int i = 0; i <= I.size(); i++) {
    dp[i][0] = true;
  }

  std::optional<int32_t> maxSoFar;
  for (int i = 1; i <= I.size(); i++) {
    for (int j = 1; j <= T; j++) {
      if (I[i-1] > j) {
        dp[i][j] = dp[i-1][j];
      }
      if (I[i-1] <= j) {
        dp[i][j] = dp[i-1][j] || dp[i-1][j-I[i-1]];
        if (dp[i][j]) {
          // keep track of the greatest j <= T for which we have an answer.
          maxSoFar = j;
        }
      }
    }
  }
  if (!maxSoFar.has_value() || maxSoFar.value() == 0)  {
    S = 0;
    return;
  }   

  S = maxSoFar.value();
  int current = maxSoFar.value();
  // Find the path by incrementally 
  while (current != 0) {
    for (int i = 1; i < I.size() +1; i++) {
      if (dp[i][current]) {
        M.push_back(I[i-1]);
        current -= I[i-1];
        break;
      }
    }
  }
}

void printVector(const std::vector<uint32_t>& v) {
  for (const uint32_t a : v) {
    std::cout << a << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  std::vector<uint32_t> ans;
  uint32_t S;
  find_largest_sum(11, {1,2,3,4,5,6,7}, ans, S);
  std::cout << "answer:";
  printVector(ans);
  find_largest_sum(10, {2, 3, 5, 6, 8, 10}, ans, S);
  std::cout << "answer:";
  printVector(ans);
  find_largest_sum(15, {2, 3, 5, 6, 8, 10}, ans, S);
  std::cout << "answer:";
  printVector(ans);
  find_largest_sum(10, {0,0,0}, ans, S);
  std::cout << "answer:";
  printVector(ans);
  find_largest_sum(5, {10,20,30}, ans, S);
  std::cout << "answer:";
  printVector(ans);
  //find_largest_sum(1000, {1,2,3,4,5,6,7}, ans, S);
}
