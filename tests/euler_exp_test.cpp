
#include "euler.hpp"
#include <gtest/gtest.h>
#include <fstream>

TEST(EulerExponential, Exponential)
{
    auto const func = [](double y) { return y; };
    double const y0 = 1.0;
    double const delta = 0.001;

    auto const values = explicit_euler_integrate<double>(func,y0, delta,0.0,3.0);

    std::ofstream file{"euler_exp.txt"};
    for (auto const& kvp : values)
    {
        std::cout << kvp.first << " " << exp( kvp.first) << " " << kvp.second << std::endl;
        file << kvp.first << " " << exp( kvp.first) << " " << kvp.second << std::endl;
    }
}