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


int send_matrix[20][20] = {-1};
int recv_matrix[20] = {-1};

void init_tree_matrix(int low_rank, int upper_rank) { // 0 & number_of_process - 1
    if ((low_rank >= upper_rank  - 1) && recv_matrix[upper_rank] != -1) {
        cout<< "Returned for " << low_rank << " " << upper_rank << endl;
        cout<< recv_matrix[upper_rank] << endl;
        return;
    }

    int to_send = ((upper_rank + low_rank) / 2) + ((upper_rank + low_rank) % 2);

    int c = 0;
    while (send_matrix[low_rank][c] != -1) {
        c++;
    }

    send_matrix[low_rank][c] = to_send;
    recv_matrix[to_send] = low_rank;

    init_tree_matrix(low_rank, to_send);
    init_tree_matrix(to_send, upper_rank);
}

void init_dummy_matrix() {
    for(int c1=0;c1<number_of_process;c1++){
        for(int c2=0;c2<number_of_process;c2++) {
            send_matrix[c1][c2] = -1;
        }
    }

    for(int c=0;c<number_of_process;c++){
        recv_matrix[c] = -1;
    }
}

void tree(int low_rank, int upper_rank) {
    init_dummy_matrix();
    init_tree_matrix(low_rank, upper_rank);

    cout<< "Send Matrix " << endl;
    for(int c1=0;c1<number_of_process;c1++){
        cout<< c1 << " -> " ;
        for(int c2=0;send_matrix[c1][c2]!=-1;c2++) {
            cout<< send_matrix[c1][c2] << ",";
        }
        cout<< endl;
    }

    cout<< "Recv Matrix" << endl;
    for(int c=0;c<number_of_process;c++){
        cout<< c << " -> " <<recv_matrix[c]<<endl;
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

    //double_ring();

    if(my_rank == MASTER_RANK) {
        tree(0, number_of_process - 1);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}