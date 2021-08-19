import numpy as np
import matplotlib.pyplot as plt

from euler import explicit_euler_integrate_one_step


def calculate_one_free_Fall(k_string):
    k = float(k_string)
    v0 = [2.0, 10.0]
    p0 = [0.0, 0.0]

    def force(v):
        nonlocal k
        return np.asarray([0.0, -9.81]) - k * np.asarray(v)

    t_start = 0.0
    t_end = 3.0
    delta = 0.01

    t = t_start
    v = v0
    p = p0

    data = {}
    while t <= t_end:
        data[t] = p
        v = explicit_euler_integrate_one_step(force, v, delta)

        def v_func(x):
            nonlocal v
            return v

        p = explicit_euler_integrate_one_step(v_func, p, delta)

        t += delta

    return data


def test_integrate_free_fall():
    k_values = ["0", "0.1", "0.4", "1.0", "4.0"]

    fig = plt.figure()
    ax = fig.add_subplot()

    plt.xlabel('x position')
    plt.ylabel('y position')

    plt.ylim([0, 5.5])
    plt.xlim([0, 4.5])

    for k in k_values:
        data = calculate_one_free_Fall(k)
        xs = list(map(lambda kvp: kvp[0], data.values()))
        ys = list(map(lambda kvp: kvp[1], data.values()))

        ax.scatter(xs, ys, label='k=' + k)
        max_index = ys.index(max(ys))
        max_x = xs[max_index]
        max_y = ys[max_index]

        if k == '0':
            ax.text(max_x - 0.0, max_y + 0.2, 'k=' + k)
        else:
            ax.text(max_x - 0.2, max_y - 0.5, 'k=' + k)

    #plt.show()
