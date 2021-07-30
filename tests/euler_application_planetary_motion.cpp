#include "euler.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <valarray>

using Vec2 = std::valarray<double>;

TEST(EulerApplication, PlanetaryMotion)
{
    Vec2 p_sun { 0.0, 0.0 };

    Vec2 v0 { 0.1, 0.0};
    Vec2 p0 { 1.0, 8 };

    double t_start = 0.0;
    double t_end = 90.0;
    double delta = 0.02;

    double t = t_start;
    Vec2 v = v0;
    Vec2 p = p0;

    std::string const filename = "planetary_motion.pos.dat.txt";
    std::ofstream file { filename };
    while (t <= t_end) {
        // write out the current position
        file << t << " " << p[0] << " " << p[1] << std::endl;

        auto force = [p, p_sun](std::valarray<double> /*v*/) {
            // Plug in force equation
            // TODO
            return std::valarray<double>{0.0, 0.0};
        };

        // integrate velocity first
        v = explicit_euler_integrate_one_step<Vec2>(force, v, delta);

        // integrate position second
        p = explicit_euler_integrate_one_step<Vec2>(
            [&v](Vec2 /*unused*/) { return v; }, p, delta);

        // increment time
        t += delta;
    }
}