#include <gtest/gtest.h>
#include <sstream>

#include "matrix.h"

TEST (RowsColsLenTest, TruthResult) {
  size_t rows = 5;
  size_t cols = 3;
  
  Matrix m(rows, cols);

  EXPECT_EQ(m.getColumns(), cols);
  EXPECT_EQ(m.getRows(), rows);
}

TEST (IndexTest, TruthResult) {
  int res = 4;

  Matrix m(2, 3);

  m[1][1] = res;

  EXPECT_EQ(m[1][1], res);

  m[1][1] = -res;

  EXPECT_EQ(m[1][1], -res);
  EXPECT_EQ(m[0][0], 0);
}

TEST (IndexTest, ThrowException) {
  Matrix m(2, 3);

  EXPECT_THROW(m[2][0], std::out_of_range);
  EXPECT_THROW(m[0][3], std::out_of_range);
}

TEST (MulliplicationTest, TruthResult) {
  int n = 5;

  Matrix m(1, 3);

  m[0][0] = 2;
  m[0][1] = 3;

  m *= n;

  EXPECT_EQ(m[0][0], n*2);
  EXPECT_EQ(m[0][1], n*3);
  EXPECT_EQ(m[0][2], 0);
}

TEST (OutputStreamTest, CorrectWork) {
  std::string expec = "0 1 2 \n0 1 2 \n";
  std::stringstream ss;
  
  Matrix m(2, 3);

  for (size_t i = 0; i < m.getRows(); ++i) {
    for (size_t j = 0; j < m.getColumns(); ++j) {
      m[i][j] = j;
    }
  }
  
  ss << m;

  std::string res = ss.str();

  EXPECT_EQ(res, expec);
}

TEST (ComparaisonTest, TruthResult) {
  Matrix m1(2, 3);
  Matrix m2 (3, 2);

  EXPECT_FALSE(m1 == m2);

  for (size_t i = 0; i < m1.getRows(); ++i) {
    for (size_t j = 0; j < m1.getColumns(); ++j) {
      m1[i][j] = j;
    }
  }

  m2 = m1;

  EXPECT_TRUE(m1 == m2);
}

TEST (SumTest, TruthResult) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);
  Matrix expec(3, 3);

  for (size_t i = 0; i < m1.getRows(); ++i) {
    for (size_t j = 0; j < m1.getColumns(); ++j) {
      m1[i][j] = j;
      m2[i][j] = j*2;
      expec[i][j] = j + j*2;
    }
  }
  
  Matrix m3 = m1 + m2;

  ASSERT_EQ(m3, expec);
}

TEST (SumTest, ThrowException) {
  Matrix m1(3, 3);
  Matrix m2(4, 4);

  EXPECT_THROW(m1 + m2, std::invalid_argument);
}
