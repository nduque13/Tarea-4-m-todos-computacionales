//Comienza el primer punto de la tarea 4 de metodos computacionales. ODEs


//Importa las librerias necesarias 
#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"



//Crea las variables que van a ser usadas a lo largo del ejercicio, como gravedad, C y demas

// Gravedad, C, masa, y el tiempo con sus diferenciales.
float g=10.0;

float c=0.2;
float m=0.2;


float t, dt, tf;
t = 0.0;
tf = 5.0;
dt = 0.0001;


//Defino un puntero que voy a usar mas tarde como la norma de un vector con dos entradas

float norma(float *v)
{ 
	float norma2;
	norma2 = pow(v[0],2) + pow(v[1],2);
	return sqrt(norma2);
}


int main(){

	//Creo arreglos que almacenen dos velocidades y dos posiciones, como x (posicion) y v (velocidad)
	float x[2];

	float v[2];

	x[0] = 0.0; x[1]=0.0;

	v[0] = 300.0*cos(2*3.1416*45.0/360.0);

	v[1] = 300.0*sin(2*3.1416*45.0/360.0);

	//Creo los arreglos para el metodo de solucion de RungeKutta
	//Creo 4 ecuaciones para la posicion y 4 ecuaciones para la velocidad
	//Posiciones
	float xk1[2];
	float xk2[2];
	float xk3[2];
	float xk4[2];


	//Velocidad
	float vk1[2];
	float vk2[2];
	float vk3[2];
	float vk4[2];

	










}
