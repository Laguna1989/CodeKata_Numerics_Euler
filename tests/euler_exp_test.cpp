
#include "euler.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <plotter.hpp>

TEST(EulerExponential, Exponential)
{
    auto const func = [](double y) { return y; };
    double const y0 = 1.0;
    double const delta = 0.001;
    double const t_end = 3.0;

    auto const values = explicit_euler_integrate<double>(func, y0, delta, 0.0, t_end);

    std::ofstream file { "euler_exp.txt" };
    for (auto const& kvp : values) {
        file << kvp.first << " " << exp(kvp.first) << " " << kvp.second << std::endl;
    }

    std::map<double, std::valarray<double>> data;
    for (auto const& kvp : values) {
        data[kvp.first] = std::valarray<double> { kvp.second };
    }

    Plotter plotter;
    plotter.set_xrange(-0.5, 3.5);
    plotter.set_yrange(0, 22.5);
    plotter.add_data(data);
    plotter.write_png("exp.png", 800, 800);
}
