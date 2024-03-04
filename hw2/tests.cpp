#include <gtest/gtest.h>
#include <vector>

#include "parser.h"


TEST(ParseTest, StartCallback) {
  TokenParser parser;

  static int count = 0;
  std::string str = "abc asd";
  auto callback = [](){
    count++;
  };

  EXPECT_TRUE(count == 0);

  parser.setStartCallback(callback);
  parser.parse(str);

  EXPECT_TRUE(count == 1);

  for (int i = 0; i < 8; i++) {
    parser.parse(str);
  }

  EXPECT_TRUE(count == 9);
}

TEST(ParseTest, EndCallback) {
  TokenParser parser;

  static int count = 0;
  std::string str = "abc asd";
  auto callback = [](){
    count++;
  };

  EXPECT_TRUE(count == 0);

  parser.setEndCallback(callback);
  parser.parse(str);

  EXPECT_TRUE(count == 1);

  for (int i = 0; i < 8; i++) {
    parser.parse(str);
  }

  EXPECT_TRUE(count == 9);
}

TEST(ParseTest, DigitTokenCallback) {
  TokenParser parser;
  
  static std::vector<uint64_t> tokens;
  std::vector<uint64_t> expectedTokens = {123, 32, 2};
  std::string str = "123 32 2";
  auto callback = [](uint64_t token){
    tokens.push_back(token);
  };

  EXPECT_TRUE(tokens.size() == 0);

  parser.setDigitTokenCallback(callback);
  parser.parse(str);

  EXPECT_TRUE(tokens == expectedTokens);

  str = "123 aa\n24 a123";
  expectedTokens.insert(expectedTokens.end(), { 123, 24 });

  parser.parse(str);

  EXPECT_TRUE(tokens == expectedTokens);
}

TEST(ParseTest, CharTokenCallback) {
  TokenParser parser;

  static std::vector<std::string> tokens;
  std::vector<std::string> expectedTokens = {"asd", "cds"};
  std::string str = "asd 124 cds 2";
  auto callback = [](std::string token) {
    tokens.push_back(token);
  };

  EXPECT_TRUE(tokens.size() == 0);

  parser.setCharTokenCallback(callback);
  parser.parse(str);

  EXPECT_TRUE(tokens == expectedTokens);

  str = "aa ff\na\taa";
  expectedTokens.insert(expectedTokens.end(), {"aa", "ff", "a", "aa" });

  parser.parse(str);

  EXPECT_TRUE(tokens == expectedTokens);

  str = "18446744073709551616";
  expectedTokens.push_back("18446744073709551616");

  parser.parse(str);

  EXPECT_TRUE(tokens == expectedTokens);
}

TEST(ParseTest, AllCallbacks) {
  TokenParser parser;
  
  static int startCount = 0, endCount = 0;
  static std::vector<uint64_t> digitTokens;
  static std::vector<std::string> charTokens;

  std::vector<uint64_t> expectedDigitTokens = { 123, 2 };
  std::vector<std::string> expectedCharTokens = { "asd", "aa", "-2" };

  std::string str = "asd 123 aa\n2 -2";

  auto startCallback = []() {
    startCount++;
  };
  auto endCallback = []() {
    endCount++;
  };
  auto digitCallback = [](uint64_t digitToken) {
    digitTokens.push_back(digitToken);
  };
  auto charCallback = [](std::string charToken) {
    charTokens.push_back(charToken);
  };

  parser.setStartCallback(startCallback);
  parser.setEndCallback(endCallback);
  parser.setDigitTokenCallback(digitCallback);
  parser.setCharTokenCallback(charCallback);

  parser.parse(str);

  EXPECT_TRUE(startCount == 1);
  EXPECT_TRUE(endCount == 1);
  EXPECT_TRUE(digitTokens == expectedDigitTokens);
  EXPECT_TRUE(charTokens == expectedCharTokens);
}