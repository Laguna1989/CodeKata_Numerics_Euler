import numpy as np
import matplotlib.pyplot as plt

from numpy import sqrt
from euler import explicit_euler_integrate_one_step


def test_euler_planetary_motion():
    p_sun = [0.0, 0.0]
    v0 = [0.1, 0.0]
    p0 = [1.0, 8.0]

    t_start = 0.0
    t_end = 90.0
    delta = 0.02

    t = t_start
    v = v0
    p = p0

    data = {}


    while t <= t_end:
        data[t] = p

        def force(v):
            nonlocal p
            nonlocal p_sun
            # to be implemented by user
            # TODO
            return [0.0, 0.0]

        v = explicit_euler_integrate_one_step(force, v, delta)

        def v_func(x):
            nonlocal v
            return v

        p = explicit_euler_integrate_one_step (v_func, p, delta)

        t += delta

    fig = plt.figure()
    ax = fig.add_subplot()

    plt.xlabel('x position')
    plt.ylabel('y position')

    plt.xlim([-5.5, 5.5])
    plt.ylim([-11, 11])

    xs = list(map(lambda kvp: kvp[0], data.values()))
    ys = list(map(lambda kvp: kvp[1], data.values()))

    ax.scatter(xs, ys)
    # plt.show()