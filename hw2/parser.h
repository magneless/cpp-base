#pragma once

#include <string>

class TokenParser {
public:

  TokenParser() = default;

  void setStartCallback(void (*callback)());

  void setEndCallback(void (*callback)());

  void setDigitTokenCallback(void (*callback)(uint64_t));

  void setCharTokenCallback(void (*callback)(std::string));

  void parse(const std::string & line);

private:
  void (*startCallback) () = nullptr;
  void (*endCallback) () = nullptr;
  void (*digitTokenCallback) (uint64_t) = nullptr;
  void (*charTokenCallback) (std::string) = nullptr;

  void chooseCallback(std::string token, bool isNum);
};
