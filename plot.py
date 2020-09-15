import matplotlib.pyplot as plt
from data import data

Ys = data[1::2]
xs = data[::2]

plt.plot(xs, Ys, 'o-')
plt.savefig("stream.png")