#ifndef LITERALS_IMPLEMENTED
#define LITERALS_IMPLEMENTED

#include <iostream>

template <int T, int L, int M>
struct Quantity {
  double value = 0;

  Quantity<T, L, M> &operator+=(const Quantity<T, L, M> &other) {
    *this = *this + other;
    return *this;
  }

  Quantity<T, L, M> &operator-=(const Quantity<T, L, M> &other) {
    *this = *this - other;
    return *this;
  }

  template <class Scalar>
  Quantity<T, L, M> &operator*=(const Scalar &scalar) {
    this->value *= scalar;
    return *this;
  }

  template <class Scalar>
  Quantity<T, L, M> &operator/=(const Scalar &scalar) {
    this->value /= scalar;
    return *this;
  }
};

template <int T, int L, int M>
Quantity<T, L, M> operator+(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return {param1.value + param2.value};
}

template <int T, int L, int M>
Quantity<T, L, M> operator-(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return {param1.value - param2.value};
}

template <int T, int L, int M>
Quantity<T, L, M> operator+(const Quantity<T, L, M> &param) {
  return {param.value};
}

template <int T, int L, int M>
Quantity<T, L, M> operator-(const Quantity<T, L, M> &param) {
  return {-param.value};
}

template <int T1, int L1, int M1, int T2, int L2, int M2>
Quantity<T1 + T2, L1 + L2, M1 + M2> operator*(const Quantity<T1, L1, M1> &param1, const Quantity<T2, L2, M2> &param2) {
  return {param1.value * param2.value};
}

template <int T1, int L1, int M1, int T2, int L2, int M2>
Quantity<T1 - T2, L1 - L2, M1 - M2> operator/(const Quantity<T1, L1, M1> &param1, const Quantity<T2, L2, M2> &param2) {
  return {param1.value / param2.value};
}

template <int T, int L, int M, class Scalar>
Quantity<T, L, M> operator*(const Scalar &scalar, const Quantity<T, L, M> &param) {
  return {scalar * param.value};
}

template <int T, int L, int M, class Scalar>
Quantity<T, L, M> operator*(const Quantity<T, L, M> &param, const Scalar &scalar) {
  return {param.value * scalar};
}

template <int T, int L, int M, class Scalar>
Quantity<T, L, M> operator/(const Quantity<T, L, M> &param, const Scalar &scalar) {
  return {param.value / scalar};
}

template <int T, int L, int M, class Scalar>
Quantity<-T, -L, -M> operator/(const Scalar &scalar, const Quantity<T, L, M> &param) {
  return {scalar / param.value};
}

template <int T, int L, int M>
bool operator==(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return param1.value == param2.value;
}

template <int T, int L, int M>
bool operator!=(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return param1.value != param2.value;
}

template <int T, int L, int M>
bool operator<(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return param1.value < param2.value;
}

template <int T, int L, int M>
bool operator>(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return param1.value > param2.value;
}

template <int T, int L, int M>
bool operator<=(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return param1.value <= param2.value;
}

template <int T, int L, int M>
bool operator>=(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return param1.value >= param2.value;
}

using Time = Quantity<1, 0, 0>;
using Length = Quantity<0, 1, 0>;
using Mass = Quantity<0, 0, 1>;
using Speed = Quantity<-1, 1, 0>;
using Acceleration = Quantity<-2, 1, 0>;
using Force = Quantity<-2, 1, 1>;
using Energy = Quantity<-2, 2, 1>;

inline Time operator""_s(long double value) {
  return {static_cast<double>(value)};
}

inline Length operator""_m(long double value) {
  return {static_cast<double>(value)};
}

inline Mass operator""_kg(long double value) {
  return {static_cast<double>(value)};
}

inline Speed operator""_mps(long double value) {
  return {static_cast<double>(value)};
}

inline Acceleration operator""_mps2(long double value) {
  return {static_cast<double>(value)};
}

inline Force operator""_N(long double value) {
  return {static_cast<double>(value)};
}

inline Energy operator""_J(long double value) {
  return {static_cast<double>(value)};
}

#endif
