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

velocity $\vec{v_0} = \begin{pmatrix}v_{x0} \\ v_{y0}\end{pmatrix}$ at position $\vec{p_0} = \begin{pmatrix}p_{x0} \\ p_
{y0}\end{pmatrix}$

There are two forces, which act on the body:

- Gravity $\vec{F_G} = m \cdot \vec{g} $ with $\vec{g} = \begin{pmatrix}0\\-9.81\end{pmatrix}$

- Stokes Friction : $\vec{F_S} = -k\vec{v}$. k is the friction strength.

Thus the equation of motion is $\vec{F} = \vec{F_G} + \vec{F_S} = m \cdot \vec{a} = m \cdot \dot{\vec{v}}$ .

As a discrete equation this can be written as `func(v) = (FG + FS(v)) / m`.

### Implementing


### Hint

In C++ the `std::valarray` class is a very useful type to get vector math done quickly.
See [cppreference](https://en.cppreference.com/w/cpp/numeric/valarray) for further info.

# Further Reading

[Khan Academy on the euler method](https://www.youtube.com/watch?v=q87L9R9v274&ab_channel=FireflyLectures)