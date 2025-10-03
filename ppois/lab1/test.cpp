#include <gtest/gtest.h>
#include "../longint.h"
#include <sstream>

using namespace std;

TEST(LongIntConstructorTest, DefaultConstructor) {
    LongInt num;
    EXPECT_FALSE(num.isZero()); 
    EXPECT_EQ(string("0"), string(num)); 
}

TEST(LongIntConstructors, StringConstructorPositive) {
    LongInt num1("123");
    LongInt num2("000000000456");
    LongInt num3("1");
    LongInt num4("12345678901234567890");

    EXPECT_EQ("123", streamLongInt(num1));
    EXPECT_EQ("456", streamLongInt(num2));
    EXPECT_EQ("1", streamLongInt(num3));
    EXPECT_EQ("12345678901234567890", streamLongInt(num4));
    EXPECT_FALSE(num1.isZero());
    EXPECT_FALSE(num2.isZero());
    EXPECT_FALSE(num3.isZero());
}

TEST(LongIntConstructors, StringConstructorNegative) {
    LongInt num1("-123");
    LongInt num2("-0000000000456");
    LongInt num3("-1");
    LongInt num4("-12345678901234567890");

    EXPECT_EQ("-123", streamLongInt(num1));
    EXPECT_EQ("-456", streamLongInt(num2));
    EXPECT_EQ("-1", streamLongInt(num3));
    EXPECT_EQ("-12345678901234567890", streamLongInt(num4));
    EXPECT_FALSE(num1.isZero());
    EXPECT_FALSE(num2.isZero());
    EXPECT_FALSE(num3.isZero());
}

TEST(LongIntConstructors, StringConstructorZero) {
    LongInt num1("0");
    LongInt num2("0000");
    LongInt num3("-0");
    LongInt num4("-0000");

    EXPECT_EQ("0", streamLongInt(num1));
    EXPECT_EQ("0", streamLongInt(num2));
    EXPECT_EQ("0", streamLongInt(num3)); 
    EXPECT_EQ("0", streamLongInt(num4));
    EXPECT_TRUE(num1.isZero());
    EXPECT_TRUE(num2.isZero());
    EXPECT_TRUE(num3.isZero());
    EXPECT_TRUE(num4.isZero());
}

TEST(LongIntConstructors, StringConstructorExceptions) {
    EXPECT_THROW(LongInt num(""), invalid_argument);
    EXPECT_THROW(LongInt num("abc"), invalid_argument);
    EXPECT_THROW(LongInt num("12a34"), invalid_argument);
    EXPECT_THROW(LongInt num("12-34"), invalid_argument);
    EXPECT_THROW(LongInt num("--123"), invalid_argument);
    EXPECT_THROW(LongInt num("123-"), invalid_argument);
}

TEST(LongIntConstructors, CopyConstructor) {
    LongInt original("12345");
    LongInt copy(original);

    EXPECT_EQ(streamLongInt(original), streamLongInt(copy));
    EXPECT_EQ(original.isZero(), copy.isZero());

    LongInt temp("999");
    original = temp;
    EXPECT_EQ("12345", streamLongInt(copy));
    EXPECT_EQ("999", streamLongInt(original));
}

TEST(LongIntConstructors, RemoveLeadingZeros) {
    LongInt num1("00000789");
    LongInt num2("-00000456");
    LongInt num3("000000000000000001");
    LongInt num4("-000000000000000001");

    EXPECT_EQ("789", streamLongInt(num1));
    EXPECT_EQ("-456", streamLongInt(num2));
    EXPECT_EQ("1", streamLongInt(num3));
    EXPECT_EQ("-1", streamLongInt(num4));
}

TEST(LongIntIOOperators, InputOperatorLargeNumber) {
    istringstream iss("12345678901234567890");
    LongInt num;
    iss >> num;

    ostringstream oss;
    oss << num;
    EXPECT_EQ("12345678901234567890", oss.str());
}

