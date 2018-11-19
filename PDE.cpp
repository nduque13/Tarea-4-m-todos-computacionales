//Comienza el segundo ejercicio de la tarea 4 de metodos computacionales : PDEs

//Importa los paquetes necesarios

#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;
//Encuentra las temperaturas de 100 grados


float temperatura_varilla(float CaCO3[60][30])


{
	float x, y, r;
	for (int i = 0; i < 60; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			x = 50.0*((float)(i-30)/60.0);
			y = 25.0*((float)(j)/30.0);
			r = sqrt(x*x + y*y);
			if (r<10.0/2)
			{
				CaCO3[i][j] = 100.0;
			}


			// Incluir una distribucion de temperatura extrana para evaluar si las condiciones
			// de frontera funcionan correctamente
			//if (i>51 && j>23)
			//{
				//CaCO3[i][j] = 50;
			//}
		}
	}
}


//Lo siguiente que se hace es encontrar la difusion
float difusion(float CaCO3_0[60][30], float CaCO3_1[60][30], float cd)
{	// cd es el coeficiente de la difusion
	// Calcula la difusion para el tiempo 1 a partir del tiempo 0
	// en todos los nodos interiores
	for (int i = 1; i < 59; ++i)
	{
		for (int j = 1; j < 29; ++j)
		{
			// Hacer difusion en todos los nodos interiores
			CaCO3_1[i][j] = cd*( CaCO3_0[i-1][j] + CaCO3_0[i+1][j] + CaCO3_0[i][j-1] + CaCO3_0[i][j+1]);
			CaCO3_1[i][j] += (CaCO3_0[i][j]*(1.0-4.0*cd));
		}
	}


	// recorrer el borde de la simetria
	for (int i = 0; i < 59; ++i)
	{
			// Hacer difusion en todos los nodos interiores
			CaCO3_1[i][0] = cd*( CaCO3_0[i-1][0] + CaCO3_0[i+1][0] + CaCO3_0[i][1] + CaCO3_0[i][1]);
			CaCO3_1[i][0] += (CaCO3_0[i][0]*(1.0-4.0*cd));
	}

}


