#include <iostream>
#include <algorithm>

void GetLIS(const int *seq, int n, int *dp, int *prev_dp, int *inc_seq, int &size) {
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (seq[j] < seq[i] && dp[i] < dp[j] + 1) {
        dp[i] = dp[j] + 1;
        prev_dp[i] = j;
      }
    }
  }
  int ind = 0;
  for (int i = 0; i < n; ++i) {
    if (dp[i] > size) {
      size = dp[i];
      ind = i;
    }
  }
  int j = 0;
  for (int i = ind; i != -1; i = prev_dp[i]) {
    inc_seq[j] = seq[i];
    ++j;
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  int *seq = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> seq[i];
  }
  int *dp = new int[n];
  std::fill(dp, dp + n, 1);
  int *prev_dp = new int[n];
  std::fill(prev_dp, prev_dp + n, -1);
  int size = 0;
  int *inc_seq = new int[n];
  GetLIS(seq, n, dp, prev_dp, inc_seq, size);
  for (int i = size - 1; i >= 0; --i) {
    std::cout << inc_seq[i] << " ";
  }
  delete[] seq;
  delete[] dp;
  delete[] prev_dp;
  delete[] inc_seq;
  return 0;
}
