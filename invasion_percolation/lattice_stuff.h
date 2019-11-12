#ifndef LATTICE_STUFF_H
#define LATTICE_STUFF_H


int initialize_lattice(int N, int **lattice);

int boundaries_are_dry(int N, int vertex);

int assign_numbers_to_neighbours(int N, int vertex,\
	                        struct binary_tree *bintree,\
                                int *lattice, int rand_max);


#endif
