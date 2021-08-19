import numpy as np


def explicit_euler_integrate_one_step(f, y0, delta):
    return np.asarray(f(y0)) * delta + y0


def explicit_euler_integrate(f, y0, delta, t_start, t_end):
    values = {}

    t = t_start
    y = y0

    while t <= t_end:
        values[t] = y
        y = explicit_euler_integrate_one_step(f, y, delta)
        t += delta
    return values