#ifndef QUANTITY_H
#define QUANTITY_H

template<int T, int L, int M>  // time length mass
struct Quantity {
  double value{};

  Quantity() = default;

  Quantity(double val) : value(val) {}  //NOLINT

  Quantity(const Quantity& q) : value(q.value) {}  //NOLINT

  Quantity<T, L, M> &operator=(const Quantity<T, L, M> &other) {
    if (this != &other) {
      value = other.value;
    }
    return *this;
  }
};

template<int T, int L, int M>
Quantity<T, L, M> operator+(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return Quantity<T, L, M>(q1.value + q2.value);
}

template<int T, int L, int M>
Quantity<T, L, M> operator-(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return Quantity<T, L, M>(q1.value - q2.value);
}

template<int T1, int L1, int M1, int T2, int L2, int M2>
Quantity<T1 + T2, L1 + L2, M1 + M2> operator*(const Quantity<T1, L1, M1> &q1, const Quantity<T2, L2, M2> &q2) {
  return Quantity<T1 + T2, L1 + L2, M1 + M2>(q1.value * q2.value);
}

template<int T1, int L1, int M1, int T2, int L2, int M2>
Quantity<T1 - T2, L1 - L2, M1 - M2> operator/(const Quantity<T1, L1, M1> &q1, const Quantity<T2, L2, M2> &q2) {
  return Quantity<T1 - T2, L1 - L2, M1 - M2>(q1.value / q2.value);
}

template<int T, int L, int M>
Quantity<T, L, M> operator*(const Quantity<T, L, M> &q1, const double &scalar) {
  return Quantity<T, L, M>(q1.value * scalar);
}

template<int T, int L, int M>
Quantity<T, L, M> operator*(const double &scalar, const Quantity<T, L, M> &q1) {
  return Quantity<T, L, M>(q1.value * scalar);
}

template<int T, int L, int M>
Quantity<T, L, M> operator/(const Quantity<T, L, M> &q1, const double &scalar) {
  return Quantity<T, L, M>(q1.value / scalar);
}

template<int T, int L, int M>
Quantity<-T, -L, -M> operator/(const double &scalar, const Quantity<T, L, M> &q1) {
  return Quantity<-T, -L, -M>(scalar / q1.value);
}

template<int T, int L, int M>
Quantity<T, L, M> &operator+=(Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  q1.value += q2.value;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> &operator-=(Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  q1.value -= q2.value;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> &operator*=(Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  q1.value *= q2.value;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> &operator/=(Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  q1.value /= q2.value;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> &operator+=(Quantity<T, L, M> &q1, const double &scalar) {
  q1.value += scalar;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> &operator-=(Quantity<T, L, M> &q1, const double &scalar) {
  q1.value -= scalar;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> &operator*=(Quantity<T, L, M> &q1, const double &scalar) {
  q1.value *= scalar;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> &operator/=(Quantity<T, L, M> &q1, const double &scalar) {
  q1.value /= scalar;
  return q1;
}

template<int T, int L, int M>
Quantity<T, L, M> operator+(const Quantity<T, L, M> &q1) {
  Quantity<T, L, M> q(q1.value);
  return q;
}

template<int T, int L, int M>
Quantity<T, L, M> operator-(const Quantity<T, L, M> &q1) {
  Quantity<T, L, M> q(-1 * q1.value);
  return q;
}

template<int T, int L, int M>
bool operator>(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return q1.value > q2.value;
}

template<int T, int L, int M>
bool operator<(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return q1.value < q2.value;
}

template<int T, int L, int M>
bool operator<=(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return q1.value <= q2.value;
}

template<int T, int L, int M>
bool operator>=(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return q1.value >= q2.value;
}

template<int T, int L, int M>
bool operator==(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return q1.value == q2.value;
}

template<int T, int L, int M>
bool operator!=(const Quantity<T, L, M> &q1, const Quantity<T, L, M> &q2) {
  return q1.value != q2.value;
}

// template<class U, int T, int L, int M>
// bool operator==(const U &q1, const Quantity<T, L, M> &q2) {
//   return q1 == q2.value;
// }
// template<class U,int T, int L, int M>
// bool operator!=(const Quantity<T, L, M> &q1, const U &q2) {
//   return q1.value != q2;
// }
// template<class U, int T, int L, int M>
// bool operator==(const Quantity<T, L, M> &q1, const U &q2) {
//   return q1 == q2.value;
// }
// template<class U,int T, int L, int M>
// bool operator!=(const U &q1, const Quantity<T, L, M> &q2) {
//   return q1.value != q2;
// }

using Time = Quantity<1,0,0>;
using Length = Quantity<0,1,0>;
using Mass = Quantity<0,0,1>;
using Speed = Quantity<-1,1,0>;
using Acceleration = Quantity<-2,1,0>;
using Force = Quantity<-2, 1, 1>;
using Energy = Quantity<-2, 2, 1>;
#endif //QUANTITY_H
