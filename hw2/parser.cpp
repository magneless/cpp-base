#include <sstream>
#include <functional>

#include "parser.h"


void TokenParser::setStartCallback(std::function<void()> callback) {
  startCallback = callback;
}

void TokenParser::setEndCallback(std::function<void()> callback) {
  endCallback = callback;
}

void TokenParser::setDigitTokenCallback
(std::function<void(uint64_t)> callback) {
  digitTokenCallback = callback;
}

void TokenParser::setCharTokenCallback
(std::function<void(std::string)> callback) {
  charTokenCallback = callback;
}

void TokenParser::chooseCallback(std::string token) {
  try {
    if (token.find(".") != std::string::npos ||
        token.find("-") != std::string::npos) {
      throw std::exception();
    }
    uint64_t num = std::stoll(token);
    if (digitTokenCallback != nullptr) {
      digitTokenCallback(num);
    } 
  } catch(const std::exception& e) {
    if (charTokenCallback != nullptr) {
      charTokenCallback(token);
    }
  }
}

void TokenParser::parse(const std::string & line) {
  if (startCallback != nullptr) {
    startCallback();
  }

  std::stringstream tokens(line);
  std::string token;
  while(tokens >> token) {
    chooseCallback(token);
  }

  if (endCallback != nullptr) {
    endCallback();
  }
}
