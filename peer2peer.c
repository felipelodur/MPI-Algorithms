#include <mpi.h>
#define TAG 1


void main(int argc, char* argv[]) {

 int p, rank, val,destRank,numProcs; 
 int msg;

 MPI_Status status;
 MPI_Init(&argc, &argv) ;
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
 int ratio = 10000/(numProcs-1);

if (rank == 0){
   int x;
   int y = 1;
   destRank = 1;
   for (x=rank+1; x < numProcs; x++){
        for (y = x*ratio; y >= (x*ratio)-ratio; y--){
                MPI_Send(&y, 1, MPI_INT, x, TAG, MPI_COMM_WORLD);
                //printf("0 sending message %d to %d \n", y, x);
        }
   }
 
   int totalSum = 0;
   for(x=1; x<numProcs; x++){
        MPI_Recv(&msg, 1, MPI_INT, x, TAG, MPI_COMM_WORLD,&status);
        printf("Received sum: %d = %d \n", x, msg);
        totalSum += msg;
   }
   printf("Total Sum = %d", totalSum);
 
 } else {
       int z;
       int sum;
       for ( z = 0; z < ratio; z++){
           MPI_Recv(&msg, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);
           //printf("I received %d \n ", msg);
           sum += msg;
        }

        MPI_Send(&sum, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        //printf("Process %d receives a message from %d with value\n",rank,0,val);
 }
   MPI_Finalize();
}
      
