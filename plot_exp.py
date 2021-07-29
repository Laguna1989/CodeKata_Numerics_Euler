import matplotlib.pyplot as plt

xs = []
ys = []
zs = []

with open('euler_exp.txt') as f:
    for line in f:
        x, y, z = line.split()
        xs.append(float(x))
        ys.append(float(y))
        zs.append(float(z))

fig = plt.figure()
ax = fig.add_subplot()

ax.scatter(xs, ys)
ax.scatter(xs, zs)

plt.show()
