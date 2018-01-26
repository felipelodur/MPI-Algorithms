#include <time.h>
#include <stdio.h>
#include <mpi.h>
#define N 10
#define MAX 4
#define NUMBER 3

int main(int argc , char **argv){

 int size, rank, i, buffer[N], partial, total, number = NUMBER;
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);

 /*if(rank == 0) {
    srand(time(NULL));
    for(i=0; i < N; i++){
    buffer[i] = rand()%MAX;
  } } */

 int send_buffer_tamanho = (N-1)/size + 1;
 int recv_buffer_tamanho = size*send_buffer_tamanho;
 int send_buffer[send_buffer_tamanho];
 int recv_buffer[recv_buffer_tamanho];
 srand(time(NULL));

 for(i=0; i < send_buffer_tamanho; i++)
   send_buffer[i] = rand()%MAX;

 MPI_Allgather(&send_buffer, send_buffer_tamanho, MPI_INT,
 recv_buffer, send_buffer_tamanho, MPI_INT, MPI_COMM_WORLD);

 MPI_Scatter(
   &send_buffer,
    send_buffer_tamanho,
    MPI_INT,
    &recv_buffer,
    recv_buffer_tamanho,
    MPI_INT,
    0,
    MPI_COMM_WORLD);

  partial = 0;
  for(i=0; i < send_buffer_tamanho; i++){
   if(send_buffer[i] == number)
     partial++;
  }

 MPI_Reduce(&partial,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
 if(rank==0){
   printf("Input array\n");
   for(i=0; i < N; i++){
     printf("%d ",buffer[i]);
   }
   printf("\n\nTotal of number \"%d\" found = %d\n",number,total);
 }
 MPI_Finalize();
}


