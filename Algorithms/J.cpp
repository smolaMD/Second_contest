#include <iostream>

void MoveStudent(int &res_x, int &res_y, int x, int y, int h, int w, int **nums) {
  bool has_way = true;
  while (has_way) {
    int max_num = 0;
    int cnt = 0;
    int tmp_x = 0;
    int tmp_y = 0;
    for (int i = res_x; i < res_x + h; ++i) {
      for (int j = res_y; j < res_y + w; ++j) {
        if ((i < x && j < y) && nums[i][j] > max_num) {
          max_num = nums[i][j];
          tmp_x = i;
          tmp_y = j;
          ++cnt;
        }
      }
    }
    if (cnt == 0 || (tmp_x == res_x && tmp_y == res_y)) {
      break;
    }
    res_x = tmp_x;
    res_y = tmp_y;
  }
}

int main() {
  int x = 0;
  int y = 0;
  std::cin >> x >> y;
  int h = 0;
  int w = 0;
  std::cin >> h >> w;
  int **nums = new int *[x];
  for (int i = 0; i < x; ++i) {
    nums[i] = new int[y];
  }
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      std::cin >> nums[i][j];
    }
  }
  int res_x = 0;
  int res_y = 0;
  MoveStudent(res_x, res_y, x, y, h, w, nums);
  std::cout << res_x << " " << res_y;

  for (int i = 0; i < x; ++i) {
    delete[] nums[i];
  }
  delete[] nums;
  return 0;
}
