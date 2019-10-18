/*
*******FUNCIONES DEL PROYECTO 2*********
*Salma Patricia Gutiérrez Rivera       *
*25 de abril de 2017                   *
****************************************
Funciones utilizadas en el proyecto.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/* La siguiente función muestra en pantalla los argumentos que
necesita el programa si no se especifica un número adecuado de
ellos en la línea de comandos. */
void pedir_args(int n)
{
        if(n != 6) {
                printf("Necesito cinco argumentos.\n");
                printf("El primer argumento es la temperatura del borde izquierdo.\n");
                printf("El segundo argumento es la temperatura del borde superior.\n");
                printf("El tercer argumento es la temperatura del borde derecho.\n");
                printf("El cuarto argumento es la temperatura del borde inferior.\n");
                printf("El último argumento es el número de puntos que tendrá nuestra placa.\n");
	}
}

/* Esta función arma el estado incial de la placa, asignando ceros a todos los
puntos interiores y fijando las temperaturas de los bordes. */
float **iniciar_placa(float t_izq, float t_sup, float t_der, float t_inf, int n)
{   
        int i, j; // Contadores
        float **placa; // Crear puntero

        /* Reservar memoria */
        placa = (float **)malloc(n*sizeof(float*));
        for (i=0;i<n;i++)
                placa[i] = (float*)malloc(n*sizeof(float));

	/* Inicializar Matriz */
        for(i=0;i<n;i++) {
                for(j=0;j<n;j++) {
                        if(i==0) placa[i][j] = t_sup;
                        else if(i==n-1) placa[i][j] = t_inf;
                        else placa[i][j] = 0.0;
                }
                placa[i][0] = t_izq;
                placa[i][n-1] = t_der;
        }
	
        return placa;
}

/* Esta función aplica el método de Gauss-Seidel para calcular
la temperatura de cada punto interior de la placa en función de
sus vecinos. */
void aplicar_gauss(float **T, int n)
{
        int i, j;
        for(i=1;i<n-1;i++) {
                for(j=1;j<n-1;j++) {
                        T[i][j] = (T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1])/4.0;
                }
        }
}

/* Esta función guarda las temperaturas 'viejas' de la placa para poder
verificar la condición de paro */
void copiar_a_vieja(float **nueva, float **vieja, int n)
{
        int i, j;
        for(i=1;i<n-1;i++) {
                for(j=1;j<n-1;j++) vieja[i][j] = nueva[i][j];
        }
}

/* Esta función calcula, para cada celda de la placa, el error porcentual
relativo a la temperatura actual y la anterior. Cuando el error de todas
las celdas es menor que cierta epsilon, la función devuelve un 1. */
int verificar_condicion(float **Tnue, float **Tvie, int n)
{
        int i, j;
        float epsilon = 0.5;
        float max = 0.0;
        float error;
    
        for(i=1;i<n-1;i++) {
                for(j=1;j<n-1;j++) {
                        error = fabs((Tnue[i][j] - Tvie[i][j])/Tnue[i][j])*100;
                        if(error>max) max = error;
                }
        }
    
        if(max<epsilon) return 1; // Verdadero. Se cumple la condición
        else return 0; // Falso. No se cumple.
}

/* Esta función crea los archivos con las placas para graficar */
void crear_archivo(int k, float **placa, int n)
{
        char nombre[17];
        int i,j;
    
        sprintf(nombre, "archivos/%i.txt", k);
        FILE* ptr = fopen(nombre, "a");
    
        for(i=0;i<n;i++) {
                for(j=0;j<n;j++) {
                        fprintf(ptr, "%f ", placa[i][j]);
                }
                fprintf(ptr, "\n");
        }
    
        fclose(ptr);
}

void liberar_memoria(float **ptr, int n)
{
        for(int i=0;i<n;i++) free(ptr[i]);
        free(ptr);
}
