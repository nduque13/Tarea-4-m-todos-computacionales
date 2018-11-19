###Comienza el arbol de dependencias para la tarea 4 de metodos computacionales 


###crea las dependencias######
all: fronteraF_CaCO3_0.png fronteraA_CaCO3_0.png fronteraP_CaCO3_0.png salida_proyectiles.png

fronteraF_CaCO3_0.png fronteraA_CaCO3_0.png fronteraP_CaCO3_0.png salida_proyectiles.png: fronteraF_CaCO3.txt fronteraA_CaCO3.txt fronteraP_CaCO3.txt x.txt y.txt vx.txt vy.txt
	python3 Plots_hw4.py

fronteraF_CaCO3.txt fronteraA_CaCO3.txt fronteraP_CaCO3.txt: PDE.cpp
	g++ PDE.cpp -o ejecutable
	./ejecutable

x.txt y.txt vx.txt vy.txt: ODE.cpp
	g++ ODE.cpp -o ejecutable
	./ejecutable
