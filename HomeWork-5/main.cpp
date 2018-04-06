#include <iostream>
#include <mpi.h>

using namespace std;

#define DEFAULT_CHANNEL 0
#define MASTER_RANK 0

int number_of_process;
int my_rank;

void linear() {
    int send_buf = 10;
    int recv_buf;

    if(my_rank == MASTER_RANK) {
        for(int c=1;c<number_of_process;c++){
            MPI_Send(&send_buf, 1, MPI_INT, c, DEFAULT_CHANNEL, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        MPI_Recv(&recv_buf, 1, MPI_INT, MASTER_RANK, DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

        cout<< "Rank : " << my_rank << ", Received : " << recv_buf << endl;
    }
}

void ring() {
    int send_buf = 10;

    if(my_rank == MASTER_RANK) {
        int process_to_send = my_rank + 1;
        MPI_Send(&send_buf, 1, MPI_INT, process_to_send, DEFAULT_CHANNEL, MPI_COMM_WORLD);
    } else if (my_rank ==  number_of_process - 1) {
        int recv_from = my_rank - 1;
        int recv_buf;
        MPI_Status status;
        MPI_Recv(&recv_buf, 1, MPI_INT, recv_from, DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

        cout<< "Rank : "<<my_rank << ", received : " << recv_buf << endl;
    } else {
        int recv_from = my_rank - 1;
        int recv_buf;
        MPI_Status status;
        MPI_Recv(&recv_buf, 1, MPI_INT, recv_from, DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

        cout<< "Rank : "<<my_rank << ", received : " << recv_buf << endl;

        int process_to_send = my_rank + 1;
        MPI_Send(&recv_buf, 1, MPI_INT, process_to_send, DEFAULT_CHANNEL, MPI_COMM_WORLD);
    }
}

void double_ring() {
    int mid1, mid2;

    int send_buf = 10;

    if(number_of_process <=3) {
        if(number_of_process == 1) {
            cout<< "Nothing to send here , MASTER_RANK : " << my_rank
                << " has buffer " << send_buf << endl;
            return;
        } else if (number_of_process == 2) {
            if(my_rank == MASTER_RANK) {
                MPI_Send(&send_buf, 1, MPI_INT, my_rank + 1,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD);
            } else {
                int recv_buf;
                MPI_Status status;

                MPI_Recv(&recv_buf, 1, MPI_INT, MPI_ANY_SOURCE,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

                cout<< "Rank : "<<my_rank << ", received : "
                    << recv_buf << ", from rank : " << status.MPI_SOURCE << endl;
            }
        } else if (number_of_process == 3) {
            if(my_rank == MASTER_RANK) {
                MPI_Send(&send_buf, 1, MPI_INT, my_rank + 1,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD);
                MPI_Send(&send_buf, 1, MPI_INT, number_of_process - 1,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD);
            } else {
                int recv_buf;
                MPI_Status status;

                MPI_Recv(&recv_buf, 1, MPI_INT, MPI_ANY_SOURCE,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

                cout<< "Rank : "<<my_rank << ", received : "
                    << recv_buf << ", from rank : " << status.MPI_SOURCE << endl;
            }
        }

        return;
    }

    /*Even or odd number of process > 3*/
    mid1 = (number_of_process / 2) - 1;
    mid2 = mid1 + 1;

    if(my_rank == MASTER_RANK) {
        MPI_Send(&send_buf, 1, MPI_INT, my_rank + 1, DEFAULT_CHANNEL, MPI_COMM_WORLD);
        MPI_Send(&send_buf, 1, MPI_INT, number_of_process - 1, DEFAULT_CHANNEL, MPI_COMM_WORLD);
    } else if (my_rank == mid1) {
        int recv_from;
        int recv_buf;
        MPI_Status status;

        recv_from  = my_rank-1; //  mid1 receiving from mid1-1

        MPI_Recv(&recv_buf, 1, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

        cout<< "Rank : "<<my_rank << ", received : " << recv_buf
                << ", from rank : " << recv_from << endl;
    } else if (my_rank ==  mid2){
        int recv_from;
        int recv_buf;
        MPI_Status status;

        recv_from  = my_rank+1; //  mid2 receiving from mid2 + 1

        MPI_Recv(&recv_buf, 1, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

        cout<< "Rank : "<<my_rank << ", received : " << recv_buf
                << ", from rank : " << recv_from << endl;
    } else if (my_rank < mid1){
        int recv_from;
        int process_to_send;
        int recv_buf;
        MPI_Status status;

        recv_from  = my_rank-1;
        process_to_send = my_rank + 1;

        MPI_Recv(&recv_buf, 1, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

        cout<< "Rank : "<<my_rank << ", received : " << recv_buf
                << ", from rank : " << recv_from << endl;

        MPI_Send(&recv_buf, 1, MPI_INT, process_to_send,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD);

    } else if(my_rank > mid2) {

        int recv_from;
        int process_to_send;
        int recv_buf;
        MPI_Status status;

        recv_from  = (my_rank+1) % number_of_process;
        process_to_send = my_rank - 1;

        MPI_Recv(&recv_buf, 1, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &status);

        cout<< "Rank : "<<my_rank << ", received : " << recv_buf
                << ", from rank : " << recv_from << endl;

        MPI_Send(&recv_buf, 1, MPI_INT, process_to_send,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD);
    }
}

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(number_of_process == 1) {
        MPI_Finalize();
        return 0;
    }

    //linear();

    //ring();

    double_ring();

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}