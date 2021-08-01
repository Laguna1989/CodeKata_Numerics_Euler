import matplotlib.pyplot as plt

        
fig = plt.figure()
ax = fig.add_subplot()
plt.xlabel('x position')
plt.ylabel('y position')

plt.ylim([0,5.5])

for k in ['0', '0.1', '0.4', '1.0'] :
    pts = []
    pxs = []
    pys = []
    filename = 'free_fall_parabola.pos.k' + k + '.dat.txt'
    with open(filename) as f:
        for line in f:
            pt, px, py = line.split()
            if float(py) >= 0 : 
                pts.append(float(pt))
                pxs.append(float(px))
                pys.append(float(py))

    ax.scatter(pxs, pys, label='k='+k)
    max_index = pys.index(max(pys))
    max_x = pxs[max_index]
    max_y = pys[max_index]
    
    if k == '0':
        ax.text(max_x-0.0, max_y +0.2, 'k='+k)
    else:
        ax.text(max_x-0.2, max_y -0.5, 'k='+k)
    
plt.show()
fig.savefig('freefall.png', format='png',dpi=500)