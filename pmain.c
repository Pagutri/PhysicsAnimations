/*
***************PROYECTO 2***************
*Salma Patricia Gutiérrez Rivera       *
*25 de abril de 2017                   *
****************************************
Función main del Proyecto 2.
Este programa simula la distribución de 
temperaturas en una placa cuadrada ais- 
da usando el método de Gauss-Seidel.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void pedir_args(int n);
float **iniciar_placa(float t_izq, float t_sup, float t_der, float t_inf, int n);
void aplicar_gauss(float **T, int n);
void copiar_a_vieja(float **nueva, float **vieja, int n);
int verificar_condicion(float **Tnue, float **Tvie, int n);
void crear_archivo(int k, float **placa, int n);
void liberar_memoria(float **ptr, int n);

int main(int argc, char *argv[])
{
	pedir_args(argc);
	
	/* Inicializar variables */
	int max_iter = 1000;    // Número máximo de iteraciones
	int iter = 1; // Contador de iteraciones
	int cumple = 0; // Condición de paro
	
	int n = atoi(argv[5]); // Número de puntos de la placa
	int n = sqrt(n); // Medida del lado de la placa, sin bordes
	n += 2; // Medida final de la placa
	
	/* Temperaturas inciales de la placa */
	float **placa = iniciar_placa(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), n);
	float **placaVieja = iniciar_placa(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), n);
	
	crear_archivo(0, placa, n);
	/* Ciclo que implementa el método de Gauss-Seidel */
	while(iter<=max_iter && cumple==0)
	{
	    aplicar_gauss(placa, n);
	    cumple = verificar_condicion(placa, placaVieja, n);
	    copiar_a_vieja(placa, placaVieja, n);
	    crear_archivo(iter, placa, n);
	    iter++;
	}
	
	liberar_memoria(placa, n);
	liberar_memoria(placaVieja, n);
	
 return 0;
} 
