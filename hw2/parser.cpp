#include <string>
#include <iostream>
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

void TokenParser::chooseCallback(std::string token) {
  try {
    uint64_t convertToken = std::stoull(token);
    if (digitTokenCallback != nullptr) {
      digitTokenCallback(convertToken);
    }
  } catch(std::exception) {
    if (charTokenCallback != nullptr) {
      charTokenCallback(token);
    }
  }
}

void TokenParser::parse(const std::string & line) {
  if (startCallback != nullptr) {
    startCallback();
  }

  if (charTokenCallback != nullptr || digitTokenCallback != nullptr) {
    std::string token;
    for (char c : line) {
      if (!(c == ' ' || c == '\t' || c == '\n')) {
        token += c;
      }
      else {
        chooseCallback(token);
        token.clear();
      }
    }
    chooseCallback(token);
}

  if (endCallback != nullptr) {
    endCallback();
  }
}