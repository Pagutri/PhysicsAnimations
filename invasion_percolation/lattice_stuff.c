#include "libraries.h"


int initialize_lattice(int N, int **lattice)
{
int i;
int size = N * N;

*lattice = (int *)malloc(size * sizeof(int));

for(i = 0; i < size; i++)
  {
  (*lattice)[i] = 0;
  }

i = (size - 1) / 2;
(*lattice)[i] = 1;

return(i);
}


int boundaries_are_dry(int N, int vertex)
{
int column = 0;
int row = 0;

column = vertex % N;
row = vertex / N;

if(column == 0 || column == (N - 1) ||\
	row == 0 || row == (N - 1))
  {
  return(0);
  }
else
  {
  return(1);
  }
}


int assign_numbers_to_neighbours(int N, int vertex,\
	                        struct binary_tree *bintree,\
                                int *lattice, int rand_max)
{
int column;
int row;
int left_nb, right_nb, up_nb, bottom_nb;

column = vertex % N;
row = vertex / N;
left_nb = row * N + column - 1;
right_nb = left_nb + 2;
up_nb = (row + 1) * N + column;
bottom_nb = (row - 1) * N + column;

if(!lattice[left_nb])
  {
  extend_bintree(bintree, rand_zero_n(rand_max), left_nb);
  }
if(!lattice[right_nb])
  {
  extend_bintree(bintree, rand_zero_n(rand_max), right_nb);
  }
if(!lattice[up_nb])
  {
  extend_bintree(bintree, rand_zero_n(rand_max), up_nb);
  }
if(!lattice[bottom_nb])
  {
  extend_bintree(bintree, rand_zero_n(rand_max), bottom_nb);
  }
return(1);
}
