#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "format.h"

TEST(TestFormat, CorrectInput) {
  auto text = format("{1} + {1} = {0}", 2, "one");
  EXPECT_EQ(text, "one + one = 2");
}

TEST(TestFormat, UnprintableArgumnet) {
  struct S {
    int s = 0;
  };
  S s;
  EXPECT_THROW(format("{0}", s), std::ios_base::failure);
}

TEST(TestFormat, WrongNumberOfArguments) {
  EXPECT_THROW(format("", 1), std::logic_error);
  EXPECT_THROW(format("{0}", 1, 2), std::logic_error);
  EXPECT_THROW(format("{0} {1}", 1), std::logic_error);
  EXPECT_THROW(format("{1} {1}", 1, 2), std::logic_error);
}

TEST(TestFormat, LackOfLeftBracket) {
  EXPECT_THROW(format("}", 1), std::logic_error);
  EXPECT_THROW(format("{}}", 1), std::logic_error);
  EXPECT_THROW(format("}{}", 1), std::logic_error);
}

TEST(TestFormat, LackOfRightBracket) {
  EXPECT_THROW(format("{", 1), std::logic_error);
  EXPECT_THROW(format("{}{", 1), std::logic_error);
  EXPECT_THROW(format("{{}", 1), std::logic_error);
}

TEST(TestFormat, NotNumberInBrackets) {
  EXPECT_THROW(format("{one}", 1), std::logic_error);
  EXPECT_THROW(format("{0} {one}", 1, 2), std::logic_error);
}
