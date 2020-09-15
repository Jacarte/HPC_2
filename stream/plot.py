import matplotlib.pyplot as plt
from data import data
import sys

from latex_common import *

Ys = data[1::2]
xs = data[::2]


latexify(fig_width=6, fig_height=5, font_size=12, tick_size=12)

fix, ax = plt.subplots()

format_axes(ax, hide=['top', 'right'], show=['bottom', 'left'])

ax.plot(xs, Ys, 'o-')
ax.set_xlabel("Number of threads")
ax.set_ylabel("Copy bandwidth")

plt.savefig(sys.argv[1]) # out folder is the first arg