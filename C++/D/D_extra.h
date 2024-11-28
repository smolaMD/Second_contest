#ifndef MATRIX_SQUARE_MATRIX_IMPLEMENTED
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

#include <iostream>

template <typename T>
void Swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, size_t Rows, size_t Cols>
class Matrix {

 public:
  T matrix[Rows][Cols];

  size_t RowsNumber() const {
    return Rows;
  }

  size_t ColumnsNumber() const {
    return Cols;
  }

  T &operator()(size_t i, size_t j) {
    return matrix[i][j];
  }

  const T &operator()(size_t i, size_t j) const {
    return matrix[i][j];
  }

  T &At(size_t i, size_t j) {
    if (i >= Rows || j >= Cols) {
      throw MatrixOutOfRange();
    }
    return matrix[i][j];
  }

  const T &At(size_t i, size_t j) const {
    if (i >= Rows || j >= Cols) {
      throw MatrixOutOfRange();
    }
    return matrix[i][j];
  }

  Matrix<T, Rows, Cols> &operator+=(const Matrix<T, Rows, Cols> &other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        this->operator()(i, j) += other(i, j);
      }
    }
    return *this;
  }

  Matrix<T, Rows, Cols> &operator-=(const Matrix<T, Rows, Cols> &other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        this->operator()(i, j) -= other(i, j);
      }
    }
    return *this;
  }

  Matrix<T, Rows, Cols> &operator*=(const Matrix<T, Cols, Cols> &other) {
    Matrix<T, Rows, Cols> tmp_matrix;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        tmp_matrix(i, j) = T();
        for (size_t k = 0; k < Cols; ++k) {
          tmp_matrix(i, j) += this->operator()(i, k) * other(k, j);
        }
      }
    }
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        this->operator()(i, j) = tmp_matrix(i, j);
      }
    }
    return *this;
  }

  template <typename Scalar>
  Matrix<T, Rows, Cols> &operator*=(const Scalar &scalar) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        this->operator()(i, j) *= scalar;
      }
    }
    return *this;
  }

  template <typename Scalar>
  Matrix<T, Rows, Cols> &operator/=(const Scalar &scalar) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        this->operator()(i, j) /= scalar;
      }
    }
    return *this;
  }

  bool operator==(const Matrix<T, Rows, Cols> &other) const {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        if (this->operator()(i, j) != other(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix<T, Rows, Cols> &other) const {
    return !(*this == other);
  }
};

template <class T, size_t Rows, size_t Cols>
Matrix<T, Cols, Rows> GetTransposed(const Matrix<T, Rows, Cols> &matrix) {
  Matrix<T, Cols, Rows> transposed;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      transposed(j, i) = matrix(i, j);
    }
  }
  return transposed;
}

template <class T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols> &first, const Matrix<T, Rows, Cols> &second) {
  Matrix<T, Rows, Cols> matrix_sum;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      matrix_sum(i, j) = first(i, j) + second(i, j);
    }
  }
  return matrix_sum;
}

template <class T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols> &first, const Matrix<T, Rows, Cols> &second) {
  Matrix<T, Rows, Cols> matrix_dif;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      matrix_dif(i, j) = first(i, j) - second(i, j);
    }
  }
  return matrix_dif;
}

template <typename T, size_t Rows, size_t Cols, size_t Cols1>
Matrix<T, Rows, Cols1> operator*(Matrix<T, Rows, Cols> first, Matrix<T, Cols, Cols1> second) {
  Matrix<T, Rows, Cols1> matrix_prod;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols1; ++j) {
      matrix_prod(i, j) = T();
      for (size_t k = 0; k < Cols; ++k) {
        matrix_prod(i, j) += first(i, k) * second(k, j);
      }
    }
  }
  return matrix_prod;
}

template <class T, size_t Rows, size_t Cols, class Scalar>
Matrix<T, Rows, Cols> operator*(const Matrix<T, Rows, Cols> matrix, const Scalar &scalar) {
  Matrix<T, Rows, Cols> scalar_prod;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      scalar_prod(i, j) = matrix(i, j) * scalar;
    }
  }
  return scalar_prod;
}

template <class T, size_t Rows, size_t Cols, class Scalar>
Matrix<T, Rows, Cols> operator*(const Scalar &scalar, Matrix<T, Rows, Cols> matrix) {
  return matrix * scalar;
}

template <class T, size_t Rows, size_t Cols, class Scalar>
Matrix<T, Rows, Cols> operator/(const Matrix<T, Rows, Cols> matrix, const Scalar &scalar) {
  Matrix<T, Rows, Cols> scalar_prod;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      scalar_prod(i, j) = matrix(i, j) / scalar;
    }
  }
  return scalar_prod;
}

template <class T, size_t Rows, size_t Cols>
std::ostream &operator<<(std::ostream &os, const Matrix<T, Rows, Cols> &matrix) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      os << matrix(i, j);
      if (j < Cols - 1) {
        os << " ";
      }
    }
    os << "\n";
  }
  return os;
}

