#include <algorithm>
#include <iostream>

struct Team {
  int num = 0;
  int tasks = 0;
  int time = 0;
  Team() : num(0), tasks(0), time(0) {
  }
  Team(int num, int tasks, int time) : num(num), tasks(tasks), time(time) {
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  auto *teams = new Team[n]();
  for (int i = 0; i < n; ++i) {
    int tasks = 0;
    int time = 0;
    std::cin >> tasks >> time;
    teams[i] = Team(i + 1, tasks, time);
  }
  std::sort(teams, teams + n, [](const Team &a, const Team &b) {
    if (a.tasks == b.tasks) {
      if (a.time == b.time) {
        return a.num < b.num;
      }
      return a.time < b.time;
    }
    return a.tasks > b.tasks;
  });

  for (int i = 0; i < n; ++i) {
    std::cout << teams[i].num << "\n";
  }
  delete[] teams;
  return 0;
}
