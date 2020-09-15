import matplotlib.pyplot as plt
from data import data_static, data_guided, data_dynamic
import sys

from latex_common import *

Ys_static = data_static[1::2]
Ys_dynamic = data_dynamic[1::2]
Ys_guided = data_guided[1::2]
xs = data_static[::2]


latexify(fig_width=6, fig_height=5, font_size=12, tick_size=12)

fix, ax = plt.subplots()

format_axes(ax, hide=['top', 'right'], show=['bottom', 'left'])

a1, = ax.plot(xs, Ys_static, 'o--')
ax.grid()

plt.savefig(sys.argv[1]) # out folder is the first arg


a2, = ax.plot(xs, Ys_dynamic, 'o--')
a3, = ax.plot(xs, Ys_guided, 'o--')
ax.set_xlabel("Number of threads")
ax.set_ylabel("Copy bandwidth")
plt.legend( [a1, a2, a3],["Static schedule", "Dynamic schedule", "Guided schedule"])

plt.savefig(sys.argv[2]) # out folder is the first arg
