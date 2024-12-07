#include <algorithm>
#include <iostream>

int GetLIS(int *seq, int n, int *prev, int *pos, int *dp) {
  dp[0] = -2147483648;
  int size = 0;
  for (int i = 0; i < n; ++i) {
    int target = seq[i];
    int j = static_cast<int>(std::lower_bound(dp, dp + size + 1, target) - dp);

    if (j > 0 && dp[j - 1] < target) {
      dp[j] = target;
      pos[j] = i;
      prev[i] = pos[j - 1];
      if (j == size + 1) {
        size++;
      }
    }
  }

  return size;
}

int main() {
  int n = 0;
  std::cin >> n;
  int *seq = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> seq[i];
  }
  int *prev = new int[n];
  int *pos = new int[n + 1];
  int *dp = new int[n + 1];
  int size = GetLIS(seq, n, prev, pos, dp);
  std::cout << size;
  delete[] prev;
  delete[] pos;
  delete[] dp;
  delete[] seq;
  return 0;
}
