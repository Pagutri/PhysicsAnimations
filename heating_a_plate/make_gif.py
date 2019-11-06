import matplotlib.pyplot as plt
import imageio
import numpy as np

N = 30 # Number of files created for the C program
images = []
names = []
title = 'plate_heating.gif'

for i in range(N):
    data_img = np.loadtxt('files/' + str(i) + '.txt')
    plt.gcf().clear()
    plt.imshow(data_img)
    plt.colorbar()
    plt.savefig('files/' + str(i) + '.png')
    names.append('files/' + str(i) + '.png')

for name in names:
    images.append(imageio.imread(name))
    
imageio.mimsave(title, images)
