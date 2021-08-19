#include "euler.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

auto const_func = [](double /*v*/) { return 5.0; };

TEST(OneStepTest, CallsFunction)
{
    bool has_been_called { false };
    explicit_euler_integrate_one_step<double>(
        [&has_been_called](double /*unused*/) {
            has_been_called = true;
            return 0.0;
        },
        0.0, 0.0);
    ASSERT_TRUE(has_been_called);
}

TEST(OneStepTest, ReturnsY0ForDeltaZero)
{
    ASSERT_EQ(explicit_euler_integrate_one_step<double>(const_func, 1.0, 0.0), 1.0);
}

TEST(OneStepTest, ReturnsCorrectValueForDelta1)
{
    ASSERT_EQ(5.0, explicit_euler_integrate_one_step<double>(const_func, 0.0, 1.0));
}

TEST(OneStepTest, ReturnsCorrectValueForDelta2)
{
    ASSERT_EQ(10.0, explicit_euler_integrate_one_step<double>(const_func, 0.0, 2.0));
}
TEST(OneStepTest, ReturnsCorrectValueForDelta00001)
{
    ASSERT_EQ(00001 * 5.0, explicit_euler_integrate_one_step<double>(const_func, 0.0, 00001));
}

class EulerUnitTestReturnedMapSizeTestFixture
    : public ::testing::TestWithParam<std::tuple<double, std::size_t>> {
};

// integrate from 0 to 1 and check that for a given delta the correct amount of points is contained.
TEST_P(EulerUnitTestReturnedMapSizeTestFixture, ReturnedMapContainsCorrectAmountOfEntries)
{
    auto const delta = std::get<0>(GetParam());
    auto const expected_size = std::get<1>(GetParam());
    auto values = explicit_euler_integrate<double>(const_func, 0.0, delta, 0.0, 1.0);
    ASSERT_EQ(values.size(), expected_size);
}

INSTANTIATE_TEST_SUITE_P(EulerUnitTestReturnedMapSizeTest, EulerUnitTestReturnedMapSizeTestFixture,
    ::testing::Values(
        std::make_tuple<double, std::size_t>(1.5, 1), // only the start point contained
        std::make_tuple<double, std::size_t>(1.0, 2), // start point and end point contained
        std::make_tuple<double, std::size_t>(0.5, 3), // start, end and one midpoint contained
        std::make_tuple<double, std::size_t>(0.1, 11))); // start, end and 9 points contained

class EulerUnitTestReturnedMapValuesTestFixture : public ::testing::TestWithParam<double> {
};

TEST_P(EulerUnitTestReturnedMapValuesTestFixture, ReturnedMapContainsTRangeStart)
{
    auto const delta = GetParam();
    auto values = explicit_euler_integrate<double>(const_func, 0.0, delta, 0.0, 1.0);
    ASSERT_DOUBLE_EQ(values.cbegin()->first, 0.0);
}
TEST_P(EulerUnitTestReturnedMapValuesTestFixture, ReturnedMapContainsTRangeEnd)
{
    auto const delta = GetParam();
    auto values = explicit_euler_integrate<double>(const_func, 0.0, delta, 0.0, 1.0);
    ASSERT_DOUBLE_EQ((--values.cend())->first, 1.0);
}

TEST_P(EulerUnitTestReturnedMapValuesTestFixture,
    ReturnedMapContainsCorrectValueForOneIterationPointAndConstantFunction)
{
    auto const delta = GetParam();
    auto values = explicit_euler_integrate<double>(const_func, 0.0, delta, 0.0, 1.0);

    double value = (--values.cend())->second;
    double const deviation = value - const_func(1);
    ASSERT_LT(deviation, 1e-5);
}

INSTANTIATE_TEST_SUITE_P(EulerUnitTestReturnedMapValuesTest,
    EulerUnitTestReturnedMapValuesTestFixture, ::testing::Values(1.0, 0.5, 0.1));
