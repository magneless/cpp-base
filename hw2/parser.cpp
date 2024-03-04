#include "parser.h"

void TokenParser::setStartCallback(void (*callback)()) {
  startCallback = callback;
}

void TokenParser::setEndCallback(void (*callback)()) {
  endCallback = callback;
}

void TokenParser::setDigitTokenCallback(void (*callback)(uint64_t)) {
  digitTokenCallback = callback;
}

void TokenParser::setCharTokenCallback(void (*callback)(std::string)) {
  charTokenCallback = callback;
}

void TokenParser::chooseCallback(std::string token, bool isUint64) {
  std::string maxString = std::to_string(UINT64_MAX);
  uint64_t maxSize = maxString.size();

  if (token.size() > maxSize) isUint64 = false;
  else if (token.size() == maxSize && token > maxString) isUint64 = false;

  if (isUint64 && digitTokenCallback != nullptr) {
    digitTokenCallback(std::stoll(token));
  }
  else if (!isUint64 && charTokenCallback != nullptr) {
    charTokenCallback(token);
  }
}

void TokenParser::parse(const std::string & line) {
  if (startCallback != nullptr) {
    startCallback();
  }

  if (charTokenCallback != nullptr || digitTokenCallback != nullptr) {
    std::string token;
    bool isUint64 = true;
    for (char c : line) {
      if (!(c == ' ' || c == '\n' || c == '\t')) {
        token += c;
        if (c > '9' || c < '0') isUint64 = false;
      }
      else {
        chooseCallback(token, isUint64);
        token.clear();
        isUint64 = true;
      }
    }
    chooseCallback(token, isUint64);
  }

  if (endCallback != nullptr) {
    endCallback();
  }
}