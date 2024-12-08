#include <iostream>
#include <deque>

struct Turple {
  int f = -1;
  int s = 0;
  int t = 0;
  int i = 0;

  bool operator<(const Turple &other) const {
    return f < other.f;
  }

  bool operator>=(const Turple &other) const {
    return f >= other.f;
  }

  bool operator==(const Turple &other) const {
    return f == other.f;
  }
};

struct MinQueue {
  std::deque<Turple> queue;
  std::deque<Turple> maxis;

  void Enqueue(Turple value) {
    Turple temp{};
    if (queue.empty()) {
      queue.push_back(value);
      maxis.push_back(value);
      return;
    }
    while (true) {
      if (maxis.empty()) {
        maxis.push_back(value);
        break;
      }
      temp = maxis.back();
      if (temp.f == -1 || temp >= value) {
        maxis.push_back(value);
        break;
      }
      maxis.pop_back();
    }
    queue.push_back(value);
  }

  void Dequeue() {
    if (queue.empty()) {
      return;
    }
    Turple temp = maxis.front();
    Turple q_front = queue.front();
    if (q_front == temp) {
      maxis.pop_front();
    }
    queue.pop_front();
  }

  Turple Front() {
    if (queue.empty()) {
      return {};
    }
    return queue.front();
  }

  int Size() {
    return static_cast<int>(queue.size());
  }

  void Clear() {
    while (!queue.empty()) {
      queue.pop_front();
    }
    while (!maxis.empty()) {
      maxis.pop_front();
    }
  }

  Turple Max() {
    if (maxis.empty()) {
      return {};
    }
    return maxis.front();
  }
};

void LastDays(int x, int y, int h, int w, MinQueue &mq, MinQueue &fq, Turple **&dp) {
  int now = 0;
  for (int i = 0; i < x; ++i) {
    dp[i] = new Turple[y]{};
    std::cin >> dp[i][0].f;
    dp[i][0].i = i;
    for (int j = 1; j < w; ++j) {
      std::cin >> now;
      Turple p(now, 0, j, i);
      mq.Enqueue(p);
      dp[i][j] = p;
    }
    for (int j = w; j < y; ++j) {
      std::cin >> now;
      Turple p(now, 0, j, i);
      dp[i][j] = p;
      if (mq.Size() != 0) {
        Turple max = mq.Max();
        dp[i][j - w].s = max.f;
        dp[i][j - w].t = max.t;
      }
      mq.Dequeue();
      mq.Enqueue(p);
    }
    for (int j = y - w; j < y; ++j) {
      if (mq.Size() != 0) {
        Turple max = mq.Max();
        dp[i][j].s = max.f;
        dp[i][j].t = max.t;
        mq.Dequeue();
      } else {
        dp[i][j].s = dp[i][j].f;
        dp[i][j].t = j;
      }
    }
    mq.Clear();
  }

  for (int j = 0; j < y; ++j) {
    // MinQueue mq;
    for (int i = 1; i < h; ++i) {
      mq.Enqueue({dp[i][j].s, dp[i][j].f, dp[i][j].t, dp[i][j].i});
      fq.Enqueue(dp[i][j]);
    }
    for (int i = h; i < x; ++i) {
      if (j != y - 1) {
        if (mq.Size() != 0 && dp[i - h][j].s < std::max(mq.Max().f, fq.Max().f)) {
          if (mq.Max().f > fq.Max().f) {
            dp[i - h][j].s = mq.Max().f;
            dp[i - h][j].t = mq.Max().t;
            dp[i - h][j].i = mq.Max().i;
          } else {
            dp[i - h][j].s = fq.Max().f;
            dp[i - h][j].t = j;
            dp[i - h][j].i = fq.Max().i;
          }
        }
      } else {
        if (fq.Size() != 0) {
          dp[i - h][j].s = fq.Max().f;
          dp[i - h][j].t = j;
          dp[i - h][j].i = fq.Max().i;
        }
      }
      mq.Enqueue({dp[i][j].s, dp[i][j].f, dp[i][j].t, dp[i][j].i});
      fq.Enqueue(dp[i][j]);
      mq.Dequeue();
      fq.Dequeue();
    }
    for (int i = x - h; i < x; ++i) {
      if (j == y - 1) {
        if (mq.Size() != 0) {
          dp[i][j].s = fq.Max().f;
          dp[i][j].t = j;
          dp[i][j].i = fq.Max().i;
        }
      } else {
        if (mq.Size() != 0 && dp[i][j].s < std::max(mq.Max().f, fq.Max().f)) {
          if (mq.Max().f > fq.Max().f) {
            dp[i][j].s = mq.Max().f;
            dp[i][j].t = mq.Max().t;
            dp[i][j].i = mq.Max().i;
          } else {
            dp[i][j].s = fq.Max().f;
            dp[i][j].t = j;
            dp[i][j].i = fq.Max().i;
          }
        }
      }
      mq.Dequeue();
      fq.Dequeue();
    }
    mq.Clear();
    fq.Clear();
  }
}

void LIS(Turple **&dp, int &i, int &j, int *&arr_i, int *&arr_j, int &cnt) {
  while (true) {
    if (dp[i][j].i == i && dp[i][j].t == j) {
      return;
    }
    int temp_i = 0;
    int temp_j = 0;
    temp_i = dp[i][j].i;
    temp_j = dp[i][j].t;
    i = temp_i;
    j = temp_j;
    arr_i[cnt] = i;
    arr_j[cnt] = j;
    cnt++;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int x = 0;
  int y = 0;
  std::cin >> x >> y;
  int w = 0;
  int h = 0;
  int cnt = 1;
  std::cin >> h >> w;
  auto **dp = new Turple *[x];
  MinQueue mq;
  MinQueue fq;
  int *arr_i = new int[x + y]{};
  int *arr_j = new int[y + x]{};
  int i = 0;
  int j = 0;
  LastDays(x, y, h, w, mq, fq, dp);
  LIS(dp, i, j, arr_i, arr_j, cnt);
  for (int f = 0; f < cnt; ++f) {
    std::cout << arr_i[f] << " " << arr_j[f] << '\n';
  }
  for (int r = 0; r < x; ++r) {
    delete[] dp[r];
  }
  delete[] arr_i;
  delete[] arr_j;
  delete[] dp;
}
