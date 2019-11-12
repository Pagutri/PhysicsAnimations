/*
Implementation of the invasion
percolation algorithm for a simple
square lattice with NxN vertices.

Patricia Gutierrez, February 2018
gutierrezrs2015@licifug.ugto.mx
*/

#include "libraries.h"

int main(int argc, char **argv)
{
int N = 0;
int rand_max = 100;
int current_vertex = 0;
int next_vertex = 0;
int min_num = 0;
int *lattice;
struct binary_tree *min_num_node;
struct binary_tree *bintree;
FILE *wet_coordinates;

initialize_rand();

N = parse_commandline(argc, argv);
wet_coordinates = fopen("files/fractal.dat", "w");
current_vertex = initialize_lattice(N, &lattice);
fprintf(wet_coordinates, "%i %i\n", current_vertex % N, current_vertex / N);

allocate_and_initialize_bintree(&bintree);

while(boundaries_are_dry(N, current_vertex))
  {
  assign_numbers_to_neighbours(N, current_vertex, bintree, lattice, rand_max);
  min_num_node = bintree_minrandom_number_node(bintree);
  next_vertex = min_num_node->index;

  min_num = min_num_node->random_number;
  remove_node_from_bintree(bintree, min_num, next_vertex);
  
  if(lattice[next_vertex] == 0)
    {
    lattice[next_vertex] = 1;
    fprintf(wet_coordinates, "%i %i\n", next_vertex % N, next_vertex / N);
    current_vertex = next_vertex;
    }
  }

empty_bintree(bintree);
fclose(wet_coordinates);

return(1);
}



