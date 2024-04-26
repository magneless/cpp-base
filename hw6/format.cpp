#include "format.h"

void checkString(const std::string& str, size_t size) {
  size_t posStart = 0;
  size_t posEnd = 0;
  size_t count = 0;

  while ((posStart = str.find('{', posStart)) != std::string::npos) {
    if ((posEnd = str.find('}', posEnd)) != std::string::npos) {
      if(posEnd < posStart) {
        throw std::logic_error("1. Wrong string fromat!!! Expect '{' before '}'.\n");
      }
      ++posStart;
      try {
        std::stoll(str.substr(posStart, posEnd - posStart));
      } catch(...) {
        throw std::logic_error("Wrong string fromat!!! Expect number in brackets.\n");
      }
      ++count;
      ++posEnd;
    }
    else throw std::logic_error("Wrong string fromat!!! Need '}'.\n");
  }
  if (str.find('}', posEnd) != std::string::npos) {
    throw std::logic_error("2. Wrong string fromat!!! Expect '{' before '}'.\n");
  }

  if (count != size) {
    throw std::logic_error("Wrong number of arguments!!!\n");
  }
}
