#ifndef RANDU_HPP_GUARD
#define RANDU_HPP_GUARD

#include <cmath>
#include <cstdint>
#include <functional>
#include <map>

template <typename T>
T explicit_euler_integrate_one_step(std::function<T(T)> func, T y0, double delta)
{
    // implementation needed
    // TODO

    // fake implementation
    return y0;
}

template <typename T>
std::map<double, T> explicit_euler_integrate(
    std::function<T(T)> func, T y0, double delta, double t_start, double t_end)
{

    // implementation needed
    // TODO

    // fake implementation
    std::map<double, T> values;
    values[42.0] = y0 * 42.0;
    return values;
}

#endif