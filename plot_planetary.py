import matplotlib.pyplot as plt

        
fig = plt.figure()
ax = fig.add_subplot()
plt.xlabel('x position')
plt.ylabel('y position')

plt.ylim([-11,11])
plt.xlim([-5.5, 5.5])

pts = []
pxs = []
pys = []
filename = 'planetary_motion.pos.dat.txt'
with open(filename) as f:
    for line in f:
        pt, px, py = line.split()
        pts.append(float(pt))
        pxs.append(float(px))
        pys.append(float(py))

ax.scatter(pxs, pys)
max_index = pys.index(max(pys))
max_x = pxs[max_index]
max_y = pys[max_index]

    
plt.show()