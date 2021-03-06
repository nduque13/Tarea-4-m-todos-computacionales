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

	// Calcula la difusion para el tiempo 1 a partir del tiempo 0 en todos los nodos interiores

	
	for (int i = 1; i < 59; ++i)
	{
		for (int j = 1; j < 29; ++j)
		{
			// Hace difusion en todos los nodos interiores


			CaCO3_1[i][j] = cd*( CaCO3_0[i-1][j] + CaCO3_0[i+1][j] + CaCO3_0[i][j-1] + CaCO3_0[i][j+1]);

			CaCO3_1[i][j] += (CaCO3_0[i][j]*(1.0-4.0*cd));

		}
	}


	
	//Recorre el borde de simetria


	for (int i = 0; i < 59; ++i)
	{
			// Hacer difusion en todos los nodos interiores
			CaCO3_1[i][0] = cd*( CaCO3_0[i-1][0] + CaCO3_0[i+1][0] + CaCO3_0[i][1] + CaCO3_0[i][1]);


			CaCO3_1[i][0] += (CaCO3_0[i][0]*(1.0-4.0*cd));
	}

}


////Comienza simulando la frontera fija //////////////////////////////////////////////////////////////

float Simular_frontera_fija()
{
	

	// Para eso se crea una malla de 60*30


	// Define los limites


	int n1=60;

	int n2=30;

	// a pesar de que el dominio es rectangular, cada nodo mide lo mismo porque 50/60 es igual que 25/30

	float dx = 0.25/30;

	// Define las constantes 
	float k=1.62;

	float calor_especifico=820.0;

	float rho=2710.0;

	float v = k/(calor_especifico*rho);


	float dt = pow(dx,2.0)*0.1/v;

	int iteraciones_tiempo=10000;

	float cd=v*dt/pow(dx,2);



	//Define la calcita como CaCO3 y su tamaño

	float CaCO3_0[60][30];


	float CaCO3_1[60][30];


	//Crea matriz de ceros

	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n2; ++j)
		{
			CaCO3_0[i][j] = 0.0;
			CaCO3_1[i][j] = 0.0;
		}
	}
	//Pide las temperaturas de las varillas y de los bordes


	temperatura_varilla(CaCO3_0);

	temperatura_varilla(CaCO3_1);


	
	for (int i = 0; i < n1; ++i)
	{
			CaCO3_0[i][0] = 10.0;
			CaCO3_1[i][0] = 10.0;

			CaCO3_0[i][60-1] = 10.0;
			CaCO3_1[i][60-1] = 10.0;
	}

	for (int j = 0; j < n2; ++j)
	{
			CaCO3_0[0][j] = 10.0;
			CaCO3_1[0][j] = 10.0;

			CaCO3_0[60-1][j] = 10.0;
			CaCO3_1[60-1][j] = 10.0;
	}


	//Realizo un recorrido para ver la difusion y reubicar la temperatura

	for (int ki = 0; ki < iteraciones_tiempo; ++ki)
	{
		
		difusion(CaCO3_0, CaCO3_1, cd);

		
		temperatura_varilla(CaCO3_1);


		// Para el siguiente tiempo, futuro va a ser pasado ahora


		for (int i = 0; i < n1; ++i)
		{
			for (int j = 0; j < n2; ++j)
			{
				CaCO3_0[i][j] = CaCO3_1[i][j];
			}
		}
	}
	


	ofstream CaCO3_txt("fronteraF_CaCO3.txt");
	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n2; ++j)
		{
		CaCO3_txt << CaCO3_1[i][j] << " ";
		}CaCO3_txt << "\n";
	}

}




////////////////////////////////////////////////////////////////////SIMULA FRONTERA ABIERTA//////////////////////////////

float Simular_frontera_abierta()
{
	
	// Creo una malla igual que en frontera fija 
 


	// limites del dominio


	int n1=60;

	int n2=30;

	// a pesar de que el dominio es rectangular, cada nodo mide lo mismo porque 50/60 es igual que 25/30


	float dx = 0.25/30;

	// Define las constantes


	float k=1.62;

	float calor_especifico=820.0;

	float rho=2710.0;

	float v = k/(calor_especifico*rho);

	float dt = pow(dx,2.0)*0.1/v;

	int iteraciones_tiempo=10000;

	float cd=v*dt/pow(dx,2);



	// Define de nuevo la calcita

	float CaCO3_0[60][30];

	float CaCO3_1[60][30];


	//Crea las matrices con ceros

	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n2; ++j)
		{
			CaCO3_0[i][j] = 0.0;

			CaCO3_1[i][j] = 0.0;
		}
	}


	//Pide las temperaturas de las varillas y de los bordes


	temperatura_varilla(CaCO3_0);


	temperatura_varilla(CaCO3_1);



	// Recorre para encontrar difusion y temperatura



	for (int ki = 0; ki < iteraciones_tiempo; ++ki)
	{
		
		difusion(CaCO3_0, CaCO3_1, cd);

		
		temperatura_varilla(CaCO3_1);

		
		// Condiciones de frontera

		for (int j = 0; j < 29; ++j)
		{
			// Calcula los bordes


			CaCO3_1[0][j] = CaCO3_1[1][j];

			CaCO3_1[59][j] = CaCO3_1[58][j];

		}

		for (int i = 0; i < 60; ++i)
		{
			// Borde derecho

			CaCO3_1[i][29] = CaCO3_1[i][28];

		}


		// Para lo siguiente, e futuro es el pasado ahora 
		for (int i = 0; i < n1; ++i)
		{
			for (int j = 0; j < n2; ++j)
			{
				CaCO3_0[i][j] = CaCO3_1[i][j];
			}
		}
	}
	


	ofstream CaCO3_txt("fronteraA_CaCO3.txt");
	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n2; ++j)
		{
		CaCO3_txt << CaCO3_1[i][j] << " ";
		}CaCO3_txt << "\n";
	}

}




