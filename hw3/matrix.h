#pragma once

#include <iostream>

class Matrix {
private:
  class ProxyRow {
  public:
    ProxyRow();
    explicit ProxyRow(size_t columns);
    int& operator[](size_t j);
    int& operator[](size_t j) const;

    int *data_;
    size_t len_;
  };

public:
  Matrix(size_t rows, size_t columns);
  Matrix(const Matrix& matrix);
  ~Matrix();

  size_t getRows() const;
  size_t getColumns() const;

  ProxyRow& operator[](size_t i);
  ProxyRow& operator[](size_t j) const;
  Matrix& operator*=(int num);
  Matrix operator+(const Matrix& matrix) const;
  bool operator==(const Matrix& matrix) const;
  Matrix& operator=(const Matrix& matrix);

  friend std::ostream& operator<<(std::ostream &out, const Matrix& matrix);
private:
  size_t rows_;
  size_t columns_;

  ProxyRow *pRows_ = nullptr;
};


