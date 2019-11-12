#include "libraries.h"


int parse_commandline(int argc, char **argv)
{
int N = 0;

if(argc!=2)
  {
  explain_useage_exit(argv[0]);
  }

if(1 != sscanf(argv[1], "%d", &N) )
  {
  explain_useage_exit(argv[0]);
  }

if(N < 1)
  {
  explain_useage_exit(argv[0]);
  }

if(N % 2 != 1)
  {
  explain_useage_exit(argv[0]);
  }

return(N);
}



void explain_useage_exit(char *myname)
{
printf("\n\nUseage:\n\n%s  N\n\nwill simulate the \n"\
       "invasion percolation algorithm for a simple \n"\
       "square lattice with NxN vertices.\n\n"\
       "N must be a positive odd integer.\n\n", myname);
exit(0);
}
