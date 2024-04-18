#include <iostream>
#include <string>

#include "serializer.h"


Serializer::Serializer(std::ostream* out) : out_(out) {}


Error Serializer::process(bool arg) {
    *out_ << (arg ? "true" : "false") << sep;
    return Error::NoError;
}

Error Serializer::process(uint64_t arg) {
    *out_ << arg << sep;
    return Error::NoError;
}

Deserializer::Deserializer(std::istream* in) : in_(in) {}

Error Deserializer::process(bool* arg) {
  std::string text;
  *in_ >> text;
  
  if (text == "true") *arg = true;
  else if (text == "false") *arg = false;
  else return Error::CorruptedArchive;

  return Error::NoError;
}

Error Deserializer::process(uint64_t* arg) {
  std::string text;
  *in_ >> text;

  try {
    *arg = std::stoll(text);
  } catch(const std::exception & e) {
    return Error::CorruptedArchive;
  }

  return Error::NoError;
}
