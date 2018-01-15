#include <iostream>
#include <chrono>

using namespace std;

int** board =  NULL;
int** mirrorBoard = NULL;
int rowNumber = 0;
int colNumber = 0;

void loadBoard() {
    srand(time(NULL));

    int liveOrdead;

    for(int x = 1; x <= rowNumber; x++) {
        for(int y = 1; y <= colNumber; y++) {
            liveOrdead = rand() % 2;
            board[x][y] = liveOrdead;
        }
    }

    /*top 1..colnum*/
    for(int y = 1; y <= colNumber; y++) {
        board[0][y] = board[rowNumber][y];
    }

    /*bottom 1..colnum*/
    for(int y = 1; y <= colNumber; y++) {
        board[rowNumber+1][y] = board[1][y];
    }

    /*left 1..rowNumber*/
    for(int x = 1; x <= rowNumber; x++) {
        board[x][0] = board[x][colNumber];
    }

    /*top left and bottom  left*/
    board[0][0] = board[0][colNumber];
    board[rowNumber+1][0] = board[1][0];

    /*right 1..rowNumber*/
    for(int x = 1; x <= rowNumber; x++) {
        board[x][colNumber+1] = board[x][1];
    }

    /*top-right*/
    board[0][colNumber+1] = board[rowNumber][colNumber+1];
    /*bottom-right*/
    board[rowNumber+1][colNumber+1] = board[1][colNumber+1];

    for(int x = 0; x <= rowNumber + 1; x++) {
        for(int y = 0; y <= colNumber + 1; y++) {
            mirrorBoard[x][y] = board[x][y];
        }
    }

}

void printBoard() {
    cout<< "printing ..........." << endl;

    for(int x = 0; x <= rowNumber + 1; x++) {
        for(int y = 0; y <= colNumber + 1; y++) {
            cout<<board[x][y] << " ";
        }
        cout<<endl;
    }
}

void doIteration(){
    int totalLive = 0;
    for (int x = 1; x <= rowNumber; x++) {
        totalLive = 0;
        for (int y = 1; y <= colNumber; y++) {
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
                        break;
                    default:
                        mirrorBoard[x][y] = 0;
                }
            } else if(mirrorBoard[x][y] == 1) {
                switch (totalLive) {
                    case 0:
                    case 1:
                        mirrorBoard[x][y] = 0;// die of loneliness
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
                        break;
                    default:
                        mirrorBoard[x][y] = 0;
                }
            }
        }
    }
}

void updateBoard() {
    for(int x = 0; x <= rowNumber + 1; x++) {
        for(int y = 0; y <= colNumber + 1; y++) {
            board[x][y] = mirrorBoard[x][y];
        }
    }
}

int main(int argc, char** argv)
{
    rowNumber = 5;
    colNumber = 5;

    board = new int*[rowNumber+2];
    mirrorBoard = new int*[rowNumber+2];

    for(int count=0;count<rowNumber+2;count++){
        board[count] = new int[colNumber+2];
        mirrorBoard[count] = new int[colNumber+2];
    }

    loadBoard();
    //printBoard();

    auto start = chrono::system_clock::now();
    doIteration();
    auto end = chrono::system_clock::now();

    auto elapsed = chrono::duration_cast<chrono::seconds>(end - start);

    cout<< "Time Taken in microseconds " << elapsed.count() << endl;
    updateBoard();
    //printBoard();

    for(int count=0;count<rowNumber+2;count++){
        delete board[count];
        delete mirrorBoard[count];
    }

    delete board;
    delete mirrorBoard;
}