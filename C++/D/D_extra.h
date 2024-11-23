T Trace() {
    T trace = T();
    for (size_t i = 0; i < cols; ++i) {
      trace += this->operator()(i, i);
    }
    return trace;
  }

  friend void Transpose(Matrix<T, Cols, Cols> &matrix) {
    for (int i = 0; i < Cols; ++i) {
      for (int j = i + 1; j < Cols; ++j) {
        Swap(matrix(i, j), matrix(j, i));
      }
    }
  }

double Determinant() {
    double det = 0;
    size_t m_size = this->size;
    if (m_size == 1) {
      return this->matrix[0][0];
    }
    if (m_size == 2) {
      return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
    }
    for (size_t col = 0; col < m_size; ++col) {
      Matrix<T, Rows, Cols> tmp_matrix;
      tmp_matrix.size = m_size - 1;
      for (int i = 0; i < m_size - 1; ++i) {
        for (int j = 0; j < m_size; ++j) {
          if (j < col) {
            tmp_matrix.matrix[i][j] = this->matrix[i + 1][j];
          } else if (j > col) {
            tmp_matrix.matrix[i][j - 1] = this->matrix[i + 1][j];
          }
        }
      }
      if (col % 2 == 0) {
        det += this->matrix[0][col] * tmp_matrix.Determinant();
      } else {
        det -= this->matrix[0][col] * tmp_matrix.Determinant();
      }
    }
    return det;
  }
