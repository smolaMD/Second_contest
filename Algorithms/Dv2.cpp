#include <algorithm>
#include <iostream>

void Foo(int n, int m, int **&arr, int *first, int *second, int **pos) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (i == 0 || j == 0) {
        arr[i][j] = 0;
        continue;
      }
      if (first[i] == second[j]) {
        arr[i][j] = 1 + arr[i - 1][j - 1];
        pos[i][j] = 3;
      }
      if (arr[i][j] != std::max(arr[i][j], arr[i - 1][j])) {
        pos[i][j] = 1;
        arr[i][j] = arr[i - 1][j];
      }
      if (arr[i][j] != std::max(arr[i][j], arr[i][j - 1])) {
        pos[i][j] = 2;
        arr[i][j] = arr[i][j - 1];
      }
    }
  }
}

void GetPos(int **pos, const int *first, int i, int j, int *&ans, int &cnt) {
  while (pos[i][j] > 0) {
    if (pos[i][j] == 1) {
      --i;
      continue;
    }
    if (pos[i][j] == 2) {
      --j;
      continue;
    }
    if (pos[i][j] == 3) {
      ans[cnt] = first[i];
      ++cnt;
      --i;
      --j;
    }
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  int *first = new int[n + 1]{};
  for (int i = 1; i <= n; i++) {
    std::cin >> first[i];
  }
  int m = 0;
  std::cin >> m;
  int *second = new int[m + 1]{};
  for (int i = 1; i <= m; i++) {
    std::cin >> second[i];
  }
  int **arr = new int *[n + 1];
  int **pos = new int *[n + 1];
  for (int i = 0; i <= n; i++) {
    arr[i] = new int[m + 1]{};
    pos[i] = new int[m + 1]{};
  }
  int *ans = new int[n + m + 1]{};
  int cnt = 0;
  Foo(n, m, arr, first, second, pos);
  GetPos(pos, first, n, m, ans, cnt);
  // std::cout << arr[n][m] << '\n';
  for (int i = cnt - 1; i > -1; --i) {
    std::cout << ans[i] << ' ';
  }
  delete[] ans;
  for (int i = 0; i <= n; i++) {
    delete[] arr[i];
    delete[] pos[i];
  }
  delete[] arr;
  delete[] pos;
  delete[] first;
  delete[] second;
}
