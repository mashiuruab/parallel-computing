#include <iostream>
#include <mpi.h>
#include <chrono>

using namespace std;

#define DEFAULT_CHANNEL 0
#define MASTER_RANK 0

int number_of_process;
int my_rank;


void  print(int recv_buf[],  int length, int src) {
#ifdef DEBUG_PRINT
    cout<< "Rank : " << my_rank << ", Received : ";

    for(int c=0;c<length;c++){
        cout<< recv_buf[c] <<", ";
    }

    cout << "|||| from rank : " << src << endl;
#endif
}

void linear(int send_buf[],  int length) {
    int recv_buf[length];

    if(my_rank == MASTER_RANK) {
        MPI_Request request[number_of_process-1];
        MPI_Status status[number_of_process-1];

        for(int c=1;c<number_of_process;c++){
            MPI_Isend(send_buf, length, MPI_INT, c, DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[c-1]);
        }

        MPI_Waitall(number_of_process-1, request, status);

    } else {
        MPI_Request request;
        MPI_Status status;
        MPI_Irecv(recv_buf, length, MPI_INT, MASTER_RANK, DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);

        MPI_Waitall(1,&request, &status);

        print(recv_buf, length, status.MPI_SOURCE);
    }
}

void ring(int send_buf[],  int length) {

    if(my_rank == MASTER_RANK) {
        MPI_Request request;
        MPI_Status status;

        int process_to_send = my_rank + 1;
        MPI_Isend(send_buf, length, MPI_INT, process_to_send,
                  DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
        MPI_Waitall(1, &request, &status);

    } else if (my_rank ==  number_of_process - 1) {
        int recv_from = my_rank - 1;
        int recv_buf[length];

        MPI_Request request;
        MPI_Status status;
        MPI_Irecv(recv_buf, length, MPI_INT, recv_from, DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
        MPI_Waitall(1, &request, &status);

        print(recv_buf,length,status.MPI_SOURCE);
    } else {
        int recv_from = my_rank - 1;
        int recv_buf[length];

        MPI_Request request[2];
        MPI_Status status[2];

        MPI_Irecv(recv_buf, length, MPI_INT, recv_from, DEFAULT_CHANNEL,
                  MPI_COMM_WORLD, &request[0]);
        MPI_Waitall(1, &request[0], &status[0]);

        print(recv_buf,length,status[0].MPI_SOURCE);

        int process_to_send = my_rank + 1;
        MPI_Isend(recv_buf, length, MPI_INT, process_to_send, DEFAULT_CHANNEL,
                  MPI_COMM_WORLD, &request[1]);
        MPI_Waitall(1, &request[1], &status[1]);
    }
}

void double_ring(int send_buf[],  int length) {
    int mid1, mid2;

    if(number_of_process <=3) {
        if(number_of_process == 1) {
            cout<< "Nothing to send here , MASTER_RANK : " << my_rank
                << " has buffer " << send_buf << endl;
            return;
        } else if (number_of_process == 2) {
            if(my_rank == MASTER_RANK) {
                MPI_Request request;
                MPI_Status status;
                MPI_Isend(send_buf, length, MPI_INT, my_rank + 1,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
                MPI_Waitall(1,  &request, &status);
            } else {
                int recv_buf[length];
                MPI_Request request;
                MPI_Status status;

                MPI_Irecv(recv_buf, length, MPI_INT, MPI_ANY_SOURCE,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
                MPI_Waitall(1, &request, &status);

                print(recv_buf, length,  status.MPI_SOURCE);
            }
        } else if (number_of_process == 3) {
            if(my_rank == MASTER_RANK) {
                MPI_Request request[2];
                MPI_Status status[2];

                MPI_Isend(send_buf, length, MPI_INT, my_rank + 1,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[0]);
                MPI_Isend(send_buf, length, MPI_INT, number_of_process - 1,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[1]);
                MPI_Waitall(2, request, status);
            } else {
                int recv_buf[length];
                MPI_Request request;
                MPI_Status status;

                MPI_Irecv(recv_buf, length, MPI_INT, MPI_ANY_SOURCE,
                         DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
                MPI_Waitall(1, &request, &status);

                print(recv_buf,  length, status.MPI_SOURCE);
            }
        }

        return;
    }

    /*Even or odd number of process > 3*/
    mid1 = (number_of_process / 2) - 1;
    mid2 = mid1 + 1;

    if(my_rank == MASTER_RANK) {
        MPI_Request request[2];
        MPI_Status status[2];

        MPI_Isend(send_buf, length, MPI_INT, my_rank + 1,
                  DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[0]);
        MPI_Isend(send_buf, length, MPI_INT, number_of_process - 1,
                  DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[1]);
        MPI_Waitall(2, request, status);

    } else if (my_rank == mid1) {
        int recv_from;
        int recv_buf[length];

        MPI_Request request;
        MPI_Status status;

        recv_from  = my_rank-1; //  mid1 receiving from mid1-1

        MPI_Irecv(recv_buf, length, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
        MPI_Waitall(1, &request, &status);

        print(recv_buf, length, recv_from);

    } else if (my_rank ==  mid2){
        int recv_from;
        int recv_buf[length];

        MPI_Request request;
        MPI_Status status;

        recv_from  = my_rank+1; //  mid2 receiving from mid2 + 1

        MPI_Irecv(recv_buf, length, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
        MPI_Waitall(1, &request, &status);

        print(recv_buf, length, recv_from);

    } else if (my_rank < mid1){
        int recv_from;
        int process_to_send;
        int recv_buf[length];

        MPI_Request request[2];
        MPI_Status status[2];

        recv_from  = my_rank-1;
        process_to_send = my_rank + 1;

        MPI_Irecv(recv_buf, length, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[0]);
        MPI_Waitall(1, &request[0], &status[0]);

        print(recv_buf,length,recv_from);

        MPI_Isend(recv_buf, length, MPI_INT, process_to_send,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[1]);
        MPI_Waitall(1, &request[1], &status[1]);

    } else if(my_rank > mid2) {

        int recv_from;
        int process_to_send;
        int recv_buf[length];

        MPI_Request request[2];
        MPI_Status status[2];

        recv_from  = (my_rank+1) % number_of_process;
        process_to_send = my_rank - 1;

        MPI_Irecv(recv_buf, length, MPI_INT, recv_from,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[0]);
        MPI_Waitall(1, &request[0], &status[0]);

        print(recv_buf,length,recv_from);

        MPI_Isend(recv_buf, length, MPI_INT, process_to_send,
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[1]);
        MPI_Waitall(1, &request[1], &status[1]);
    }
}

/*methods and  varaibles related  to tree broadcast algorithm*/

int send_matrix[20][20] = {-1};
int recv_matrix[20] = {-1};

void init_tree_matrix(int low_rank, int upper_rank) { // 0 & number_of_process - 1
    if ((low_rank >= upper_rank  - 1) && recv_matrix[upper_rank] != -1) {
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

void tree(int low_rank, int upper_rank, int send_buf[],  int length) {
    init_dummy_matrix();
    init_tree_matrix(low_rank, upper_rank);

    if(my_rank ==  MASTER_RANK) {
        MPI_Request request[20];
        int send_count  = 0;

        for(int c=0;send_matrix[my_rank][c]!=-1;c++){
            MPI_Isend(send_buf, length, MPI_INT, send_matrix[my_rank][c],
                      DEFAULT_CHANNEL, MPI_COMM_WORLD, &request[send_count]);
            send_count++;
        }

        MPI_Status status[send_count];

        MPI_Waitall(send_count, request, status);

    } else if(recv_matrix[my_rank] != -1) {// everyone  should  receive except master
        int recv_buf[length];

        MPI_Request request;
        MPI_Status status;
        MPI_Irecv(recv_buf, length, MPI_INT, recv_matrix[my_rank],
                 DEFAULT_CHANNEL, MPI_COMM_WORLD, &request);
        MPI_Waitall(1, &request, &status);

        print(recv_buf,length, status.MPI_SOURCE);

        MPI_Request request1[20];
        int send_count  = 0;

        for(int c=0;send_matrix[my_rank][c]!=-1;c++){
            MPI_Isend(recv_buf, length, MPI_INT, send_matrix[my_rank][c],
                     DEFAULT_CHANNEL, MPI_COMM_WORLD, &request1[send_count]);
            send_count++;
        }

        MPI_Status status1[send_count];
        MPI_Waitall(send_count, request1, status1);
    }
}

int main(int argc, char** argv) {

    if(argc != 3) {
        cout<<" arg1 = which algorithm to run,  "
                "arg2 = buffer size (how many ints to pass on broadcast)" << endl;
        exit(EXIT_FAILURE);
    }

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(number_of_process == 1) {
        cout<<"only one process nothing to broadcast"<<endl;
        MPI_Finalize();
        return 0;
    }

    int c = atoi(argv[1]);
    int buff_size = atoi(argv[2]);
    int length =  buff_size / 4;

    /*Initializing buffer with dummy value */

    int send_buff[length];

    for(int c=0;c<length;c++){
        send_buff[c] = (c + 1) * 10;
    }

    auto start = chrono::system_clock::now();
    auto end = chrono::system_clock::now();

    switch (c) {
        case 1:
            if (my_rank == MASTER_RANK) cout<< "Linear BroadCast>>>>> for " << buff_size
                                            << " bytes and number_of_process = " << number_of_process << endl;
            start = chrono::system_clock::now();
            linear(send_buff, length);
            end =  chrono::system_clock::now();
            break;
        case 2:
            if (my_rank == MASTER_RANK) cout<< "Ring BroadCast>>>>> for " << buff_size
                                            << " bytes and number_of_process = " << number_of_process << endl;
            start = chrono::system_clock::now();
            ring(send_buff, length);
            end =  chrono::system_clock::now();
            break;
        case 3:
            if (my_rank == MASTER_RANK) cout<< "Double Ring BroadCast>>>>> for " << buff_size
                                            << " bytes and  number_of_process = " << number_of_process << endl;
            start = chrono::system_clock::now();
            double_ring(send_buff, length);
            end =  chrono::system_clock::now();
            break;
        case 4:
            if (my_rank == MASTER_RANK) cout<< "Tree BroadCast>>>>> for  " << buff_size
                                            << " bytes and  number_of_process = " << number_of_process << endl;
            start = chrono::system_clock::now();
            tree(0, number_of_process - 1, send_buff, length);
            end =  chrono::system_clock::now();
            break;
    }

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    long local_duration = elapsed.count();
    long global_duration;

    /*cout<< "LOCAL:: elapsed time,  "<<"Rank : " << my_rank << ": " << local_duration << " milliseconds " << endl;*/

    if(my_rank ==  MASTER_RANK) {// only master should receive data here
        MPI_Reduce(&local_duration, &global_duration, 1, MPI_LONG,
                   MPI_MAX, MASTER_RANK, MPI_COMM_WORLD);

        long max_duration = local_duration >= global_duration ? local_duration : global_duration;

        cout<<"GLOBAL:: elapsed time " << max_duration << " milliseconds" << endl;
    } else {
        MPI_Reduce(&local_duration, &global_duration, 1, MPI_LONG,
                   MPI_MAX, MASTER_RANK, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}