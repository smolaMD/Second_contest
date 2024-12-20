#include <iostream>
#include <algorithm>

int CountMultiplications(const int *sizes, int n, int **dp) {
  for (int i = 2; i < n; ++i) {
    for (int j = 0; j < n - i; ++j) {
      int ind = i + j;
      dp[j][ind] = 2147483647;
      for (int k = j + 1; k < ind; ++k) {
        dp[j][ind] = std::min(dp[j][ind], sizes[j] * sizes[k] * sizes[ind] + dp[j][k] + dp[k][ind]);
      }
    }
  }
  return dp[0][n - 1];
}

int main() {
  int n = 0;
  std::cin >> n;
  int *sizes = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> sizes[i];
  }
  int **dp = new int *[n];
  for (int i = 0; i < n; ++i) {
    dp[i] = new int[n]{};
  }
  std::cout << CountMultiplications(sizes, n, dp);

  for (int i = 0; i < n; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] sizes;
  return 0;
}
