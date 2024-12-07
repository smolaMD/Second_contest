#include <algorithm>
#include <iostream>

void GetLIS(int *seq, int n, int *prev, int *pos, int *dp, int64_t *cnt) {
  dp[0] = -2147483648;
  int size = 0;
  for (int i = 0; i < n; ++i) {
    int target = seq[i];
    int j = static_cast<int>(std::lower_bound(dp, dp + size + 1, target) - dp);
    if (j > 0 && dp[j - 1] < target) {
      dp[j] = target;
      pos[j] = i;
      prev[i] = pos[j - 1];
      cnt[i] = 0;
      if (j == size + 1) {
        size++;
      }
    }
    cnt[i] = 1;
    for (int k = 0; k < i; ++k) {
      if (seq[k] < seq[i]) {
        cnt[i] += cnt[k];
        cnt[i] %= 1000000;
      }
    }
  }
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
  auto *cnt = new int64_t[n];
  std::fill(cnt, cnt + n, 0);
  GetLIS(seq, n, prev, pos, dp, cnt);
  int64_t res_cnt = 0;
  for (int i = 0; i < n; ++i) {
    res_cnt += cnt[i];
  }
  std::cout << res_cnt % 1000000 << "\n";

  delete[] prev;
  delete[] pos;
  delete[] dp;
  delete[] seq;
  delete[] cnt;
  return 0;
}
