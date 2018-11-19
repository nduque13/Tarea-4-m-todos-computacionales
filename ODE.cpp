//Comienza el primer punto de la tarea 4 de metodos computacionales. ODEs


//Importa las librerias necesarias 
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;
using namespace std;


//Crea las variables que van a ser usadas a lo largo del ejercicio, como gravedad, C y demas

// Gravedad, C, masa, y el tiempo con sus diferenciales.
float g=10.0;

float c=0.2;
float m=0.2;



float t = 0.0;
float tf = 5.0;
float dt = 0.0001;


//Defino un puntero que voy a usar mas tarde como la norma de un vector con dos entradas

float norma(float *v)
{ 
	float norma2;
	norma2 = pow(v[0],2) + pow(v[1],2);
	return sqrt(norma2);
}


int main(){

	//Creo arreglos que almacenen dos velocidades y dos posiciones, como x (posicion) y v (velocidad), lo calcula para los 8 angulos


	float x[2][8];

	float v[2][8];


	////Inicializa cada posicion 

	for (int i = 0; i < 8; ++i)
	{	
		x[0][i] = 0.0; x[1][i]=0.0;	
	}


	//pasa a inicializar cada velocidad

	
	v[0][0] = 300.0*cos(2*3.1416*45.0/360.0);
	v[1][0] = 300.0*sin(2*3.1416*45.0/360.0);

	v[0][1] = 300.0*cos(2*3.1416*10.0/360.0);
	v[1][1] = 300.0*sin(2*3.1416*10.0/360.0);
	v[0][2] = 300.0*cos(2*3.1416*20.0/360.0);
	v[1][2] = 300.0*sin(2*3.1416*20.0/360.0);
	v[0][3] = 300.0*cos(2*3.1416*30.0/360.0);
	v[1][3] = 300.0*sin(2*3.1416*30.0/360.0);
	v[0][4] = 300.0*cos(2*3.1416*40.0/360.0);
	v[1][4] = 300.0*sin(2*3.1416*40.0/360.0);
	v[0][5] = 300.0*cos(2*3.1416*50.0/360.0);
	v[1][5] = 300.0*sin(2*3.1416*50.0/360.0);
	v[0][6] = 300.0*cos(2*3.1416*60.0/360.0);
	v[1][6] = 300.0*sin(2*3.1416*60.0/360.0);
	v[0][7] = 300.0*cos(2*3.1416*70.0/360.0);
	v[1][7] = 300.0*sin(2*3.1416*70.0/360.0);



	//Creo los arreglos para el metodo de solucion de RungeKutta
	//Creo 4 ecuaciones para la posicion y 4 ecuaciones para la velocidad
	//Posiciones


	float xk1[2][8];
	float xk2[2][8];
	float xk3[2][8];
	float xk4[2][8];


	//Velocidades


	float vk1[2][8];
	float vk2[2][8];
	float vk3[2][8];
	float vk4[2][8];


	//Crea los arreglos que almacenen el futuro para las posiciones y para las velocidades

	float fut_x[2][8];
	float fut_v[2][8];

	//Crea varios archivos de salida que almacene posiciones y velocidades del proyectil

	
	ofstream salidax("x.txt");
	ofstream saliday("y.txt");
	ofstream salidavx("vx.txt");
	ofstream salidavy("vy.txt");
	

	//Crea archivos de dstancia recorrida

	float d_recorridax[8];
	d_recorridax[0] = 0.0;
	d_recorridax[1] = 0.0;
	d_recorridax[2] = 0.0;
	d_recorridax[3] = 0.0;
	d_recorridax[4] = 0.0;
	d_recorridax[5] = 0.0;
	d_recorridax[6] = 0.0;
	d_recorridax[7] = 0.0;

	cout << d_recorridax[0] << " ";

	float normav;

	do
	{

	//Antes de comenzar, exporta los datos para despues graficarlos
		for (int i = 0; i < 8; ++i)
			{
				// exportar datos
			salidax << x[0][i] << " ";
			saliday << x[1][i] << " ";
			salidavx << v[0][i] << " ";
			salidavy << v[1][i] << " ";

	//Una vez hecha la ruta para exportar los datos, se empieza con el metodo de rungekutta, 4 ecuaciones, hay que definirlas y calcularlas todas

			// Calcula k1
			xk1[0][i] = v[0][i];
			xk1[1][i] = v[1][i];
			normav = sqrt(pow(v[0][i],2) + pow(v[1][i],2));
			vk1[0][i] = -(c/m)*normav*normav*v[0][i]/normav;
			vk1[1][i] = -g -(c/m)*normav*normav*v[1][i]/normav;
	
			//Calcula k2
			fut_v[0][i] = v[0][i] + 0.5*dt*vk1[0][i];
			fut_v[1][i] = v[1][i] + 0.5*dt*vk1[1][i];
			xk2[0][i] = fut_v[0][i];
			xk2[1][i] = fut_v[1][i];
			normav = sqrt(pow(fut_v[0][i],2) + pow(fut_v[1][i],2));
			vk2[0][i] = -(c/m)*normav*normav*fut_v[0][i]/normav;
			vk2[1][i] = -g -(c/m)*normav*normav*fut_v[1][i]/normav;

			//Calcula k3
			fut_v[0][i] = v[0][i] + 0.5*dt*vk2[0][i];
			fut_v[1][i] = v[1][i] + 0.5*dt*vk2[1][i];
			xk3[0][i] = fut_v[0][i];
			xk3[1][i] = fut_v[1][i];
			normav = sqrt(pow(fut_v[0][i],2) + pow(fut_v[1][i],2));
			vk3[0][i] = -(c/m)*normav*normav*fut_v[0][i]/normav;
			vk3[1][i] = -g -(c/m)*normav*normav*fut_v[1][i]/normav;

			//Calcula k4
			fut_v[0][i] = v[0][i] + 1.0*dt*vk3[0][i];
			fut_v[1][i] = v[1][i] + 1.0*dt*vk3[1][i];
			xk4[0][i] = fut_v[0][i];
			xk4[1][i] = fut_v[1][i];
			normav = sqrt(pow(fut_v[0][i],2) + pow(fut_v[1][i],2));
			vk4[0][i] = -(c/m)*normav*normav*fut_v[0][i]/normav;
			vk4[1][i] = -g -(c/m)*normav*normav*fut_v[1][i]/normav;


			// Calcular los nuevos valores de posicion y velocidad

			fut_x[0][i] = x[0][i] + dt/6.0*( xk1[0][i] + 2*xk2[0][i] + 2*xk3[0][i] + xk4[0][i]);

			fut_x[1][i] = x[1][i] + dt/6.0*( xk1[1][i] + 2*xk2[1][i] + 2*xk3[1][i] + xk4[1][i]);

			fut_v[0][i] = v[0][i] + dt/6.0*( vk1[0][i] + 2*vk2[0][i] + 2*vk3[0][i] + vk4[0][i]);

			fut_v[1][i] = v[1][i] + dt/6.0*( vk1[1][i] + 2*vk2[1][i] + 2*vk3[1][i] + vk4[1][i]);


			// El futuro ahora es el pasado

			x[0][i] = fut_x[0][i];

			x[1][i] = fut_x[1][i];

			v[0][i] = fut_v[0][i];

			v[1][i] = fut_v[1][i];


			//Cuando llega al piso es
			if (fut_x[1][i] < 0.0)
			{ 
			
				if (d_recorridax[i]==0.0)
				{
				d_recorridax[i] = x[0][i];
				cout << x[0][i] << " ";
				}
			}


			
			}

		salidax << " \n";
		saliday << " \n";
		salidavx << " \n";
		salidavy << " \n";

		t = t+dt;
	} while (t<=tf);

	//Define cuanto se lanza el proyectil a 45 grados


	cout << "\n***El proyectil que se lanza a 45 grados recorre " << d_recorridax[0] << " en x *****";

	int mas_lejos=1;
	for (int i = 1; i < 8; ++i)
	{
		if (d_recorridax[i]>d_recorridax[mas_lejos])
		{
			mas_lejos = i;
		}
	}
	//El proyectil que mas recorre //////
	cout << "\n***El proyectil que mayor distancia recorre es el que se lanza a " << mas_lejos*10 << " grados ya que recorre " << d_recorridax[mas_lejos] << " en x *****\n";

}




