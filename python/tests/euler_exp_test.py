from math import exp
import pytest
import matplotlib.pyplot as plt

from euler import explicit_euler_integrate


def test_euler_exponential():
    def f(y):
        return y

    y0 = 1
    delta = 0.001
    t_end = 3.0

    values = explicit_euler_integrate(f, y0, delta, 0.0, t_end)

    xs = list(values.keys())
    ys = list(map(lambda x: exp(x), values.keys()))
    zs = list(values.values())

    fig = plt.figure()
    ax = fig.add_subplot()

    ax.scatter(xs, ys)
    ax.scatter(xs, zs)

    # plt.show()

