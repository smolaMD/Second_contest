#include <algorithm>
#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int *arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  int k = 0;
  std::cin >> k;
  std::cout << std::count(arr, arr + n, k);
  delete[] arr;
  return 0;
}
