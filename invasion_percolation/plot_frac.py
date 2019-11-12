import matplotlib.pyplot as plt
import numpy as np

plt.scatter(*np.loadtxt("files/fractal.dat", unpack = True), marker = 'o')
plt.savefig("files/fractal.png")
