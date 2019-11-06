import matplotlib.pyplot as plt
import imageio
import numpy as np

N = 30 # Numero de archivos creados por el programa en C
imagenes = [] # Lista para guardar las imagenes generadas
nombres = [] # Lista para armar los nombres de las imagenes
titulo = 'calentamiento.gif' # Nombre del gif que se creara

# Iterar sobre cada archivo
for i in range(N):
    # Crear imagenes con las placas
    data_img=np.loadtxt(str(i)+'.txt') # Cargar archivo con el estado de la placa
    plt.gcf().clear() # Limpiar grafico previo
    plt.imshow(data_img) # Crear imagen
    plt.colorbar()  # Mostrar la escala utilizada
    plt.savefig(str(i)+'.png') # Guardar imagen
    nombres.append(str(i)+".png") # Guardar nombre de la imagen

# Crear gif
for nombre in nombres:
    imagenes.append(imageio.imread(nombre)) # Anadir imagen a la lista
    
imageio.mimsave(titulo, imagenes) # Guardar gif
