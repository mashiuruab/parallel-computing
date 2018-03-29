#include <stdio.h>
#include <mpi.h>

using namespace std;

#define MASTER_RANK 0
#define TAG_VERSION 0

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
                   " out of %d processors\n",
           processor_name, my_rank, world_size);


    if (my_rank ==  MASTER_RANK) {
        int result[world_size][10];

        for(int count = 1; count < world_size;count++) {
            MPI_Status status;

            MPI_Probe(count, TAG_VERSION, MPI_COMM_WORLD, &status);

            printf("DEBUG:: src = %d ",  status.MPI_SOURCE);

            MPI_Recv(result[status.MPI_SOURCE], 10, MPI_INT, status.MPI_SOURCE, TAG_VERSION, MPI_COMM_WORLD, &status);

        }


        for(int count = 1; count < world_size;count++) {
            printf("%d  -> ", count);

            for(int count2 = 0; count2 < 10; count2++) {
                printf("%d  ", result[count][count2]);
            }

            printf("");
        }
    } else {
        int tempArray[10];

        for(int count = 0; count < 10; count++) {
            tempArray[count] = my_rank * 10 + count;
        }

        MPI_Send(tempArray, 10, MPI_INT, MASTER_RANK, TAG_VERSION, MPI_COMM_WORLD);

    }

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}