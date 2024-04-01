#include <gtest/gtest.h>

#include "BigInt.h"

//-----------StrongLessOperator
TEST (StrongLessOperatorTest, DifSigns) {
    BigInt num1("123");
    BigInt num2("-123");


    EXPECT_FALSE(num1 < num2);
    EXPECT_TRUE(num2 < num1);
}

TEST (StrongLessOperatorTest, DifSizes) {
    BigInt num1("123");
    BigInt num2("12");


    EXPECT_FALSE(num1 < num2);
    EXPECT_TRUE(num2 < num1);
}

TEST (StrongLessOperatorTest, SameSignsAndSizes) {
    BigInt num1("123");
    BigInt num2("123");


    EXPECT_FALSE(num1 < num2);

    BigInt num3("1234");
    BigInt num4("4234");

    EXPECT_TRUE(num3 < num4);
    EXPECT_FALSE(num4 < num3);

    BigInt num5("-123");
    BigInt num6("-123");


    EXPECT_FALSE(num5 < num6);

    BigInt num7("-1234");
    BigInt num8("-4234");

    EXPECT_FALSE(num7 < num8);
    EXPECT_TRUE(num8 < num7);
}
//-----------EqualOperator
TEST (EqualOperatorTest, DifSigns) {
    BigInt num1("123");
    BigInt num2("-123");


    EXPECT_FALSE(num1 == num2);
    EXPECT_FALSE(num2 == num1);
}

TEST (EqualOperatorTest, DifSizes) {
    BigInt num1("123");
    BigInt num2("12");


    EXPECT_FALSE(num1 == num2);
    EXPECT_FALSE(num2 == num1);
}

TEST (EqualOperatorTest, SameSignsAndSizes) {
    BigInt num1("123");
    BigInt num2("123");


    EXPECT_TRUE(num1 == num2);

    BigInt num3("1234");
    BigInt num4("4234");

    EXPECT_FALSE(num3 == num4);
    EXPECT_FALSE(num4 == num3);

    BigInt num5("-123");
    BigInt num6("-123");


    EXPECT_TRUE(num5 == num6);

    BigInt num7("-1234");
    BigInt num8("-4234");

    EXPECT_FALSE(num7 == num8);
    EXPECT_FALSE(num8 == num7);
}
//-----------WeakLessOperator
TEST (WeakLessOperatorTest, DifSigns) {
    BigInt num1("123");
    BigInt num2("-123");


    EXPECT_FALSE(num1 <= num2);
    EXPECT_TRUE(num2 <= num1);
}

TEST (WeakLessOperatorTest, DifSizes) {
    BigInt num1("123");
    BigInt num2("12");


    EXPECT_FALSE(num1 <= num2);
    EXPECT_TRUE(num2 <= num1);
}

TEST (WeakLessOperatorTest, SameSignsAndSizes) {
    BigInt num1("123");
    BigInt num2("123");


    EXPECT_TRUE(num1 <= num2);

    BigInt num3("1234");
    BigInt num4("4234");

    EXPECT_TRUE(num3 <= num4);
    EXPECT_FALSE(num4 <= num3);

    BigInt num5("-123");
    BigInt num6("-123");


    EXPECT_TRUE(num5 <= num6);

    BigInt num7("-1234");
    BigInt num8("-4234");

    EXPECT_FALSE(num7 <= num8);
    EXPECT_TRUE(num8 <= num7);
}
//-----------NotEqualOperator
TEST (NotEqualOperatorTest, DifSigns) {
    BigInt num1("123");
    BigInt num2("-123");


    EXPECT_TRUE(num1 != num2);
    EXPECT_TRUE(num2 != num1);
}

TEST (NotEqualOperatorTest, DifSizes) {
    BigInt num1("123");
    BigInt num2("12");


    EXPECT_TRUE(num1 != num2);
    EXPECT_TRUE(num2 != num1);
}

