import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import csv
import sys

from latex_common import *


ticks = []
vals = []
with open(sys.argv[1], newline='') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=",")
	for row in spamreader:
		ticks = row[1::2]
		vals = row[2::2]
		break
	
#ticks = ticks[::-1]
#vals = vals[::-1]

ticks = [int(v) for v in ticks]
vals = [float(v) for v in vals]
ticks, vals = zip(*sorted(zip(ticks, vals)))

print(ticks, vals)

latexify(fig_width=6, fig_height=5, font_size=12, tick_size=12)

fix, ax = plt.subplots()

format_axes(ax, hide=['top', 'right'], show=['bottom', 'left'])

a2, = ax.plot(ticks, vals, 'o--')
#a3, = ax.plot(xs, Ys_guided, 'o--')

ax.set_xlabel("Number of threads")
ax.set_ylabel("Execution  time (s)")
plt.tight_layout()

plt.savefig(sys.argv[2]) # out folder is the first arg
