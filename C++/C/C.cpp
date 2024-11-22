#include "rational.h"
#include <iostream>

Rational::Rational() : num_(0), den_(1) {}
Rational::Rational(int n) : num_(n), den_(1) {}
Rational::Rational(int n, int m) : num_(n), den_(m) {
  Reduce();
}

void Rational::Reduce() {
  if (den_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (num_ == 0) {
    den_ = 1;
  } else {
    int gcd = std::abs(num_);
    int copy_den = std::abs(den_);
    while (copy_den != 0) {
      int tmp = copy_den;
      copy_den = gcd % copy_den;
      gcd = tmp;
    }
    num_ /= gcd;
    den_ /= gcd;
    if (den_ < 0) {
      num_ *= (-1);
      den_ *= (-1);
    }
  }
}

int Rational::GetNumerator() const {
  return num_;
}

int Rational::GetDenominator() const {
  return den_;
}

void Rational::SetNumerator(int a) {
  num_ = a;
  Reduce();
}

void Rational::SetDenominator(int a) {
  den_ = a;
  Reduce();
}

Rational operator+(const Rational &first, const Rational &second) {
  int new_num = first.GetNumerator() * second.GetDenominator() + second.GetNumerator() * first.GetDenominator();
  int new_den = first.GetDenominator() * second.GetDenominator();
  return Rational{new_num, new_den};
}

Rational operator-(const Rational &first, const Rational &second) {
  int new_num = first.GetNumerator() * second.GetDenominator() - second.GetNumerator() * first.GetDenominator();
  int new_den = first.GetDenominator() * second.GetDenominator();
  return Rational{new_num, new_den};
}

Rational operator/(const Rational &first, const Rational &second) {
  int new_num = first.GetNumerator() * second.GetDenominator();
  int new_den = first.GetDenominator() * second.GetNumerator();
  return Rational{new_num, new_den};
}

Rational operator*(const Rational &first, const Rational &second) {
  int new_num = first.GetNumerator() * second.GetNumerator();
  int new_den = first.GetDenominator() * second.GetDenominator();
  return Rational{new_num, new_den};
}

Rational &Rational::operator+=(const Rational &other) {
  *this = *this + other;
  Reduce();
  return *this;
}

Rational &Rational::operator-=(const Rational &other) {
  *this = *this - other;
  Reduce();
  return *this;
}

Rational &Rational::operator/=(const Rational &other) {
  *this = *this / other;
  Reduce();
  return *this;
}

Rational &Rational::operator*=(const Rational &other) {
  *this = *this * other;
  Reduce();
  return *this;
}

Rational operator+(const Rational &rational) {
  return Rational{rational.GetNumerator(), rational.GetDenominator()};
}

Rational operator-(const Rational &rational) {
  return Rational{-rational.GetNumerator(), rational.GetDenominator()};
}

Rational &Rational::operator++() {
  *this = *this + 1;
  return *this;
}

Rational Rational::operator++(int) {
  *this = *this + 1;
  return *this - 1;
}

Rational &Rational::operator--() {
  *this = *this - 1;
  return *this;
}

Rational Rational::operator--(int) {
  *this = *this - 1;
  return *this + 1;
}

bool operator==(const Rational first, const Rational second) {
  return (first.GetNumerator() * second.GetDenominator() == first.GetDenominator() * second.GetNumerator());
}

bool operator!=(const Rational first, const Rational second) {
  return !(first == second);
}

bool operator<(const Rational first, const Rational second) {
  return (first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator());
}

bool operator>(const Rational first, const Rational second) {
  return (first.GetNumerator() * second.GetDenominator() > first.GetDenominator() * second.GetNumerator());
}

bool operator<=(const Rational first, const Rational second) {
  return (first.GetNumerator() * second.GetDenominator() <= first.GetDenominator() * second.GetNumerator());
}

bool operator>=(const Rational first, const Rational second) {
  return (first.GetNumerator() * second.GetDenominator() >= first.GetDenominator() * second.GetNumerator());
}

std::istream &operator>>(std::istream &is, Rational &rat) {
  int32_t n = 0;
  int32_t m = 0;
  char t = 0;
  is >> n;
  if (is.peek() != '/') {
    rat = Rational(n);
    return is;
  }
  is >> t;
  is >> m;
  rat = Rational(n, m);
  return is;
}

std::ostream &operator<<(std::ostream &os, const Rational &rational) {
  if (rational.GetDenominator() == 1) {
    os << rational.GetNumerator();
    return os;
  }
  os << rational.GetNumerator() << '/' << rational.GetDenominator();
  return os;
}
