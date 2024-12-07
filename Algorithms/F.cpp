#include <cstring>
#include <iostream>
#include <algorithm>

int LevDist(const char *str1, int size1, const char *str2, int size2, int **dp) {
  for (int i = 0; i <= size1; ++i) {
    dp[i][0] = i;
  }
  for (int j = 0; j <= size2; ++j) {
    dp[0][j] = j;
  }
  for (int i = 1; i <= size1; ++i) {
    for (int j = 1; j <= size2; ++j) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1});
      }
    }
  }

  return dp[size1][size2];
}

int main() {
  char str1[5001];
  char str2[5001];
  std::cin >> str1 >> str2;
  int size1 = static_cast<int>(strlen(str1));
  int size2 = static_cast<int>(strlen(str2));
  int **dp = new int *[size1 + 1];
  for (int i = 0; i < size1 + 1; ++i) {
    dp[i] = new int[size2 + 1];
  }
  std::cout << LevDist(str1, size1, str2, size2, dp);

  for (int i = 0; i < size1 + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return 0;
}