TEST (NotEqualOperatorTest, SameSignsAndSizes) {
    BigInt num1("123");
    BigInt num2("123");


    EXPECT_FALSE(num1 != num2);

    BigInt num3("1234");
    BigInt num4("4234");

    EXPECT_TRUE(num3 != num4);
    EXPECT_TRUE(num4 != num3);

    BigInt num5("-123");
    BigInt num6("-123");


    EXPECT_FALSE(num5 != num6);

    BigInt num7("-1234");
    BigInt num8("-4234");

    EXPECT_TRUE(num7 != num8);
    EXPECT_TRUE(num8 != num7);
}
//-----------StrongMoreOperator
TEST (StrongMoreOperatorTest, DifSigns) {
    BigInt num1("123");
    BigInt num2("-123");


    EXPECT_TRUE(num1 > num2);
    EXPECT_FALSE(num2 > num1);
}

TEST (StrongMoreOperatorTest, DifSizes) {
    BigInt num1("123");
    BigInt num2("12");


    EXPECT_TRUE(num1 > num2);
    EXPECT_FALSE(num2 > num1);
}

TEST (StrongMoreOperatorTest, SameSignsAndSizes) {
    BigInt num1("123");
    BigInt num2("123");


    EXPECT_FALSE(num1 > num2);

    BigInt num3("1234");
    BigInt num4("4234");

    EXPECT_FALSE(num3 > num4);
    EXPECT_TRUE(num4 > num3);

    BigInt num5("-123");
    BigInt num6("-123");


    EXPECT_FALSE(num5 > num6);

    BigInt num7("-1234");
    BigInt num8("-4234");

    EXPECT_TRUE(num7 > num8);
    EXPECT_FALSE(num8 > num7);
}
//-----------WeakMoreOperator
TEST (WeakMoreOperatorTest, DifSigns) {
    BigInt num1("123");
    BigInt num2("-123");


    EXPECT_TRUE(num1 > num2);
    EXPECT_FALSE(num2 > num1);
}

TEST (WeakMoreOperatorTest, DifSizes) {
    BigInt num1("123");
    BigInt num2("12");


    EXPECT_TRUE(num1 > num2);
    EXPECT_FALSE(num2 > num1);
}

TEST (WeakMoreOperatorTest, SameSignsAndSizes) {
    BigInt num1("123");
    BigInt num2("123");


    EXPECT_FALSE(num1 > num2);

    BigInt num3("1234");
    BigInt num4("4234");

    EXPECT_FALSE(num3 > num4);
    EXPECT_TRUE(num4 > num3);

    BigInt num5("-123");
    BigInt num6("-123");


    EXPECT_FALSE(num5 > num6);

    BigInt num7("-1234");
    BigInt num8("-4234");

    EXPECT_TRUE(num7 > num8);
    EXPECT_FALSE(num8 > num7);
}
//-----------
//-----------SumOperator
TEST (SumOperatorTest, BothPositive) {
    BigInt num1("19");
    BigInt num2("27");
    BigInt num3("46");

    EXPECT_EQ(num1 + num2, num3);

    BigInt num4("99");
    BigInt num5("199");
    BigInt num6("298");

    EXPECT_EQ(num4 + num5, num6);
}

TEST (SumOperatorTest, BothNegative) {
    BigInt num1("-19");
    BigInt num2("-27");
    BigInt num3("-46");

    EXPECT_EQ(num1 + num2, num3);

    BigInt num4("-99");
    BigInt num5("-199");
    BigInt num6("-298");

    EXPECT_EQ(num4 + num5, num6);
}

TEST (SumOperatorTest, FirstNegativeSecondPositive) {
    BigInt num1("-9955");
    BigInt num2("10000");
    BigInt num3("45");

    EXPECT_EQ(num1 + num2, num3);

    BigInt num4("-10000");
    BigInt num5("9955");
    BigInt num6("-45");

    EXPECT_EQ(num4 + num5, num6);

    BigInt num7("-4321");
    BigInt num8("1234");
    BigInt num9("-3087");
}

TEST (SumOperatorTest, FirstPositiveSecondNegative) {
    BigInt num1("9955");
    BigInt num2("-10000");
    BigInt num3("-45");

    EXPECT_EQ(num1 + num2, num3);

    BigInt num4("10000");
    BigInt num5("-9955");
    BigInt num6("45");

    EXPECT_EQ(num4 + num5, num6);

    BigInt num7("4321");
    BigInt num8("-1234");
    BigInt num9("3087");
}

