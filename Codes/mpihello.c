#include <stdio.h>
#include "mpi.h"
main(argc,argv)
int argc;
char **argv;
{
int mpi_size, mpi_rank;
 //FILE *fp;
// char fn[20];
 MPI_Init(0,0);      
  MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);
  printf("Hello world for %d\n",mpi_rank);
 // sprintf(fn,"HELLO_%d",mpi_rank);
 // fp = fopen(fn, "w");
 // fprintf(fp,"%d",mpi_rank);
 // fclose(fp);
  MPI_Finalize();
  return ;
}

