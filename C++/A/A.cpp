#ifndef ARRAY
#define ARRAY
#include<iostream>

template<typename T, size_t N>
class Array {
public:
  T* array[N];

  T &operator[](size_t i) {
    return array[i];
  }

  T &Front() {
    return array[0];
  }

  const T &Front() const {
    return array[0];
  }

  T &Back() {
    return array[N - 1];
  }

  const T &Back() const {
    return array[N - 1];
  }

  T *Data() {
    return array;
  }

  const T *Data() const {
    return array;
  }

  size_t Size() {
    return N;
  }

  bool Empty() {
    return (N == 0);
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      array[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    T tmp;
    for (size_t i = 0; i < N; ++i) {
      tmp = array[i];
      array[i] = other[i];
      other[i] = tmp;
    }
  }
};

#endif