TEST (SumOperatorTest, BigIntAndInt32_t) {
    BigInt num1("123");
    int32_t num2 = -124;
    BigInt num3("-1");

    EXPECT_EQ(num1 + num2, num3);
}
//-----------DifOperator
TEST (DifOperatorTest, BothPositive) {
    BigInt num1("9955");
    BigInt num2("10000");
    BigInt num3("-45");

    EXPECT_EQ(num1 - num2, num3);

    BigInt num4("10000");
    BigInt num5("9955");
    BigInt num6("45");

    EXPECT_EQ(num4 - num5, num6);

    BigInt num7("4321");
    BigInt num8("1234");
    BigInt num9("3087");
}

TEST (DifOperatorTest, BothNegative) {
    BigInt num1("-9955");
    BigInt num2("-10000");
    BigInt num3("45");

    EXPECT_EQ(num1 - num2, num3);

    BigInt num4("-10000");
    BigInt num5("-9955");
    BigInt num6("-45");

    EXPECT_EQ(num4 - num5, num6);

    BigInt num7("-4321");
    BigInt num8("-1234");
    BigInt num9("-3087");
}

TEST (DifOperatorTest, FirstNegativeSecondPositive) {
    BigInt num1("-19");
    BigInt num2("27");
    BigInt num3("-46");

    EXPECT_EQ(num1 - num2, num3);

    BigInt num4("-99");
    BigInt num5("199");
    BigInt num6("-298");

    EXPECT_EQ(num4 - num5, num6);
}

TEST (DifOperatorTest, FirstPositiveSecondNegative) {
    BigInt num1("19");
    BigInt num2("-27");
    BigInt num3("46");

    EXPECT_EQ(num1 - num2, num3);

    BigInt num4("99");
    BigInt num5("-199");
    BigInt num6("298");

    EXPECT_EQ(num4 - num5, num6);
}

TEST (DifOperatorTest, BigIntAndInt32_t) {
    BigInt num1("-123");
    int32_t num2 = -124;
    BigInt num3("1");

    EXPECT_EQ(num1 - num2, num3);
}
//-----------MultOperator
TEST (MultOperatorTest, OneAndZero) {
    BigInt num1("1");
    BigInt num2("100");

    EXPECT_EQ(num1 * num2, num2);

    BigInt num3("0");
    BigInt num4("19");
    BigInt num5("-19");

    EXPECT_EQ(num3 * num4, num3);
    EXPECT_EQ(num3 * num5, num3);
}

TEST (MultOperatorTest, BothPositive) {
    BigInt num1("2");
    BigInt num2("3");
    BigInt num3("6");

    EXPECT_EQ(num1 * num2, num3);

    BigInt num4("99");
    BigInt num5("9801");

    EXPECT_EQ(num4 * num4, num5);
}

TEST (MultOperatorTest, BothNegative) {
    BigInt num1("-2");
    BigInt num2("-3");
    BigInt num3("6");

    EXPECT_EQ(num1 * num2, num3);

    BigInt num4("-99");
    BigInt num5("9801");

    EXPECT_EQ(num4 * num4, num5);
}

TEST (MultOperatorTest, FirstPositiveSecondNegative) {
    BigInt num1("2");
    BigInt num2("-3");
    BigInt num3("-6");

    EXPECT_EQ(num1 * num2, num3);

    BigInt num4("-99");
    BigInt num5("99");
    BigInt num6("-9801");

    EXPECT_EQ(num4 * num5, num6);
}

TEST (MultOperatorTest, FirstNegativeSecondPositive) {
    BigInt num1("-2");
    BigInt num2("3");
    BigInt num3("-6");

    EXPECT_EQ(num1 * num2, num3);

    BigInt num4("99");
    BigInt num5("-99");
    BigInt num6("-9801");

    EXPECT_EQ(num4 * num5, num6);
}

TEST (MultOperationTest, BigIntAndInt32_t) {
    BigInt num1("-2");
    int32_t num2 = 3;
    BigInt num3("-6");

    EXPECT_EQ(num1 * num2, num3);

    BigInt num4("-99");
    int32_t num5 = -99;
    BigInt num6("9801");

    EXPECT_EQ(num4 * num5, num6);
}