TEST(LongIntIOOperators, OutputOperatorLargeNumber) {
    LongInt num("999999999999999999999");
    ostringstream oss;
    oss << num;

    EXPECT_EQ("999999999999999999999", oss.str());
}

TEST(LongIntComparisonOperators, LargeNumbers) {
    LongInt huge1("12345678901234567890");
    LongInt huge2("12345678901234567891");
    LongInt huge3("-12345678901234567890");
    LongInt huge4("-12345678901234567891");

    EXPECT_TRUE(huge1 < huge2);
    EXPECT_TRUE(huge4 < huge3);
    EXPECT_TRUE(huge3 > huge4);
    EXPECT_TRUE(huge1 <= huge2);
    EXPECT_TRUE(huge2 >= huge1);
    EXPECT_FALSE(huge1 == huge2);
    EXPECT_TRUE(huge1 != huge2);
}

TEST(LongIntAddition, LargeNumbers) {
    LongInt num1("12345678901234567890");
    LongInt num2("98765432109876543210");
    LongInt result = num1 + num2;

    EXPECT_EQ("111111111011111111100", streamLongInt(result));
}

TEST(LongIntAddition, VeryDifferentLength) {
    LongInt num1("1000000000000000000000");
    LongInt num2("1");
    LongInt result = num1 + num2;

    EXPECT_EQ("1000000000000000000001", streamLongInt(result));
}

TEST(LongIntAddition, LeadingZerosInOperands) {
    LongInt num1("000123");
    LongInt num2("000456");
    LongInt result = num1 + num2;

    EXPECT_EQ("579", streamLongInt(result));
}

TEST(LongIntAssignment, LargeNumberAssignment) {
    LongInt num1("123456789012345678901234567890");
    LongInt num2;
    num2 = num1;

    EXPECT_EQ("123456789012345678901234567890", streamLongInt(num2));
}

TEST(LongIntAddition, NegativeToZeroTransition) {
    LongInt num1("-999999999999999999999999999999");
    LongInt num2("999999999999999999999999999999");
    LongInt result = num1 + num2;

    EXPECT_EQ("0", streamLongInt(result));
    EXPECT_TRUE(result.isZero());
}

TEST(LongIntAddition, MixedSignLargeNumbersPositiveResult) {
    LongInt num1("1000000000000000000000000000000");
    LongInt num2("-999999999999999999999999999999");
    LongInt result = num1 + num2;

    EXPECT_EQ("1", streamLongInt(result));
}

TEST(LongIntAddition, NegativeWithNegative) {
    LongInt num1("-999999999999999999999999999999");
    LongInt num2("-1");
    LongInt result = num1 + num2;

    EXPECT_EQ("-1000000000000000000000000000000", streamLongInt(result));
}

TEST(LongIntAddition, LargeNegativeSelfAddition) {
    LongInt num("-999999999999999999999999999999");
    num += num;

    EXPECT_EQ("-1999999999999999999999999999998", streamLongInt(num));
}

TEST(LongIntSubtraction, LargeNumbersNegativeResult) {
    LongInt num1("9876543210987654321");
    LongInt num2("12345678901234567890");
    LongInt result = num1 - num2;

    EXPECT_EQ("-2469135690246913569", streamLongInt(result));
}

TEST(LongIntSubtraction, LargeNumbers) {
    LongInt num1("12345678901234567890");
    LongInt num2("9876543210987654321");
    LongInt result = num1 - num2;

    EXPECT_EQ("2469135690246913569", streamLongInt(result));
}

TEST(LongIntCompoundSubtraction, SelfSubtractionCompound) {
    LongInt num("123456789123456789");
    num -= num;

    EXPECT_EQ("0", streamLongInt(num));
    EXPECT_TRUE(num.isZero());
}

TEST(LongIntSubtraction, VeryLargeNegativeNumbersReverse) {
    LongInt num1("-999999999999999999999999999998");
    LongInt num2("-999999999999999999999999999999");
    LongInt result = num1 - num2;

    EXPECT_EQ("1", streamLongInt(result));
}

