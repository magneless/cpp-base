#pragma once

#include <functional>
#include <string>


class TokenParser {
public:

  TokenParser() = default;

  void setStartCallback(std::function<void()> callback);

  void setEndCallback(std::function<void()> callback);

  void setDigitTokenCallback(std::function<void(uint64_t)> callback);

  void setCharTokenCallback(std::function<void(std::string)> callback);

  void parse(const std::string & line);

private:
  std::function<void()> startCallback = nullptr;
  std::function<void()> endCallback = nullptr;
  std::function<void(uint64_t)> digitTokenCallback = nullptr;
  std::function<void(std::string)> charTokenCallback = nullptr;

  void chooseCallback(std::string token);
};
