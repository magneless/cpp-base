#pragma once

#include <iostream>
#include <string>
#include <sstream>

template<class T>
void replaceArg(std::string* formatStr, uint64_t argNum, T arg) {
  size_t posStart; 
  size_t posEnd = 0;

  while ((posStart = formatStr->find('{', posEnd)) != std::string::npos) {
    ++posStart;
    posEnd = formatStr->find('}', posStart);

    if (std::to_string(argNum) == formatStr->substr(posStart, posEnd - posStart)) {
      std::stringstream ss;
      ss << arg;
      formatStr->replace(posStart, posEnd - posStart, ss.str());
    }
  }
}

template<class T, class... ArgsT>
void replaceArg(std::string* formatStr, uint64_t argNum, T arg, ArgsT... args) {
  replaceArg(formatStr, argNum, arg);
  replaceArg(formatStr, argNum+1, args...);
}

template<class... ArgsT>
std::string format(const std::string& str, ArgsT... args) {
  std::string formatStr = str;

  replaceArg(&formatStr, 0, args...);
  return formatStr;
}
