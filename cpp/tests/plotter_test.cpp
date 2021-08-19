#include "plotter.hpp"
#include <gtest/gtest.h>

TEST(PlotterTest, OnePoint)
{
    std::map<double, std::valarray<double>> data;

    data[0] = std::valarray<double> { 0.5, 1.0 };

    Plotter plotter;
    plotter.set_yrange(0.0, 2.0);
    plotter.add_data(data);
    plotter.write_png("out2.png", 20, 20);
}