TEST(LongIntSubtraction, VeryLargeNegativeNumbers) {
    LongInt num1("-999999999999999999999999999999");
    LongInt num2("-999999999999999999999999999998");
    LongInt result = num1 - num2;

    EXPECT_EQ("-1", streamLongInt(result));
}

TEST(LongIntMultiplication, LargeNumbers) {
    LongInt num1("123456789");
    LongInt num2("987654321");
    LongInt result = num1 * num2;

    EXPECT_EQ("121932631112635269", streamLongInt(result));
}

TEST(LongIntMultiplicationEdgeCases, MixedSignLargeNumbers) {
    LongInt num1("-12345678901234567890");
    LongInt num2("98765432109876543210");
    LongInt result = num1 * num2;

    EXPECT_EQ("-1219326312467611632370370370370358153900", streamLongInt(result));
}

TEST(LongIntMultiplicationEdgeCases, LargeNegativeNumbers) {
    LongInt num1("-12345678901234567890");
    LongInt num2("-98765432109876543210");
    LongInt result = num1 * num2;

    EXPECT_EQ("1219326312467611632370370370370358153900", streamLongInt(result));
}

TEST(LongIntMultiplicationEdgeCases, MultiplicationByOne) {
    LongInt num("12345678901234567890");
    LongInt one("1");
    LongInt result = num * one;

    EXPECT_EQ("12345678901234567890", streamLongInt(result));
}

TEST(LongIntMultiplicationEdgeCases, MultiplicationByZero) {
    LongInt num("12345678901234567890");
    LongInt zero("0");
    LongInt result = num * zero;

    EXPECT_EQ("0", streamLongInt(result));
    EXPECT_TRUE(result.isZero());
}

TEST(LongIntMultiplication, WithLeadingZeros) {
    LongInt num1("00123");
    LongInt num2("00456");
    LongInt result = num1 * num2;

    EXPECT_EQ("56088", streamLongInt(result));
}

TEST(LongIntDivisionEdgeCases, NegativeLargeNumbers) {
    LongInt num1("-123456789012345678901234567890");
    LongInt num2("1234567890123456789");
    LongInt result = num1 / num2;

    EXPECT_EQ("-100000000000", streamLongInt(result));
}

TEST(LongIntDivisionEdgeCases, LargeDivisor) {
    LongInt num1("999999999999999999999999999999");
    LongInt num2("111111111111111111111111111111");
    LongInt result = num1 / num2;

    EXPECT_EQ("9", streamLongInt(result));
}

TEST(LongIntDivisionEdgeCases, VerySmallResult) {
    LongInt num1("1");
    LongInt num2("1000000000000000000000000000000");
    LongInt result = num1 / num2;

    EXPECT_EQ("0", streamLongInt(result));
    EXPECT_TRUE(result.isZero());
}

TEST(LongIntDivisionEdgeCases, VeryLargeDivision) {
    LongInt num1("1000000000000000000000000000000");
    LongInt num2("1000000000000000000000000000000");
    LongInt result = num1 / num2;

    EXPECT_EQ("1", streamLongInt(result));
}

TEST(LongIntCompoundDivision, DivisionByZeroCompound) {
    LongInt num("12345678901234567890");
    LongInt zero("0");

    EXPECT_THROW(num /= zero, invalid_argument);
}

TEST(LongIntDivisionEdgeCases, BothNegativeLargeNumbers) {
    LongInt num1("-123456789012345678901234567890");
    LongInt num2("-1234567890123456789");
    LongInt result = num1 / num2;

    EXPECT_EQ("100000000000", streamLongInt(result));
}

TEST(LongIntIncrementDecrement, PrefixIncrementLargeNumber) {
    LongInt num("999999999999999999999999999998");
    ++num;

    EXPECT_EQ("999999999999999999999999999999", streamLongInt(num));
}

