#include <iostream>
#include <algorithm>

int main() {
  int n = 0;
  std::cin >> n;
  int *facs = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> facs[i];
  }
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int fac = 0;
    std::cin >> fac;
    std::cout << std::upper_bound(facs, facs + n, fac) - std::lower_bound(facs, facs + n, fac) << "\n";
  }
  delete[] facs;
  return 0;
}
