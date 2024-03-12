#include <gtest/gtest.h>
#include <vector>

#include "parser.h"


TEST(ParseTest, StartCallback) {
  TokenParser parser;

  int count = 0;
  std::string str = "abc asd";
  auto callback = [&count](){
    count++;
  };

  EXPECT_EQ(count, 0);

  parser.setStartCallback(callback);
  parser.parse(str);

  EXPECT_EQ(count, 1);

  for (int i = 0; i < 8; i++) {
    parser.parse(str);
  }

  EXPECT_EQ(count, 9);
}

TEST(ParseTest, EndCallback) {
  TokenParser parser;

  int count = 0;
  std::string str = "abc asd";
  auto callback = [&count](){
    count++;
  };

  EXPECT_EQ(count, 0);

  parser.setEndCallback(callback);
  parser.parse(str);

  EXPECT_EQ(count, 1);

  for (int i = 0; i < 8; i++) {
    parser.parse(str);
  }

  EXPECT_EQ(count, 9);
}

TEST(ParseTest, DigitTokenCallback) {
  TokenParser parser;
  
  std::vector<uint64_t> tokens;
  std::vector<uint64_t> expectedTokens = {123, 32, 2};
  std::string str = "123 32 2";
  auto callback = [&tokens](uint64_t token){
    tokens.push_back(token);
  };

  EXPECT_EQ(tokens.size(), 0);

  parser.setDigitTokenCallback(callback);
  parser.parse(str);

  EXPECT_EQ(tokens, expectedTokens);

  str = "123 aa\n24 a123";
  expectedTokens.insert(expectedTokens.end(), { 123, 24 });

  parser.parse(str);

  EXPECT_EQ(tokens, expectedTokens);
}

TEST(ParseTest, CharTokenCallback) {
  TokenParser parser;

  std::vector<std::string> tokens;
  std::vector<std::string> expectedTokens = {"asd", "cds"};
  std::string str = "asd 124 cds 2";
  auto callback = [&tokens](std::string token) {
    tokens.push_back(token);
  };

  EXPECT_EQ(tokens.size(), 0);

  parser.setCharTokenCallback(callback);
  parser.parse(str);

  EXPECT_EQ(tokens, expectedTokens);

  str = "aa ff\na\taa";
  expectedTokens.insert(expectedTokens.end(), {"aa", "ff", "a", "aa" });

  parser.parse(str);

  EXPECT_EQ(tokens, expectedTokens);

  str = "18446744073709551616";
  expectedTokens.push_back("18446744073709551616");

  parser.parse(str);

  EXPECT_EQ(tokens, expectedTokens);
}

TEST(ParseTest, AllCallbacks) {
  TokenParser parser;
  
  int startCount = 0, endCount = 0;
  std::vector<uint64_t> digitTokens;
  std::vector<std::string> charTokens;

  std::vector<uint64_t> expectedDigitTokens = { 2 };
  std::vector<std::string> expectedCharTokens = { "asd", "-123", "aa", "20.2" };

  std::string str = "asd -123 aa\n2 20.2";

  auto startCallback = [&startCount]() {
    startCount++;
  };
  auto endCallback = [&endCount]() {
    endCount++;
  };
  auto digitCallback = [&digitTokens](uint64_t digitToken) {
    digitTokens.push_back(digitToken);
  };
  auto charCallback = [&charTokens](std::string charToken) {
    charTokens.push_back(charToken);
  };

  parser.setStartCallback(startCallback);
  parser.setEndCallback(endCallback);
  parser.setDigitTokenCallback(digitCallback);
  parser.setCharTokenCallback(charCallback);

  parser.parse(str);

  EXPECT_EQ(startCount, 1);
  EXPECT_EQ(endCount, 1);
  EXPECT_EQ(digitTokens, expectedDigitTokens);
  EXPECT_EQ(charTokens, expectedCharTokens);
}