////////////SIMULA FRONTERA PERIODICA////////////////////////////////////////


float Simular_frontera_periodica()
{
	

	// Define los mismos limites


	int n1=60;


	int n2=30;

	// a pesar de que el dominio es rectangular, cada nodo mide lo mismo porque 50/60 es igual que 25/30

	float dx = 0.25/30;

	// Define las constantes
	float k=1.62;

	float calor_especifico=820.0;

	float rho=2710.0;

	float v = k/(calor_especifico*rho);

	float dt = pow(dx,2.0)*0.1/v;

	int iteraciones_tiempo=10000;

	float cd=v*dt/pow(dx,2);


	// Define OTRA VEZ calcita


	float CaCO3_0[60][30];

	float CaCO3_1[60][30];


	// Crea las mismas matrices de ceros

	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n2; ++j)
		{
			CaCO3_0[i][j] = 0.0;

			CaCO3_1[i][j] = 0.0;
		}
	}
	// Pide las t de las varillas y los bordes

	temperatura_varilla(CaCO3_0);


	temperatura_varilla(CaCO3_1);



	// Recorrido para hallar difusion y la tempratura recalculada


	for (int ki = 0; ki < iteraciones_tiempo; ++ki)
	{
		
		difusion(CaCO3_0, CaCO3_1, cd);

		
		temperatura_varilla(CaCO3_1);

		
		// Define las condiciones de frontera periodica


		for (int j = 1; j < 29; ++j)
		{
			// Bordes superior e inferior


			CaCO3_1[0][j] = cd*( CaCO3_0[0][j-1] + CaCO3_0[0][j+1] + CaCO3_0[59][j] + CaCO3_0[1][j]);

			CaCO3_1[0][j] += (CaCO3_0[0][j]*(1.0-4.0*cd));

			CaCO3_1[59][j] = cd*( CaCO3_0[59][j-1] + CaCO3_0[59][j+1] + CaCO3_0[58][j]+ CaCO3_0[0][j] );


			CaCO3_1[59][j] += (CaCO3_0[59][j]*(1.0-4.0*cd));

		}

		for (int i = 1; i < 59; ++i)
		{

			// Borde derecho


			CaCO3_1[i][29] = cd*( CaCO3_0[i-1][29] + CaCO3_0[i+1][29] + CaCO3_0[i][28]+ CaCO3_0[i][28] );


			CaCO3_1[i][29] += (CaCO3_0[i][29]*(1.0-4.0*cd));
		}

		// Por ultimo las esquinas
		CaCO3_1[0][0] = cd*( CaCO3_0[1][0] + CaCO3_0[59][0] + CaCO3_0[0][29] + CaCO3_0[0][1]);

		CaCO3_1[0][0] += (CaCO3_0[0][0]*(1.0-4.0*cd));


		CaCO3_1[0][29] = cd*( CaCO3_0[59][29] + CaCO3_0[1][29] + CaCO3_0[0][28] + CaCO3_0[0][0]);

		CaCO3_1[0][29] += (CaCO3_0[0][29]*(1.0-4.0*cd));		


		CaCO3_1[59][0] = cd*( CaCO3_0[58][0] + CaCO3_0[0][0] + CaCO3_0[59][29] + CaCO3_0[59][1]);

		CaCO3_1[59][0] += (CaCO3_0[59][0]*(1.0-4.0*cd));		


		CaCO3_1[59][29] = cd*( CaCO3_0[58][29] + CaCO3_0[0][29] + CaCO3_0[59][28] + CaCO3_0[59][60]);

		CaCO3_1[59][29] += (CaCO3_0[59][29]*(1.0-4.0*cd));		




		//Cambia el tiempo, el futuro es el pasado ahora papaa

		for (int i = 0; i < n1; ++i)
		{
			for (int j = 0; j < n2; ++j)
			{
				CaCO3_0[i][j] = CaCO3_1[i][j];
			}
		}
	}
	


	ofstream CaCO3_txt("fronteraP_CaCO3.txt");
	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n2; ++j)
		{
		CaCO3_txt << CaCO3_1[i][j] << " ";
		}CaCO3_txt << "\n";
	}

}











//Utiliza el main para obtener frontera fija, frontera abierta y frontera periodica

int main()
{
	Simular_frontera_fija();
	Simular_frontera_abierta();
	Simular_frontera_periodica();
	
}


