#include "euler.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <valarray>
#include <map>
#include "plotter.hpp"

using Vec2 = std::valarray<double>;
using Vec2Map = std::map<double, Vec2>;

TEST(EulerApplication, PlanetaryMotion)
{
    Vec2 p_sun { 0.0, 0.0 };

    Vec2 v0 { 0.1, 0.0 };
    Vec2 p0 { 1.0, 8 };

    double t_start = 0.0;
    double t_end = 90.0;
    double delta = 0.02;

    double t = t_start;
    Vec2 v = v0;
    Vec2 p = p0;
    Vec2Map data;

    std::string const filename = "planetary_motion.pos.dat.txt";
    std::ofstream file { filename };
    while (t <= t_end) {
        // write out the current position
        file << t << " " << p[0] << " " << p[1] << std::endl;
        data[t] = p;

        auto force = [p, p_sun](std::valarray<double> /*v*/) {
            // Plug in force equation
            auto p_diff = p_sun - p;
            double const r = sqrt(p_diff[0] * p_diff[0] + p_diff[1] * p_diff[1]);
            p_diff /= r;

            return p_diff / r / r * 0.5;
        };

        // integrate velocity first
        v = explicit_euler_integrate_one_step<Vec2>(force, v, delta);

        // integrate position second
        p = explicit_euler_integrate_one_step<Vec2>([&v](Vec2 /*unused*/) { return v; }, p, delta);

        // increment time
        t += delta;
    }

    Plotter plotter;
    plotter.set_xrange(-5.5, 5.5);
    plotter.set_yrange(-11, 11);
    plotter.add_data(data);
    plotter.write_png("planetary_motion.png", 800,800 );
}
