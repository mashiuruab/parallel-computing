#include <iostream>
#include <mpi.h>
#include <math.h>
#include <chrono>

using namespace std;

#define MASTER_RANK 0
#define TAG_VERSION 0


// board array pointer to pointer of type int
int** board =  NULL;
// mirror board array pointer to pointer of type int
int** mirrorBoard = NULL;
// row number without the ghost cells
int rowNumber = 0;
// column  number without the ghost cells
int colNumber = 0;

int maxGeneration;

int number_of_process = 1;
int my_rank;

int totalRow;


// initializing the board with random value (0 or 1)
void loadBoard() {
    // to ensure random board in each iteration
    srand(time(NULL));

    // 1 or 0 representing live or dead
    int liveOrdead;

    //  initializing the board  without the ghost cells
    for(int x = 1; x <= rowNumber; x++) {
        for(int y = 1; y <= colNumber; y++) {
            liveOrdead = rand() % 2;
            board[x][y] = liveOrdead;
            mirrorBoard[x][y] = board[x][y];
        }
    }

    /*initializing ghost cell top row*/
    /*top row, column = 1..column*/
    for(int y = 1; y <= colNumber; y++) {
        board[0][y] = board[rowNumber][y];
        mirrorBoard[0][y] = board[0][y];
    }

    /*initializing bottom ghost cell*/
    /*row = rowNumber + 1,  column = 1..colnum*/
    for(int y = 1; y <= colNumber; y++) {
        board[rowNumber+1][y] = board[1][y];
        mirrorBoard[rowNumber+1][y]  = board[rowNumber+1][y];
    }

    /*initializing left ghost cell*/
    /*left row  = 1..rowNumber, column  = 0*/
    for(int x = 1; x <= rowNumber; x++) {
        board[x][0] = board[x][colNumber];
        mirrorBoard[x][0] = board[x][0];
    }

    /*initializing top left and bottom  left ghost cell*/
    /* row = 0, col = 0 and row = rowNumber + 1, column = 0*/
    board[0][0] = board[0][colNumber];
    board[rowNumber+1][0] = board[1][0];

    mirrorBoard[0][0] = board[0][0];
    mirrorBoard[rowNumber+1][0] = board[rowNumber+1][0];

    /*initializing  right ghost cell, with out top and bottom one*/
    /*right 1..rowNumber*/
    for(int x = 1; x <= rowNumber; x++) {
        board[x][colNumber+1] = board[x][1];
        mirrorBoard[x][colNumber+1] = board[x][colNumber+1];
    }

    /*initializing top-right ghost cell*/
    board[0][colNumber+1] = board[rowNumber][colNumber+1];
    /*initializing bottom-right ghost cell*/
    board[rowNumber+1][colNumber+1] = board[1][colNumber+1];

    mirrorBoard[0][colNumber+1] = board[0][colNumber+1];
    mirrorBoard[rowNumber+1][colNumber+1] = board[rowNumber+1][colNumber+1];

}


/*Printing the current state of the board*/
void printBoard() {
    cout<< "BOARD :: " << endl;

    for(int x = 0; x <= rowNumber + 1; x++) {
        for(int y = 0; y <= colNumber + 1; y++) {
            cout<<board[x][y] << " ";
        }
        cout<<endl;
    }
}

/*Updating the MirrorBoard for each generation based on the GameOfLife Rule,
 * ghost cells are also updated after the change of main board*/

