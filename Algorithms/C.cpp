#include <iostream>
#include <cstdint>

int main() {
  uint64_t n = 0;
  std::cin >> n;
  auto *dp = new uint64_t[n];
  dp[0] = 2;
  dp[1] = 3;
  for (int i = 2; i < n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  std::cout << dp[n - 1];
  delete[] dp;
  return 0;
}
