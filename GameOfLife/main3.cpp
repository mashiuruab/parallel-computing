/*
Name: Md Mashiur Rahman Chowdhury
BlazerId: mashiur
Course Section: CS 432 or CS 632 or CS 732
Homework #: 1 - Sequential Program
*/
/*
 * How to run
 * g++ --std=c++11 main.cpp
 * ./a.out {rowNumber} {columnNumber} {Generation}
 * for Example ./a.out 10 10 10
 * */
#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>

using namespace std;

// board array pointer to pointer of type int
int** board =  NULL;
// mirror board array pointer to pointer of type int
int** mirrorBoard = NULL;
// row number without the ghost cells
int rowNumber = 0;
// column  number without the ghost cells
int colNumber = 0;

int thread_count = 1;

int update_count = 0;


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

void  doIteration() {

    double my_rank  = (double) omp_get_thread_num();
    double thread_count =  (double) omp_get_num_threads();

    double row_chunk_with_ghost = (rowNumber + 2) / thread_count;
    double col_chunk_with_ghost = (colNumber + 2) / thread_count;

    double row_chunk = rowNumber / thread_count;
    double col_chunk = colNumber / thread_count;

    if(my_rank == thread_count - 1) {
        row_chunk_with_ghost = (rowNumber + 2) - (row_chunk_with_ghost * (thread_count - 1));
        col_chunk_with_ghost = (colNumber + 2) - (col_chunk_with_ghost * (thread_count - 1));

        row_chunk = rowNumber - (row_chunk * (thread_count - 1));
        col_chunk = colNumber - (col_chunk * (thread_count - 1));
    }

    int row_start_with_ghost = (int) (my_rank * row_chunk_with_ghost);
    int col_start_with_ghost = (int) (my_rank * col_chunk_with_ghost);

    int row_end_with_ghost = (int) (row_start_with_ghost + row_chunk_with_ghost);
    int col_end_with_ghost = (int) (col_start_with_ghost + col_chunk_with_ghost);

    int row_start = (int) (my_rank * row_chunk);
    int col_start = (int) (my_rank * col_chunk);

    int row_end = (int) (row_start + row_chunk);
    int col_end = (int) (col_start + col_chunk);

    int totalLive = 0;

    /*updating  the mirror board from main board after  swapping*/
    for(int col = col_start_with_ghost;  col < col_end_with_ghost; col++) {
        mirrorBoard[0][col]  =  board[0][col];
        mirrorBoard[rowNumber+1][col]  =  board[rowNumber+1][col];
    }

    /*updating  the mirror  board for  swapping*/
    for(int row = row_start_with_ghost; row < row_end_with_ghost;  row++) {
        mirrorBoard[row][0] =  board[row][0];
        mirrorBoard[row][colNumber+1] = board[row][colNumber+1];
    }



    for (int x = row_start + 1; x < row_end + 1; x++) {
        totalLive = 0;
        for (int y = col_start + 1; y < col_end + 1; y++) {
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

    if (my_rank == 0) { // just ensuring that only one thread executes this,
        // other thread would just waste cpu computation cycle
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
    }

}

/*update the main board from mirror board after each generation*/
void updateBoard() {
    int **temp = board;
    board  =  mirrorBoard;
    mirrorBoard  = temp;
}

int main(int argc, char** argv)
{

    if (argc != 5) {
        cout<< "arg1 = rowNumber, arg2 = colNumber, "
                "arg3 = maxgeneration expected, arg4 = num_threads" << endl;
        exit(EXIT_FAILURE);
    }

    rowNumber = atoi(argv[1]);
    colNumber = atoi(argv[2]);
    int maxGeneration = atoi(argv[3]);
    thread_count = atoi(argv[4]);

    cout<< "arg1 = " << rowNumber << " arg2 = " << colNumber
        << " arg3 = " << maxGeneration << " thread_count = " << thread_count << endl;

    /*allocating memory for board and mirror board*/
    board = new int*[rowNumber+2];
    mirrorBoard = new int*[rowNumber+2];

    for(int count=0;count<rowNumber+2;count++){
        board[count] = new int[colNumber+2];
        mirrorBoard[count] = new int[colNumber+2];
    }


    double avgTime = 0;
    int iteration = 1;

    /* executing  3 times to calculate average time*/
    for(int count = 0; count < iteration; count++) {
        loadBoard();
        auto start = chrono::system_clock::now();

        for(int i = 0; i < maxGeneration;i++) {
            /*updating the mirror board based on other cells condition or state*/
            update_count = 0;
            #pragma omp parallel num_threads(thread_count) reduction(+: update_count)
            doIteration();

            if(update_count == 0) {
                cout<< "converged after generation " << i << endl;
                break;
            }

            /*Updating the main board from  mirror board*/
            updateBoard();
        }

        auto end = chrono::system_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
        avgTime += elapsed.count();
    }

    avgTime /= iteration;

    cout<< "Avg Time Taken : " << avgTime << " milliseconds" << endl;

#ifdef DEBUG_PRINT
    printBoard();
#endif

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