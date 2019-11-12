CC = gcc
CFLAGS   = -O3 -Wall -Wstrict-prototypes -ansi -pedantic
COMMONSRC = libraries.h
EXECUTABLE = invasion_percolation


$(EXECUTABLE): invasion_percolation.o simple_random.o parsing.o\
               binary_tree.o lattice_stuff.o $(COMMONSRC)
	$(CC) -o $(EXECUTABLE) invasion_percolation.o simple_random.o\
                               parsing.o binary_tree.o lattice_stuff.o $(CFLAGS)


invasion_percolation.o: invasion_percolation.c $(COMMONSRC)
	$(CC) -c -o invasion_percolation.o invasion_percolation.c $(CFLAGS)

simple_random.o: simple_random.c simple_random.h $(COMMONSRC)
	$(CC) -c -o simple_random.o simple_random.c $(CFLAGS)

parsing.o: parsing.c parsing.h $(COMMONSRC)
	$(CC) -c -o parsing.o parsing.c $(CFLAGS)

binary_tree.o: binary_tree.c binary_tree.h $(COMMONSRC)
	$(CC) -c -o binary_tree.o binary_tree.c $(CFLAGS)

lattice_stuff.o: lattice_stuff.c lattice_stuff.h $(COMMONSRC)
	$(CC) -c -o lattice_stuff.o lattice_stuff.c $(CFLAGS)


clean:
	rm -f *.o $(EXECUTABLE)