int doIteration() {

    int update_count = 0;
    int totalLive = 0;

    /*updating  the mirror board from main board after  swapping*/
    for(int col = 0;  col <= colNumber + 1; col++) {
        mirrorBoard[0][col]  =  board[0][col];
        mirrorBoard[rowNumber+1][col]  =  board[rowNumber+1][col];
    }

    /*updating  the mirror  board for  swapping*/
    for(int row = 0; row <= rowNumber + 1;  row++) {
        mirrorBoard[row][0] =  board[row][0];
        mirrorBoard[row][colNumber+1] = board[row][colNumber+1];
    }

    for (int x = 1; x <= rowNumber; x++) {
        totalLive = 0;
        for (int y = 1; y <= colNumber; y++) {
            /*This  is for  swapping and making  sure that mirror  board  is updated*/
            mirrorBoard[x][y]  = board[x][y];

            totalLive += board[x-1][y-1];//top left
            totalLive += board[x-1][y];//top middle
            totalLive += board[x-1][y+1];//top right
            totalLive += board[x][y-1];//middle left
            totalLive += board[x][y+1];//middle right
            totalLive += board[x+1][y-1]; //bottom left
            totalLive += board[x+1][y]; //bottom middle
            totalLive += board[x+1][y+1];//bottom right

            if (mirrorBoard[x][y] == 0) {
                switch (totalLive) {
                    case 3:
                        mirrorBoard[x][y] = 1;
                        update_count++;
                        break;
                    default:
                        mirrorBoard[x][y] = 0;
                }
            } else if(mirrorBoard[x][y] == 1) {
                switch (totalLive) {
                    case 0:
                    case 1:
                        mirrorBoard[x][y] = 0;// die of loneliness
                        update_count++;
                        break;
                    case 2:
                    case 3:
                        mirrorBoard[x][y] = 1;// carry on living
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        mirrorBoard[x][y] = 0;//die for overcrowding
                        update_count++;
                        break;
                    default:
                        mirrorBoard[x][y] = 0;
                        update_count++;
                }
            }
        }
    }

    /*top 1..colnum*/
    for(int y = 1; y <= colNumber; y++) {
        mirrorBoard[0][y] = mirrorBoard[rowNumber][y];
    }

    /*bottom 1..colnum*/
    for(int y = 1; y <= colNumber; y++) {
        mirrorBoard[rowNumber+1][y] = mirrorBoard[1][y];
    }

    /*left 1..rowNumber*/
    for(int x = 1; x <= rowNumber; x++) {
        mirrorBoard[x][0] = mirrorBoard[x][colNumber];
    }

    /*top left and bottom  left*/
    mirrorBoard[0][0] = mirrorBoard[0][colNumber];
    mirrorBoard[rowNumber+1][0] = mirrorBoard[1][0];

    /*right 1..rowNumber*/
    for(int x = 1; x <= rowNumber; x++) {
        mirrorBoard[x][colNumber+1] = mirrorBoard[x][1];
    }

    /*top-right*/
    mirrorBoard[0][colNumber+1] = mirrorBoard[rowNumber][colNumber+1];
    /*bottom-right*/
    mirrorBoard[rowNumber+1][colNumber+1] = mirrorBoard[1][colNumber+1];

    return update_count;
}

/*update the main board from mirror board after each generation*/
void updateBoard() {
    int **temp = board;
    board  =  mirrorBoard;
    mirrorBoard  = temp;
}


void init_memory() {
    /*allocating memory for board and mirror board*/
    board = new int*[rowNumber+2];
    mirrorBoard = new int*[rowNumber+2];

    for(int count=0;count<rowNumber+2;count++){
        board[count] = new int[colNumber+2];
        mirrorBoard[count] = new int[colNumber+2];
    }
}

void delete_memory() {
    /*deleting the allocated memory for 1-D arrays representing
     * the columns for each row in board and  mirrorBoard*/
    for(int count=0;count<rowNumber+2;count++){
        delete board[count];
        delete mirrorBoard[count];
    }

    /*deleting the momory allocated for each row in board and mirrorBoard*/
    delete board;
    delete mirrorBoard;
}

void set_row_number() {
    double my_row = (double)totalRow / (double)number_of_process;
    rowNumber = floor(my_row);

    if(my_rank == number_of_process - 1) {
        rowNumber = totalRow - (rowNumber * (number_of_process - 1));
    }

    cout<< "row assigned : " << rowNumber << endl;
}

int main(int argc, char** argv) {

    if (argc != 4) {
        cout<< "arg1 = rowNumber, arg2 = colNumber, arg3 = maxgeneration expected" << endl;
        exit(EXIT_FAILURE);
    }

    totalRow = atoi(argv[1]);
    colNumber = atoi(argv[2]);
    maxGeneration = atoi(argv[3]);

    if (my_rank == MASTER_RANK) {
        cout<< "arg1 = " << rowNumber << " arg2 = " << colNumber
            << " arg3 = " << maxGeneration << endl;
    }


    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    set_row_number();
    init_memory();

    loadBoard();

    int update_count;
    int i;

    for(i = 0; i < maxGeneration;i++) {
        /*updating the mirror board based on other cells condition or state*/
        update_count = doIteration();

        if(update_count == 0) {
            break;
        }

        /*Updating the main board from  mirror board*/
        updateBoard();
    }

    if (my_rank == MASTER_RANK) {


        double execution_time = 0;
        auto start = chrono::system_clock::now();

        cout<< "src = " << MASTER_RANK << ": converged after : " << i << " iteration " << endl;

        for(int count = 1; count < number_of_process; count++) {
            int recv;
            MPI_Status status;

            MPI_Probe(count, TAG_VERSION, MPI_COMM_WORLD, &status);

            MPI_Recv(&recv, 1, MPI_INT, status.MPI_SOURCE, TAG_VERSION, MPI_COMM_WORLD, &status);

            cout<< "src = " << status.MPI_SOURCE << ": converged after : " << recv << " iteration " << endl;
        }

        auto end = chrono::system_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
        execution_time += elapsed.count();

        cout<< "Time Taken : " << execution_time << " milliseconds" << endl;

    } else {
        MPI_Send(&i, 1, MPI_INT, MASTER_RANK, TAG_VERSION, MPI_COMM_WORLD);
    }


    delete_memory();

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}