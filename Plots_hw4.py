###COmienza el plots de la tarea 4 de metodos computacionales

###recibe los datos creados en el ODE.cpp

import numpy as np
import matplotlib.pyplot as plt

##trae los datos
data = np.genfromtxt("salida.txt")


posicion = data[:,0]

velocidad = data[:,1]

##Plotea la posicion y la velocidad
plt.plot(posicion,velocidad)
plt.ylim([0,10])
plt.savefig('salida.png')
