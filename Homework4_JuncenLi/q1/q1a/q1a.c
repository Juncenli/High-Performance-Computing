#include <stdio.h>
#include <mpi.h>

const int COUNT_LIMIT = 32;

int main(int argc, char *argv[])
{
    int processNum, size, namelen;
    char node_name[MPI_MAX_PROCESSOR_NAME];

    int count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processNum);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(node_name, &namelen);
    
    if(count<COUNT_LIMIT){
        if(processNum != 0)
            MPI_Recv(&count, 1, MPI_INT, processNum-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        count++;
        // printf("Proces %d from the Node %s increments count from %d to %d.\n", rank, processor_name, count-1, count);
        printf("The Node %s's Process %d increases the count from %d to %d.\n", node_name, processNum, count-1, count);
        if(processNum!=size-1)
	   MPI_Send(&count, 1, MPI_INT, processNum+1, 0, MPI_COMM_WORLD);
    }
    
   MPI_Finalize();
   return 0;
}