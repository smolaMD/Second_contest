#ifndef ARRAY_TRAITS_IMPLEMENTED
#define ARRAY_TRAITS_IMPLEMENTED

#include<iostream>

template<typename T, size_t N>
class Array {
public:
  T array[N];

  T &operator[](size_t i) {
    return array[i];
  }
  
  const T &operator[](size_t i) const {
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

  size_t Size() const {
    return N;
  }

  bool Empty() const {
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

  size_t GetSize(const T &) {
    return 0;
  }

};

template <class T>
size_t GetSize(const T&) {
  return 0;
}

template <class T, size_t Size>
size_t GetSize(const T (&)[Size]) {
  return Size;
}

template <class T>
size_t GetRank(const T&) {
  return 0;
}

template <class T, size_t Size>
size_t GetRank(const T (&)[Size]) {
  return 1 + GetRank(T{});
}

template <class T>
size_t GetNumElements(const T&) {
  return 1;
}

template <class T, size_t Size>
size_t GetNumElements(const T (&)[Size]) {
  return Size * GetNumElements(T{});
}

#endif
