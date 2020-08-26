#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdio.h>
#include <optional>
#include "definitions.h"


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
  // Traditional implementation uses booleans to indicate whether subset
  // adds up to j. We can optimize the path finding step by additionally storing
  // an offset to the first index i where I[0..i] sums up to j. The element in
  // this first index i is guaranteed to be part of a set that adds up to j.
  // Here -1 is the same as false and any other number is true.
  std::vector<std::vector<int>> dp(I.size()+1, std::vector<int>(T+1, -1));

  // Base case, we can always take an empty set to sum up to zero.
  for (size_t i = 0; i <= I.size(); i++) {
    dp[i][0] = 0;
  }

  std::optional<int32_t> maxSoFar;
  for (size_t i = 1; i <= I.size(); i++) {
    for (size_t j = 1; j <= T; j++) {
      if (I[i-1] > j) {
        dp[i][j] = dp[i-1][j] == -1 ? -1 : dp[i-1][j]+1;

      }
      if (I[i-1] <= j) {
        if (dp[i-1][j] != -1) {
          dp[i][j] = dp[i-1][j]+1;
        } else if (dp[i-1][j-I[i-1]] != -1) {
          dp[i][j] = 0;
        }
        if (dp[i][j] != -1) {
          // keep track of the greatest j <= T for which we have an answer.
          maxSoFar = j;
        }
      }
    }
  }
  // Could not find a subset in I with sum <= T.
  if (!maxSoFar.has_value() || maxSoFar.value() == 0)  {
    S = 0;
    return;
  }   

  S = maxSoFar.value();
  int current = maxSoFar.value();
  
  // All elements at position [I.size()][j] contain an offset to the 
  // first index where the sum of elements in subset [0..i] equal to j.
  // This element is guaranteed to be part of the path.
  while (current != 0) {
    int offset = dp[I.size()][current];
    int idx = I.size() - offset;
    M.push_back(I[idx-1]);
    current -= I[idx-1];
  }
}

