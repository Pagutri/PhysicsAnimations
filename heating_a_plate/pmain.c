/*
This program simulates the temperature distribution
of an isolated square plate using the Gauss-Seidel
method.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void request_args(int n);
float **initialize_plate(float left_temp, float upper_temp, float right_temp,\
                         float lower_temp, int n);
void apply_gauss_seidel(float **T, int n);
void copy_to_old_plate(float **new, float **old, int n);
int verify_stop_condition(float **Tnue, float **Tvie, int n);
void create_file(int k, float **placa, int n);
void free_memory(float **ptr, int n);

int main(int argc, char *argv[])
{
	int max_iter;
	int iter;
	int meets_condition;
	int n;
	float **plate;
	float **oldPlate;

	request_args(argc);
	max_iter = 1000;
	iter = 1;
	meets_condition = 0;
	n = atoi(argv[5]); /* Number of sites in the plate */
	n = sqrt(n);
	n += 2; /* Side length of the plate, including bounds */
	
	/* Initial temperatures of the plate */
	plate = initialize_plate(atof(argv[1]), atof(argv[2]),
								  atof(argv[3]), atof(argv[4]), n);

	oldPlate = initialize_plate(atof(argv[1]), atof(argv[2]),
										   atof(argv[3]), atof(argv[4]), n);
	
	create_file(0, plate, n);

	while(iter<=max_iter && meets_condition==0)
	{
		apply_gauss_seidel(plate, n);
		meets_condition = verify_stop_condition(plate, oldPlate, n);
		copy_to_old_plate(plate, oldPlate, n);
		create_file(iter, plate, n);
		iter++;
	}
	
	free_memory(plate, n);
	free_memory(oldPlate, n);
	
return 0;
} 
