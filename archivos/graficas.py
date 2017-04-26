import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import imageio
import os
import pylab
import numpy as np

n = 29 # Número de iteraciones del programa

# Crear imágenes con las placas
for i in range(n):
    data_img=np.loadtxt(str(i)+'.txt')
    plt.gcf().clear()
    plt.imshow(data_img)
    plt.colorbar()
    plt.savefig(str(i)+'.png')

def hacer_gif(n, titulo = 'calentamiento.gif'):
    imagenes = []
    nombres = []
    for i in range(n)
        nombres.append(unicode(str(i)+".png"))
    for nombre in nombres:
        imagenes.append(imageio.imread(nombre))
    imageio.mimsave(titulo, imagenes)

hacer_gif(n)