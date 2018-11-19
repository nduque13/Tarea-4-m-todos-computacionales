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

	//Crea un archivo de salida que almacene posiciones y velocidades del proyectil

	std::ofstream salida("salida.txt");


	do
	{

	//Antes de comenzar, exporta los datos para despues graficarlos
	salida << x[0] << " " << x[1] << " " << v[0] << " " << v[1] << endl;

	//Una vez hecha la ruta para exportar los datos, se empieza con el metodo de rungekutta, 4 ecuaciones, hay que definirlas y calcularlas todas

	//Define y calcula k1
	xk1[0] = v[0];


	xk1[1] = v[1];

	vk1[0] = -(c/m)*norma(v)*norma(v)*v[0]/norma(v);


	vk1[1] = -g -(c/m)*norma(v)*norma(v)*v[1]/norma(v);

	//Define y calcula k2, empieza a involucrar el futuro

	fut_v[0] = v[0] + 0.5*dt*vk1[0];


	fut_v[1] = v[1] + 0.5*dt*vk1[1];
	
	xk2[0] = fut_v[0];


	xk2[1] = fut_v[1]; //Con esto ya puedo definir la segunda ecuacion de la velocidad

	vk2[0] = -(c/m)*norma(fut_v)*norma(fut_v)*fut_v[0]/norma(fut_v);



	vk2[1] = -g -(c/m)*norma(fut_v)*norma(fut_v)*fut_v[1]/norma(fut_v);

	//Define y calcula k3, involucra mas el futuro, es casi igual que la segunda ecuacion

	fut_v[0] = v[0] + 0.5*dt*vk2[0];

	fut_v[1] = v[1] + 0.5*dt*vk2[1];

	xk3[0] = fut_v[0];

	xk3[1] = fut_v[1];//Con esto ya puedo definir la tercera ecuacion de la velocidad

	vk3[0] = -(c/m)*norma(fut_v)*norma(fut_v)*fut_v[0]/norma(fut_v);

	vk3[1] = -g -(c/m)*norma(fut_v)*norma(fut_v)*fut_v[1]/norma(fut_v);

	//Define y calcula k4, es igual que la tercera y la segunda

	fut_v[0] = v[0] + 1.0*dt*vk3[0];

	fut_v[1] = v[1] + 1.0*dt*vk3[1];

	xk4[0] = fut_v[0];

	xk4[1] = fut_v[1];//Con esto ya puedo definir la cuarta ecuacion de la velocidad

	vk4[0] = -(c/m)*norma(fut_v)*norma(fut_v)*fut_v[0]/norma(fut_v);

	vk4[1] = -g -(c/m)*norma(fut_v)*norma(fut_v)*fut_v[1]/norma(fut_v);

	//Uiliza las ecuaciones previamente definidas y calculadas para calcular los valores de posicion y velocidad

	fut_x[0] = x[0] + dt/6.0*( xk1[0] + 2*xk2[0] + 2*xk3[0] + xk4[0]);

	fut_x[1] = x[1] + dt/6.0*( xk1[1] + 2*xk2[1] + 2*xk3[1] + xk4[1]);

	fut_v[0] = v[0] + dt/6.0*( vk1[0] + 2*vk2[0] + 2*vk3[0] + vk4[0]);



	fut_v[1] = v[1] + dt/6.0*( vk1[1] + 2*vk2[1] + 2*vk3[1] + vk4[1]);

	//Actualiza el futuro

	x[0] = fut_x[0];

	x[1] = fut_x[1];

	v[0] = fut_v[0];



	v[1] = fut_v[1];

	t = t+dt;

	}








while (t<=tf);

}




