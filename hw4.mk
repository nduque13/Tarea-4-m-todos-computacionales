###Comienza el arbol de dependencias para la tarea 4 de metodos computacionales 


###crea las dependencias######
all: fronteraF_CaCO3.png fronteraA_CaCO3.png fronteraP_CaCO3.png

fronteraF_CaCO3.png fronteraA_CaCO3.png fronteraP_CaCO3.png: fronteraF_CaCO3.txt fronteraA_CaCO3.txt fronteraP_CaCO3.txt
	python Plots_hw4.py

fronteraF_CaCO3.txt fronteraA_CaCO3.txt fronteraP_CaCO3.txt: PDE.cpp
	g++ PDE.cpp -o ejecutable
	./ejecutable

datos.txt:
	g++ ODE.cpp -o ejecutable
	./ejecutable
	python Plots_hw4.py
