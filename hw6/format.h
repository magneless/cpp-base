#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void checkString(const std::string& str, size_t size);

template <class T>
concept printable = requires(std::ostream stream, T t) {
                      { stream << t } -> std::same_as<std::ostream&>;
                    };

template <printable T>
void replaceArg(std::string* formatStr, uint64_t argNum, T arg) {
  size_t posStart;
  size_t posEnd = 0;
  bool flag = false;

  while ((posStart = formatStr->find('{', posEnd)) != std::string::npos) {
    ++posStart;
    posEnd = formatStr->find('}', posStart);
    uint64_t subStrUint64t =
        std::stoll(formatStr->substr(posStart, posEnd - posStart));
    if (argNum == subStrUint64t) {
      flag = true;
      std::stringstream ss;
      ss << arg;
      formatStr->replace(posStart - 1, posEnd - posStart + 2, ss.str());
    }
  }

  if (!flag) throw std::logic_error("Wrong argument in brackets!!!\n");
}

template <class T>
void replaceArg(std::string*, uint64_t, T) {
  throw std::ios_base::failure("Argument can not be printed!!!\n");
}

template <class T, class... ArgsT>
void replaceArg(std::string* formatStr, uint64_t argNum, T arg, ArgsT... args) {
  replaceArg(formatStr, argNum, arg);
  replaceArg(formatStr, argNum + 1, args...);
}

template <class... ArgsT>
std::string format(const std::string& str, ArgsT... args) {
  checkString(str, sizeof...(args));

  std::string formatStr = str;
  replaceArg(&formatStr, 0, args...);
  return formatStr;
}
