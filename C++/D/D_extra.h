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
