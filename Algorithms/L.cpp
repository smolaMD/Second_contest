#include <cstring>
#include <iostream>

void GetLCS(const char *str1, const char *str2, int str_len, int &size, int **dp) {
  for (int i = 1; i <= str_len; ++i) {
    for (int j = 1; j <= str_len; ++j) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  int i = str_len;
  int j = str_len;
  while (i > 0 && j > 0) {
    if (str1[i - 1] == str2[j - 1]) {
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

void InvertStr(char *str, int str_len, char *inverted_str) {
  for (int i = 0; i < str_len; ++i) {
    inverted_str[i] = str[str_len - 1 - i];
  }
}

int main() {
  char str[10000];
  std::cin >> str;
  int str_len = static_cast<int>(strlen(str));
  char *inverted_str = new char[str_len];
  InvertStr(str, str_len, inverted_str);
  int size = 0;
  int **dp = new int *[str_len + 1];
  for (int i = 0; i < str_len + 1; ++i) {
    dp[i] = new int[str_len + 1];
  }
  GetLCS(str, inverted_str, str_len, size, dp);
  std::cout << str_len - size;
  for (int i = 0; i < str_len + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] inverted_str;
  return 0;
}