TEST(LongIntIncrementDecrement, PostfixIncrementPositive) {
    LongInt num("5");
    LongInt oldValue = num++;

    EXPECT_EQ("6", streamLongInt(num));
    EXPECT_EQ("5", streamLongInt(oldValue));
}

TEST(LongIntIncrementDecrement, PrefixDecrementLargeNumber) {
    LongInt num("1000000000000000000000000000000");
    --num;

    EXPECT_EQ("999999999999999999999999999999", streamLongInt(num));
}

TEST(LongIntIncrementDecrement, PostfixDecrementPositive) {
    LongInt num("5");
    LongInt oldValue = num--;

    EXPECT_EQ("4", streamLongInt(num)); 
    EXPECT_EQ("5", streamLongInt(oldValue));
}

TEST(LongIntIntConversion, PositiveNumbers) {
    LongInt num1("0");
    LongInt num2("123");
    LongInt num3("2147483647");

    EXPECT_EQ(0, (int)num1);
    EXPECT_EQ(123, (int)num2);
    EXPECT_EQ(2147483647, (int)num3);
}

TEST(LongIntIntConversion, NegativeNumbers) {
    LongInt num1("-123");
    LongInt num2("-2147483648"); 

    EXPECT_EQ(-123, (int)num1);
    EXPECT_EQ(-2147483648, (int)num2);
}

TEST(LongIntIntConversion, VeryLargeNumbersClamping) {
    LongInt hugePos("999999999999999999999999999999");
    LongInt hugeNeg("-999999999999999999999999999999");
    LongInt exactlyIntMax("2147483647");
    LongInt exactlyIntMin("-2147483648");

    EXPECT_EQ(INT_MAX, (int)hugePos);
    EXPECT_EQ(INT_MIN, (int)hugeNeg);
    EXPECT_EQ(INT_MAX, (int)exactlyIntMax);
    EXPECT_EQ(INT_MIN, (int)exactlyIntMin);
}

TEST(LongIntCompareWith, LargeNumbers) {
    LongInt num1("12345678901234567890");
    LongInt num2("98765432109876543210");

    string output = captureOutput(&LongInt::compareWith, num1, num2);

    EXPECT_NE(output.find("12345678901234567890 == 98765432109876543210: false"), string::npos);
    EXPECT_NE(output.find("12345678901234567890 != 98765432109876543210: true"), string::npos);
    EXPECT_NE(output.find("12345678901234567890 >  98765432109876543210: false"), string::npos);
    EXPECT_NE(output.find("12345678901234567890 <  98765432109876543210: true"), string::npos);
}

TEST(LongIntZeroMethods, RemoveLeadingZerosPositive) {
    LongInt num1("000123");
    LongInt num2("000000456");
    LongInt num3("000000000000000789");

    num1.remove0s();
    num2.remove0s();
    num3.remove0s();

    EXPECT_EQ("123", streamLongInt(num1));
    EXPECT_EQ("456", streamLongInt(num2));
    EXPECT_EQ("789", streamLongInt(num3));
}

TEST(LongIntZeroMethods, RemoveLeadingZerosNegative) {
    LongInt num1("-000123");
    LongInt num2("-000000456");
    LongInt num3("-000000000000000789");

    num1.remove0s();
    num2.remove0s();
    num3.remove0s();

    EXPECT_EQ("-123", streamLongInt(num1));
    EXPECT_EQ("-456", streamLongInt(num2));
    EXPECT_EQ("-789", streamLongInt(num3));
}

TEST(LongIntZeroMethods, BoundaryCases) {
    LongInt num1("0");
    num1.remove0s();
    EXPECT_EQ("0", streamLongInt(num1));
    EXPECT_TRUE(num1.isZero());

    LongInt num2("7");
    num2.remove0s();
    EXPECT_EQ("7", streamLongInt(num2));
    EXPECT_FALSE(num2.isZero());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}