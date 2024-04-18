#pragma once

#include <iostream>

enum class Error {
  NoError,
  CorruptedArchive
};

class Serializer {
  static constexpr char sep = ' ';
public:
  explicit Serializer(std::ostream& out);
  
  template <class T>
  Error save(T& object) {
    return object.serialize(*this);
  }

  template <class... ArgsT>
  Error operator()(ArgsT... args) {
    return process(args...);
  }

  Error process(bool arg);
  Error process(uint64_t arg);
  template <class T>
  Error process(T) {
    return Error::CorruptedArchive;
  }

private:
  std::ostream& out_;

  template <class T, class... ArgsT>
  Error process(T&& val, ArgsT&&... args) {
    if (process(val) == Error::CorruptedArchive) return Error::CorruptedArchive;
    return process(std::forward<ArgsT>(args)...);
  }
};

class Deserializer {
public:
  explicit Deserializer(std::istream& in) : in_(in) {}

  template <class T>
  Error load(T& object) {
    return object.deserialize(*this);
  }

  template <class... ArgsT>
  Error operator()(ArgsT&... args) {
    return process(args...);
  }

  Error process(bool& arg);
  Error process(uint64_t& arg);
  template<class T>
  Error process(T) {
    return Error::CorruptedArchive;
  }
private:
  std::istream& in_;

  template <class T, class... ArgsT>
  Error process(T& val, ArgsT&... args) {
    if (process(val) == Error::CorruptedArchive) return Error::CorruptedArchive;
    return process(args...);
  }
};
