#ifndef QUANTITY
#define QUANTITY

template <int T, int L, int M> struct Quantity {
  double value = 0;
  Quantity() = default;
  Quantity(double value) : value(value) {} // NOLINT

  Quantity<T, L, M> &operator=(const Quantity<T, L, M> &other) {
    value = other.value;
    return *this;
  }

  Quantity<T, L, M> &operator+=(const Quantity<T, L, M> &other) {
    *this = *this + other;
    return *this;
  }

  Quantity<T, L, M> &operator-=(const Quantity<T, L, M> &other) {
    *this = *this - other;
    return *this;
  }

  template <class Scalar> Quantity<T, L, M> &operator*=(const Scalar &scalar) {
    this->value *= scalar;
    return *this;
  }

  template <class Scalar> Quantity<T, L, M> &operator/=(const Scalar &scalar) {
    this->value /= scalar;
    return *this;
  }
};

template <int T, int L, int M>
Quantity<T, L, M> operator+(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return Quantity<T, L, M>(param1.value + param2.value);
}

template <int T, int L, int M>
Quantity<T, L, M> operator-(const Quantity<T, L, M> &param1, const Quantity<T, L, M> &param2) {
  return Quantity<T, L, M>(param1.value - param2.value);
}

template <int T, int L, int M>
Quantity<T, L, M> operator+(const Quantity<T, L, M> &param) {
  return Quantity<T, L, M>(param.value);
}

template <int T, int L, int M>
Quantity<T, L, M> operator-(const Quantity<T, L, M> &param) {
  return Quantity<T, L, M>(-param.value);
}

template <int T1, int L1, int M1, int T2, int L2, int M2>
Quantity<T1 + T2, L1 + L2, M1 + M2>
operator*(const Quantity<T1, L1, M1> &param1, const Quantity<T2, L2, M2> &param2) {
  return Quantity<T1 + T2, L1 + L2, M1 + M2>(param1.value * param2.value);
}

template <int T1, int L1, int M1, int T2, int L2, int M2>
Quantity<T1 - T2, L1 - L2, M1 - M2>
operator/(const Quantity<T1, L1, M1> &param1, const Quantity<T2, L2, M2> &param2) {
  return Quantity<T1 - T2, L1 - L2, M1 - M2>(param1.value / param2.value);
}

template <int T, int L, int M, class Scalar>
Quantity<T, L, M> operator*(const Scalar &scalar, const Quantity<T, L, M> &param) {
  return Quantity<T, L, M>(scalar * param.value);
}

template <int T, int L, int M, class Scalar>
Quantity<T, L, M> operator*(const Quantity<T, L, M> &param, const Scalar &scalar) {
  return Quantity<T, L, M>(param.value * scalar);
}

template <int T, int L, int M, class Scalar>
Quantity<T, L, M> operator/(const Quantity<T, L, M> &param, const Scalar &scalar) {
  return Quantity<T, L, M>(param.value / scalar);
}

template <int T, int L, int M, class Scalar>
Quantity<-T, -L, -M> operator/(const Scalar &scalar, const Quantity<T, L, M> &param) {
  return Quantity<-T, -L, -M>(scalar / param.value);
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

#endif
