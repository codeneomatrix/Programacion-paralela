//El programa envia un mensaje a cada nodo y lo imprime en pantalla. 
//Ademas, cada nodo procesa el mensaje y retorna los resultados al nodo principal.
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char idstr[32];
  char buff[128];
  int numprocs;
  int myid;
  int i;
  MPI_Status stat; 

  MPI_Init(&argc,&argv); 
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
  MPI_Comm_rank(MPI_COMM_WORLD,&myid); 

  if(myid == 0)
  {
    printf("Tenemos %d procesos\n", numprocs);
    for(i=1;i<numprocs;i++)
    {
      sprintf(buff, "¡Holaaa %d! ", i);
      MPI_Send(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }
    for(i=1;i<numprocs;i++)
    {
      MPI_Recv(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD, &stat);
      printf("%s\n", buff);
    }
  }
  else
  {
    MPI_Recv(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &stat);
    sprintf(idstr, "Proceso %d ", myid);
    strcat(buff, idstr);
    strcat(buff, "reportandose\n");
    MPI_Send(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}