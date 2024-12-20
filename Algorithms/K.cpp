#include <iostream>

void GetLCIS(int n, const int *seq1, int m, const int *seq2, int64_t **dp) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (seq1[i] == seq2[j]) {
        dp[i][j] = 1;
        for (int k = 0; k < i; ++k) {
          if (dp[k][j] + 1 > dp[i][j] && seq1[k] < seq1[i]) {
            dp[i][j] = dp[k][j] + 1;
          }
        }
      } else if (j > 0) {
        dp[i][j] = dp[i][j - 1];
      }
    }
  }
}

void FormingAns(int n, int m, const int *seq1, int64_t **dp, int64_t &size, int *ans) {
  int i = -1;
  int j = m - 1;
  for (int k = 0; k < n; ++k) {
    if (dp[k][j] > size) {
      size = dp[k][j];
      i = k;
    }
  }
  if (i == -1) {
    return;
  }
  ans[0] = seq1[i];
  int tmp_size = 1;
  while (dp[i][j] > 1) {
    if (dp[i][j] == dp[i][j - 1]) {
      --j;
    } else {
      for (int k = i - 1; k >= 0; --k) {
        if (seq1[k] < seq1[i] && dp[k][j] + 1 == dp[i][j]) {
          ans[tmp_size] = seq1[k];
          ++tmp_size;
          i = k;
          --j;
          break;
        }
      }
    }
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  int *seq1 = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> seq1[i];
  }
  int m = 0;
  std::cin >> m;
  int *seq2 = new int[m];
  for (int i = 0; i < m; ++i) {
    std::cin >> seq2[i];
  }
  auto **dp = new int64_t *[n];
  for (int i = 0; i < n; ++i) {
    dp[i] = new int64_t[m]{};
  }
  GetLCIS(n, seq1, m, seq2, dp);
  int64_t size = 0;
  int *ans = new int[n + m];
  FormingAns(n, m, seq1, dp, size, ans);
  std::cout << size << '\n';
  for (int64_t i = size - 1; i >= 0; --i) {
    std::cout << ans[i] << " ";
  }
  delete[] seq1;
  delete[] seq2;
  for (int i = 0; i < n; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] ans;
  return 0;
}
