###COmienza el plots de la tarea 4 de metodos computacionales

###recibe los datos creados en el ODE.cpp######################

import numpy as np

import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D

##trae los datos
#data = np.genfromtxt("salida.txt")


#posicion = data[:,0]

#velocidad = data[:,1]

##Plotea la posicion y la velocidad
#plt.plot(posicion,velocidad)
#plt.ylim([0,10])
#plt.savefig('salida.png')




######recibe los datos creados en PDE.cpp############################

def analizar_temperaturas(archivo, nombre):
	#Define el tamano de los datos 


	d1 = 60
	d2 = 30

	# CREA DOS ARREGLOS, LINSPACES


	x = np.linspace(0,25,d2)

	y = np.linspace(0,50,d1)

	x,y = np.meshgrid(x,y)

	x = x.flatten()

	y = y.flatten()

	##TRAE LOS DATOS	

	I = np.genfromtxt(archivo) 
	

	print(np.shape(I))
	##Agarro el tamano de los datos

	n,m = np.shape(I) 
	# Extraigo los datos y le da shape



	ii=np.reshape(I[0,:], (d1,d2)) 

	fig = plt.figure()

	ax = fig.add_subplot(1,2,1, projection='3d')

	ax.plot_trisurf(x, y, I[0,:])

	ax = fig.add_subplot(1,2,2)

	ax.imshow(ii, vmin=0, vmax=100)

	fig.savefig( nombre+'_0', dtype='png')


	# Extraigo los datos y da shape

	ii=np.reshape(I[int(0.2*n),:], (d1,d2)) 

	fig = plt.figure()

	ax = fig.add_subplot(1,2,1, projection='3d')

	ax.plot_trisurf(x, y, I[int(0.2*n),:])

	ax = fig.add_subplot(1,2,2)

	ax.imshow(ii, vmin=0, vmax=100)

	fig.savefig( nombre+'_1', dtype='png')

	 #Extraigo los datos y da shape

	ii=np.reshape(I[int(0.6*n),:], (d1,d2))

	fig = plt.figure()

	ax = fig.add_subplot(1,2,1, projection='3d')

	ax.plot_trisurf(x, y, I[int(0.6*n),:])

	ax = fig.add_subplot(1,2,2)

	ax.imshow(ii, vmin=0, vmax=100)

	fig.savefig( nombre+'_2', dtype='png')

	 #Extraigo los datos y da shape

	ii=np.reshape(I[-1,:], (d1,d2))

	fig = plt.figure()

	ax = fig.add_subplot(1,2,1, projection='3d')

	ax.plot_trisurf(x, y, I[-1,:])

	ax = fig.add_subplot(1,2,2)

	ax.imshow(ii, vmin=0, vmax=100)

	fig.savefig( nombre+'_3', dtype='png')

	return np.mean(I, axis=1)

###Lee los datos generados en el PDE.cpp
p1 = analizar_temperaturas("fronteraF_CaCO3.txt", "fronteraF_CaCO3")

p2 = analizar_temperaturas("fronteraA_CaCO3.txt", "fronteraA_CaCO3")

p3 = analizar_temperaturas("fronteraP_CaCO3.txt", "fronteraP_CaCO3")


labels = ["fronteraF", "fronteraA", "fronteraP"]		
fig = plt.figure()

ax = fig.add_subplot(1,1,1)

ax.plot(p1)

ax.plot(p2)

ax.plot(p3)

ax.legend(labels, loc='best')

fig.savefig( "promediosT", dtype='png')
