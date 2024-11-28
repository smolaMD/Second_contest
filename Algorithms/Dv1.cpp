#include <algorithm>
#include <iostream>

void GetLCS(const int *seq1, int n, const int *seq2, int m, int *com_seq, int &size, int **dp) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (seq1[i - 1] == seq2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  int i = n;
  int j = m;
  while (i > 0 && j > 0) {
    if (seq1[i - 1] == seq2[j - 1]) {
      com_seq[size] = seq1[i - 1];
      ++size;
      --i;
      --j;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      --i;
    } else {
      --j;
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
  int *com_seq = new int[n + m];
  int **dp = new int *[n + 1];
  for (int i = 0; i < n + 1; ++i) {
    dp[i] = new int[m + 1];
  }
  int size = 0;
  GetLCS(seq1, n, seq2, m, com_seq, size, dp);
  for (int i = size - 1; i >= 0; --i) {
    std::cout << com_seq[i] << " ";
  }
  for (int i = 0; i < n + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] seq1;
  delete[] seq2;
  delete[] com_seq;
  return 0;
}
