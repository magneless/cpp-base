#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

#include "serializer.h"

struct Data1 {
  bool a;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a);
  }
};

struct Data2 {
  bool a;
  bool b;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a, b);
  }
};

struct Data3 {
  uint64_t a;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a);
  }
};

struct Data4 {
  uint64_t a;
  uint64_t b;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a, b);
  }
};

struct Data5 {
  bool a;
  uint64_t b;
  uint64_t c;
  bool d;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a, b, c, d);
  }

  template <class Deserializer>
  Error deserialize(Deserializer& desirializer) {
    return desirializer(a, b, c, d);
  }
};


struct ErrorData {
  std::string a;
  bool b;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a, b);
  }

  template <class Deserializer>
  Error deserialize(Deserializer& desirializer) {
    return desirializer(a, b);
  }
};

TEST (TestSerializerProcess, CorrectChangeOfBoolParametrs) {
  std::stringstream ss;

  Serializer ser(ss);
  Data1 data1{true};
  ser.save(data1);
  EXPECT_EQ(ss.str(), "true ");

  ss.str("");
  data1.a = false;
  ser.save(data1);
  EXPECT_EQ(ss.str(), "false ");

  ss.str("");
  Data2 data3{true, false};
  ser.save(data3);
  EXPECT_EQ(ss.str(), "true false ");
}

TEST (TestSerializerProcess, CorrectChangeOfUint64TParametrs) {
  std::stringstream ss;

  Serializer ser(ss);
  Data3 data1{ 10 };
  ser.save(data1);
  EXPECT_EQ(ss.str(), "10 ");

  ss.str("");
  Data4 data2{ 2, 3};
  ser.save(data2);
  EXPECT_EQ(ss.str(), "2 3 ");
}

TEST (TestSerializerProcess, CorrectChangeOfUint64TAndBoolParametrs) {
  std::stringstream ss;

  Serializer ser(ss);
  Data5 data5{ true, 1, 2, false };
  ser.save(data5);
  EXPECT_EQ(ss.str(), "true 1 2 false ");
}

TEST (TestDeserializer, CorrecrWork) {
  std::stringstream ss;

  Serializer ser(ss);
  Data5 data1{ true, 10, 15, false };
  ser.save(data1);
  
  Deserializer deser(ss);
  Data5 data2{ false, 1, 2, true };
  deser.load(data2);
  EXPECT_EQ(data1.a, data2.a);
  EXPECT_EQ(data1.b, data2.b);
  EXPECT_EQ(data1.c, data2.c);
}

TEST (TestErrorReturn, CorrectErrorReturnWithCorrectInputData) {
  std::stringstream ss;

  Serializer ser(ss);
  Data5 data1{ true, 1, 2, true };
  const Error err1 = ser.save(data1);
  EXPECT_EQ(err1, Error::NoError);

  Deserializer deser(ss);
  Data5 data2{ false, 2, 1, true };
  const Error err2 = deser.load(data2);
  EXPECT_EQ(err2, Error::NoError);
}

TEST (TestErrorReturn, CorrectErrorReturnWithIncorrectInputData) {
  std::stringstream ss;

  ss.str("error 100 200 true ");
  Deserializer deser(ss);
  Data5 data1{true, 1, 2, false};
  const Error err1 = deser.load(data1);
  EXPECT_EQ(err1, Error::CorruptedArchive);
  
  ss.str("true error 200 true ");
  const Error err2 = deser.load(data1);
  EXPECT_EQ(err2, Error::CorruptedArchive);
}

TEST (TestErrorReturn, CorrectErrorReturnWithIncorrectInputDataStructure) {
  std::stringstream ss;

  Serializer ser(ss);
  ErrorData errorData1{ "error", true };
  const Error err1 = ser.save(errorData1);
  EXPECT_EQ(err1, Error::CorruptedArchive);

  ss.str("error");
  Deserializer deser(ss);
  ErrorData errorData2{"error", false};
  const Error err2 = deser.load(errorData2);
  EXPECT_EQ(err2, Error::CorruptedArchive);
}
