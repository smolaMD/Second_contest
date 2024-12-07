#include <algorithm>
#include <iostream>

int FormingBackpack(const int *mass, const int *price, int n, int max_mass, int **dp, int *ans) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= max_mass; ++j) {
      if (mass[i] <= j) {
        dp[i][j] = std::max(dp[i - 1][j], price[i] + dp[i - 1][j - mass[i]]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  int ind = 0;
  int k = n;
  int tmp_w = max_mass;
  while (k > 0 && tmp_w > 0) {
    if (dp[k][tmp_w] != dp[k - 1][tmp_w]) {
      ans[ind++] = k;
      tmp_w -= mass[k];
    }
    --k;
  }
  return ind;
}

int main() {
  int n = 0;
  int max_mass = 0;
  std::cin >> n >> max_mass;
  int *mass = new int[n + 1];
  int *price = new int[n + 1];
  mass[0] = 0;
  price[0] = 0;
  for (int i = 1; i <= n; ++i) {
    std::cin >> mass[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> price[i];
  }
  int **dp = new int *[n + 1];
  for (int i = 0; i <= n; ++i) {
    dp[i] = new int[max_mass + 1]{};
  }
  int *ans = new int[n];
  int size = FormingBackpack(mass, price, n, max_mass, dp, ans);
  for (int i = size - 1; i >= 0; --i) {
    std::cout << ans[i] << "\n";
  }
  for (int i = 0; i <= n; ++i) {
    delete[] dp[i];
  }

  delete[] dp;
  delete[] mass;
  delete[] price;
  delete[] ans;
  return 0;
}
