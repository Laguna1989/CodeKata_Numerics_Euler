# Overview

This is a Code Kata about the explicit euler integration method.

# Theory

## Integration of ordinary differential equations

## Explicit Euler integration

Let's consider the ordinary differential equation `dy / dt = f(y)`.

This can be written as a discrete term: `(y(t+delta) - y(t)) / delta = f(y(t))`. The vairable `delta` is the discrete  
step size.

Solving the equation for `y(t+delta)` yields `y(t+delta) = f(y(t)) * delta + y(t)`. This can also be written as  
`ynext = func(y) * delta + y`, which is called the explicit Euler integration scheme.

The explicit Euler integration scheme is an easy integration scheme. It can be implemented very quickly and yields  
results without too much hassle. However, it mostly requires a small discrete step size `delta` (which means lots of  
calculations), as it can become unstable quickly for increasing values of `delta`.

# Exercise

## Implementation

Implement the explicit Euler integration scheme in the file `src/euler.hpp`.

* Start with the function `explicit_euler_integrate_one_step`, which will just calculate one step of the euler
  integration.
* The unit tests in `tests/euler_unittests.cpp` will guide you towards the correct implementation.
* Once one step works, implement the function `explicit_euler_integrate` which will perform an euler integration for
  multiple steps.
* You can ignore the other test files for now.

### Hint

As the euler integration is a template function, it needs to be defined in the header.

## Exponential function

Consider the equation  
`dy(t)/dt = y(t)`. This means `func(y) = y`. The initial value in this example is chosen as `y0 = 1`.

When solved analytically via separation of variables, this results in the equation  
`y = exp(t) + C`with `C = 0`.

- The file `tests/euler_exp_test.cpp` will use the implementation to solve the ordinary differential equation listed
  above. For starters, the test uses a step size of `delta = 0.001` and integrates the function in the range `[0,3]`.
- Use a plotting program of your choice (matplotlib, gnuplot, ...) to visualize the integration. Plot the  
  file `euler_exp.txt` which is written by the test.
- Experiment with different step sizes `delta = {0.0001, 0.001, 0.01, 0.1, 0.2}`. Compare the analytic solution to the  
  numerically integrated one.

## Equation of motion

### Physical explanation

The euler integration can be applied to scalar functions as in the example above or to vector functions.

This second example will plot a free fall trajectory in two dimensions. Assume a physical object of mass `m`, which
starts with

velocity <img src="https://render.githubusercontent.com/render/math?math=%24%5Cvec%7Bv_0%7D%20%3D%20%5Cbegin%7Bpmatrix%7Dv_%7Bx0%7D%20%5C%5C%20v_%7By0%7D%5Cend%7Bpmatrix%7D%24"> at position <img src="https://render.githubusercontent.com/render/math?math=%24%5Cvec%7Bp_0%7D%20%3D%20%5Cbegin%7Bpmatrix%7Dp_%7Bx0%7D%20%5C%5C%20p_%7By0%7D%5Cend%7Bpmatrix%7D%24">

There are two forces, which act on the body:

- Gravity <img src="https://render.githubusercontent.com/render/math?math=%24%5Cvec%7BF_G%7D%20%3D%20%5Cbegin%7Bpmatrix%7D0%20%5C%5C%20-9.81%5Cend%7Bpmatrix%7D%24">

- Stokes
  Friction : <img src="https://render.githubusercontent.com/render/math?math=%24%5Cvec%7BF_S%7D%20%3D%20-k%5Cvec%7Bv%7D%24">
  . k is the friction strength.

Thus the equation of motion
is <img src="https://render.githubusercontent.com/render/math?math=%24%5Cvec%7BF%7D%20%3D%20%5Cvec%7BF_G%7D%20%2B%20%5Cvec%7BF_S%7D%20%3D%20m%20%5Ccdot%20%5Cvec%7Ba%7D%20%3D%20m%20%5Ccdot%20%5Cdot%7B%5Cvec%7Bv%7D%7D%24">
. If we assume m=1, we can write it as a discrete equation `func(v) = (FG + FS(v))`.

### Integrating velocity

First, let's integrate the velocity based on the acceleration. This can be done in the
file `tests/euler_equation_of_motion_test.cpp` in the function `calculate_one_free_fall`.

### Integrate position

Based on the just calculated velocity value, use the euler integration to calculate the new position.


### Hint

In C++ the `std::valarray` class is a very useful type to get vector math done quickly.
See [cppreference](https://en.cppreference.com/w/cpp/numeric/valarray) for further info.

# Further Reading

[Khan Academy on the euler method](https://www.youtube.com/watch?v=q87L9R9v274&ab_channel=FireflyLectures)