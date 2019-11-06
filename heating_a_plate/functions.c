#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void request_args(int n)
{
    if(n != 6)
    {
        printf("Give me five arguments.\n");
        printf("The first one will be the temperature of the left bound.\n");
        printf("The second one will be the temperature of the upper bound.\n");
        printf("The third one will be the temperature of the right bound.\n");
        printf("The fourth one will be the temperature of the lower bound.\n");
        printf("The last argument will be the number of sites in the plate.\n");
	}
}

float **initialize_plate(float left_temp, float upper_temp, float right_temp,\
             float lower_temp, int n)
{   
    int i, j;
    float **plate;

    plate = (float **)malloc(n * sizeof(float*));
    for (i = 0; i < n; i++)
        plate[i] = (float*)malloc(n * sizeof(float));

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == 0) plate[i][j] = upper_temp;
            else if(i == n - 1) plate[i][j] = lower_temp;
            else plate[i][j] = 0.0;
        }
        plate[i][0] = left_temp;
        plate[i][n-1] = right_temp;
    }
	
    return plate;
}

/* This function applies the Gauss-Seidel method in calculating
the temperature of every interior point of the plate averaging
the temperature of its neighbours. */
void apply_gauss_seidel(float **T, int n)
{
    int i, j;
    for(i = 1; i < n - 1; i++)
    {
        for(j = 1; j < n - 1; j++)
        {
            T[i][j] = (T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1]) / 4.0;
        }
    }
}

void copy_to_old_plate(float **new, float **old, int n)
{
    int i, j;
    for(i = 1; i < n - 1; i++)
    {
        for(j = 1; j < n - 1; j++) old[i][j] = new[i][j];
    }
}

/* The simulation stops when the difference between the temperatures
of the previous and the current plates is small. */
int verify_stop_condition(float **Tnew, float **Told, int n)
{
    int i, j;
    float epsilon = 0.5;
    float max = 0.0;
    float error;
    
    for(i = 1; i < n - 1; i++)
    {
        for(j = 1; j < n - 1; j++)
        {
            error = fabs((Tnew[i][j] - Told[i][j]) / Tnew[i][j]) * 100;
            if(error > max) max = error;
        }
    }
    
    if(max < epsilon) return 1;
    else return 0;
}

/* Files required to create the final gif */
void create_file(int k, float **placa, int n)
{
    char name[17];
    int i, j;
    FILE* ptr;
    
    sprintf(name, "files/%i.txt", k);
    ptr = fopen(name, "w");
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            fprintf(ptr, "%f ", placa[i][j]);
        }
        fprintf(ptr, "\n");
    }
    
    fclose(ptr);
}

void free_memory(float **ptr, int n)
{
    int i;

    for(i = 0; i < n; i++) free(ptr[i]);
    free(ptr);
}
