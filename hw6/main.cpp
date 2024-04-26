#include <iostream>
#include <string>
#include <fstream>

#include "format.h"

struct S{
  int a;
  std::string str;
};

int main () {
  std::string str = "{1} + {0} = {2}";
  std::string rep = "one";
  std::cout << format(str, rep, 1, "two") << std::endl;
}