template <class T, size_t Rows, size_t Cols>
std::istream &operator>>(std::istream &is, Matrix<T, Rows, Cols> &matrix) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      is >> matrix.matrix[i][j];
    }
  }
  return is;
}

template <class T, size_t Cols>
T Determinant(const Matrix<T, Cols, Cols> &matrix) {
  size_t m_size = matrix.ColumnsNumber();
  Matrix<T, Cols, Cols> tmp_matrix;
  for (size_t i = 0; i < Cols; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      tmp_matrix(i, j) = matrix(i, j);
    }
  }
  return ReqursiveDet(tmp_matrix, m_size);
}

template <class T, size_t Cols>
T ReqursiveDet(Matrix<T, Cols, Cols> &matrix, size_t m_size) {
  T det = 0;
  if (m_size == 1) {
    return matrix(0, 0);
  }
  if (m_size == 2) {
    return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
  }
  for (size_t col = 0; col < m_size; ++col) {
    Matrix<T, Cols, Cols> tmp_matrix;
    for (size_t i = 1; i < m_size; ++i) {
      for (size_t j = 0; j < m_size; ++j) {
        if (j < col) {
          tmp_matrix(i - 1, j) = matrix(i, j);
        } else if (j > col) {
          tmp_matrix(i - 1, j - 1) = matrix(i, j);
        }
      }
    }
    if (col % 2 == 0) {
      det += matrix(0, col) * ReqursiveDet(tmp_matrix, m_size - 1);
    } else {
      det -= matrix(0, col) * ReqursiveDet(tmp_matrix, m_size - 1);
    }
  }
  return det;
}

template <class T, size_t Cols>
void Transpose(Matrix<T, Cols, Cols> &matrix) {
  for (size_t i = 0; i < Cols; ++i) {
    for (size_t j = i + 1; j < Cols; ++j) {
      std::swap(matrix(i, j), matrix(j, i));
    }
  }
}

template <class T, size_t Cols>
T Trace(const Matrix<T, Cols, Cols> &matrix) {
  T trace = T();
  for (size_t i = 0; i < Cols; ++i) {
    trace += matrix(i, i);
  }
  return trace;
}

template <class T, size_t Cols>
Matrix<T, Cols, Cols> GetInversed(const Matrix<T, Cols, Cols> &matrix) {
  Matrix<T, Cols, Cols> inversed;
  Matrix<T, Cols, Cols> tmp_matrix;
  for (size_t i = 0; i < Cols; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      tmp_matrix(i, j) = matrix(i, j);
    }
  }
  for (size_t i = 0; i < Cols; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      if (i == j) {
        inversed(i, j) = 1.0;
      } else {
        inversed(i, j) = 0.0;
      }
    }
  }
  for (size_t i = 0; i < Cols; ++i) {
    T tmp = tmp_matrix(i, i);
    if (tmp == 0) {
      throw MatrixIsDegenerateError();
    }
    for (size_t j = 0; j < Cols; ++j) {
      tmp_matrix(i, j) /= tmp;
      inversed(i, j) /= tmp;
    }
    for (size_t j = 0; j < Cols; ++j) {
      if (j != i) {
        T tmp1 = tmp_matrix(j, i);
        for (size_t k = 0; k < Cols; ++k) {
          tmp_matrix(j, k) -= tmp1 * tmp_matrix(i, k);
          inversed(j, k) -= tmp1 * inversed(i, k);
        }
      }
    }
  }
  return inversed;
}

template <class T, size_t Cols>
Matrix<T, Cols, Cols> Inverse(Matrix<T, Cols, Cols> &matrix) {
  Matrix<T, Cols, Cols> inversed;
  Matrix<T, Cols, Cols> tmp_matrix;
  for (size_t i = 0; i < Cols; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      tmp_matrix(i, j) = matrix(i, j);
    }
  }
  for (size_t i = 0; i < Cols; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      if (i == j) {
        inversed(i, j) = 1.0;
      } else {
        inversed(i, j) = 0.0;
      }
    }
  }
  for (size_t i = 0; i < Cols; ++i) {
    T tmp = tmp_matrix(i, i);
    if (tmp == 0) {
      throw MatrixIsDegenerateError();
    }
    for (size_t j = 0; j < Cols; ++j) {
      tmp_matrix(i, j) /= tmp;
      inversed(i, j) /= tmp;
    }
    for (size_t j = 0; j < Cols; ++j) {
      if (j != i) {
        T tmp1 = tmp_matrix(j, i);
        for (size_t k = 0; k < Cols; ++k) {
          tmp_matrix(j, k) -= tmp1 * tmp_matrix(i, k);
          inversed(j, k) -= tmp1 * inversed(i, k);
        }
      }
    }
  }
  for (size_t i = 0; i < Cols; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      matrix(i, j) = inversed(i, j);
    }
  }
  return matrix;
}

#endif
