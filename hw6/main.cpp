#include <iostream>
#include <string>
#include <fstream>

#include "format.h"

struct S{
  int a;
  std::string str;
};

int main () {
  std::string str = "AA {1} {0} {1} BB {2} {3}", rep = "one";
  S s;
  std::cout << format(str, rep, "two", 1, 1000) << std::endl;
}