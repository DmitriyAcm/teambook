struct Matrix {
  ULL vals[N][N];
  Matrix() {
    for (int i = 0; i < N; ++i)
      fill(vals[i], vals[i] + N, 0);
  }

  ULL* operator[](const int idx) {
    return vals[idx];
  }

  const ULL* operator[](const int idx) const {
    return vals[idx];
  }

  static Matrix Ident() {
    Matrix res;
    for (int i = 0; i < N; ++i)
      res[i][i] = 1;

    return res;
  }

  Matrix operator*(const Matrix& o) const {
    Matrix res;

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
          res[i][j] += vals[i][k] * o[k][j];
          if (k == 7)
            res[i][j] %= MOD;
        }
        res[i][j] %= MOD;
      }
    }

    return res;
  }
};
