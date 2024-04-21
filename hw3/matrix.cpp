#include <iostream>

#include "matrix.h"

Matrix::ProxyRow::ProxyRow() : data_(nullptr), len_(0) {}

Matrix::ProxyRow::ProxyRow(size_t columns) :
  data_(new int[columns]),
  len_(columns) {
  std::fill(data_, data_ + len_, 0); 
}

Matrix::Matrix(size_t rows, size_t columns) : 
  rows_(rows),
  columns_(columns),
  pRows_(new ProxyRow[rows]) {
  for (size_t i = 0; i < rows_; ++i) {
    pRows_[i] = ProxyRow(columns_);
  }
}

Matrix::Matrix(const Matrix& matrix) :
  rows_(matrix.rows_),
  columns_(matrix.columns_),
  pRows_(new ProxyRow[matrix.rows_]) {
  for (size_t  i =0; i < rows_; ++i) {
    pRows_[i] = ProxyRow(columns_);
    for (size_t  j = 0; j < columns_; ++j) {
      pRows_[i][j] = matrix[i][j];
    }
  }
}

Matrix::~Matrix() {
  for (size_t  i = 0; i < rows_; ++i) {
    delete[] pRows_[i].data_;
  }
  delete[] pRows_;
}

size_t Matrix::getRows() const {
  return rows_;
}

size_t Matrix::getColumns() const {
  return columns_;
}

Matrix::ProxyRow& Matrix::operator[](size_t i) {
  if (i >= rows_) {
    throw std::out_of_range("out of range");
  }
  return pRows_[i];
}

Matrix::ProxyRow& Matrix::operator[](size_t i) const{
  if (i >= rows_) {
    throw std::out_of_range("out of range");
  }
  return pRows_[i];
}

int& Matrix::ProxyRow::operator[](size_t j) {
  if (j >= len_) {
    throw std::out_of_range("out of range");
  }
  return data_[j];
}

int& Matrix::ProxyRow::operator[](size_t j) const{
  if (j >= len_) {
    throw std::out_of_range("out of range");
  }
  return data_[j];
}

Matrix& Matrix::operator*=(int num) {
  for (size_t  i = 0; i < rows_; ++i) {
    for (size_t  j = 0; j < columns_; ++j) {
      pRows_[i][j] *= num;
    }
  }

  return *this;
}

std::ostream& operator<<(std::ostream &out, const Matrix& matrix) {
  for (size_t  i = 0; i < matrix.rows_; i++) {
    for (size_t  j = 0; j < matrix.columns_; j++) {
      out << matrix[i][j] << " ";
    }
  out << std::endl;
  }
  return out;
}

Matrix Matrix::operator+(const Matrix& matrix) const {
  if (matrix.columns_ != columns_ || matrix.rows_ != rows_) {
    throw std::invalid_argument("Dimensions are not the same");
  }

  Matrix res(*this);
  for (size_t  i = 0; i < rows_; i++) {
    for (size_t  j = 0; j < columns_; j++) {
      res[i][j] += matrix[i][j]; 
    }
  }
  return res;
}

bool Matrix::operator==(const Matrix& matrix) const {
  if (matrix.columns_ != columns_ || matrix.rows_ != rows_) {
    return false;
  }

  for (size_t  i = 0; i < rows_; ++i) {
    for (size_t  j = 0; j < columns_; ++j) {
      if (matrix[i][j] != (*this)[i][j]) return false;
    }
  }
  return true;
}

Matrix& Matrix::operator=(const Matrix& matrix) {
  if (pRows_!= nullptr) {
    for (size_t  i = 0; i < rows_; ++i) {
      delete [] pRows_[i].data_;
    }
    delete [] pRows_;
  }

  columns_ = matrix.columns_;
  rows_ = matrix.rows_;

  pRows_ = new ProxyRow[rows_];
  for (size_t  i = 0; i < rows_; ++i) {
    pRows_[i] = ProxyRow(columns_);
    for (size_t  j = 0; j < columns_; ++j) {
      (*this)[i][j] = matrix[i][j];
    }
  }

  return *this;
}
