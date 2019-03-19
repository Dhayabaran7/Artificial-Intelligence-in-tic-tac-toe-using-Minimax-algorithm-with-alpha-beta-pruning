#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

const int dim = 3;

int maxSearch(char board[dim][dim], int level, int alpha, int beta);

//creating x and y coordinates for move position.

struct Move {
    int x;
    int y;
};

//creating character variables for player and opponent.

char player = 'X', opponent = 'O';


//function to print out the board;

void layout(char board[dim][dim]){
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;

    cout << "     |     |     " << endl << endl;
}

//function to check if the board is full or not. i.e, check if any move can be made.

bool isMovesLeft(char board[dim][dim]){
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            if(board[i][j] == '-')
                return true;
        }
    }
    return false;
}


//function to check if anyone has won the game. Score tracking function.

int resultCheck(char board[dim][dim]){

    // check the rows

    for(int i=0; i<dim; i++){
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
            if(board[i][0]==player)
                return +10;
            else if(board[i][0]==opponent)
                return -10;
        }
    }

    //check the columns

    for(int i=0; i<dim; i++){
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i]){
            if(board[0][i]==player)
                return +10;
            else if(board[0][i]==opponent)
                return -10;
        }
    }

    //check the diagonals

    if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
       if(board[0][0]==player)
           return +10;
        else if(board[0][0]==opponent)
            return -10;
    }
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
        if(board[0][2]==player)
            return +10;
        else if(board[0][2]==opponent)
            return -10;
    }

    //score is returned as 0 if there's a tie.

    if(board[0][0]!='-' && board[0][1]!='-' && board[0][2]!='-' && board[1][0]!='-' && board[1][1]!='-' && board[1][2]!='-' && board[2][0]!='-' && board[2][1]!='-' && board[2][2]!='-')
        return 0;

   //exit condition
    return -1;
}

//recursive function to find the optimal move which gives the min score for the minimizing player.

int minSearch(char board[dim][dim], int level, int alpha, int beta){

  //if terminal nodes are reached. i.e, the game has a clear winner.

    if(resultCheck(board) == 10)
        return 10;
    if(resultCheck(board) == -10)
        return -10;
    if(isMovesLeft(board)==false)
        return 0;

    int score = std::numeric_limits<int>::max();

    //finds the best move i.e, min score amongst the available moves.

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            if(board[i][j]=='-'){               // alpha-beta pruning
                board[i][j] = opponent;
                score = min(score, maxSearch(board, level + 1, alpha, beta) + level);
                alpha = min(alpha, score);
                board[i][j] = '-';
                if(beta<=alpha)return alpha;
            }
        }
    }
    return score;
}

//recursive function to find the optimal move which gives the max score for the maximizing player.

int maxSearch(char board[dim][dim], int level, int alpha, int beta){

   //if terminal nodes are reached. i.e, the game has a clear winner.

    if(resultCheck(board) == 10)
        return 10;
    if(resultCheck(board) == -10)
        return -10;
    if(isMovesLeft(board)==false)
        return 0;

    int score = std::numeric_limits<int>::min();

    //finds the best move i.e, max score amongst the available moves.

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            if(board[i][j]=='-'){                       // alpha - beta pruning
                board[i][j] = player;
                score = max(score, minSearch(board, level + 1, alpha, beta) - level);
                alpha = max(alpha, score);
                board[i][j] = '-';
                if(beta<=alpha)return alpha;
            }
        }
    }
    return score;
}

//implementation of the minimax algorithm

Move minimax(char board[dim][dim]){
    int score = std::numeric_limits<int>::max();
    Move move;
    int level = 0;
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            if(board[i][j] == '-'){
                board[i][j] = opponent; //here the the CPU is considered as the maximizing player.
                int temp = maxSearch(board, level, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                if(temp<score){
                    score = temp;
                    move.x = i;
                    move.y = j;
                }
                board[i][j] = '-';
            }
        }
    }
    return move;
}


int main(){

    int gopt;
    char board[3][3];

    for(int i=0; i<dim; i++){                           // fill board with - symbol
        for(int j=0; j<dim; j++){
            board[i][j] = '-';
        }
    }

    cout << "\t \t Let's play Tic Tac Toe! \n" << endl;                             // title menu
    cout << "Player 1 will be X and Player 2/ CPU will be O" << endl<<endl;
    cout<< "Pick a gameplay option: "<< endl;
    cout<< "1. Player 1 vs Player 2"<<endl;
    cout<< "2. Player vs CPU"<<endl<<endl;
    cout<< "Enter a number, 1 or 2: ";
    cin>> gopt;
    cout<<endl;

    while(gopt!=1 && gopt!=2){                                  // check validity of user entry
        cout<<"ERROR! Enter a valid option."<<endl<<endl;
        cout<< "Enter a number, 1 or 2: ";
        cin>> gopt;
        cout<<endl;
    }


    //Player 1 vs Player 2:

    if(gopt == 1){

        cout<<"\t Player 1 vs Player 2. Begin: "<<endl<<endl;

        int player = 1;                // player 1 moves first
        int flag;                    // used to check if the game is over or not
        char symbol;

        do{
            layout(board);

            if (player % 2 == 1)                // for alternating the moves in the game
                player = 1;
            else
                player = 2;

            if (player == 1)
                symbol = 'X';                // To change the symbol when moves are alternated
            else
                symbol = 'O';

            //To enter the respective symbol into the desired position:

            bool fail = true;
            int x = -1, y = -1;

            do{
                cout << "It's player " << player << "'s turn, please make your move(choose wisely). Enter a number as row and column (like 02):  ";
                char c;
                cin >> c;
                x = c - '0';
                cin >> c;
                y = c - '0';

                fail = board[x][y] != '-';

                //error checking code
                if(fail){
                    cout<<endl;
                    cout<<"ERROR! Illegal Move!"<<endl<<endl;
                }

                cin.clear();
               cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (fail);

            cout<<endl;

            //symbol is entered into the desired position.
            board[x][y] = symbol;

            flag = resultCheck(board);
            player++;

        }while(flag == -1);

        layout(board);

        //Comments when the game is over.

        if (flag == 10 || flag == -10)      // If the flag is 10 or -10, there is a winner.
            cout << "Congratulations! Player " << --player << " is the winner! Well done."<< endl<<endl;
        else
            cout << "Game ends in a tie." << endl<<endl;
    }

    //Player vs CPU.

    if(gopt == 2){

        cout<<"\t Player vs CPU. Begin: "<<endl<<endl;

        int player = 1;
        int flag;                    // to check if the game is over or not
        char symbol;

        do{
            layout(board);

            if (player % 2 == 1)                // for alternating the moves in the game
                player = 1;
            else
                player = 2;

            if (player == 1)
                symbol = 'X';                // To change the symbol when moves are alternated
            else
                symbol = 'O';

            if(player == 1){
                bool fail = true;
                int x = -1, y = -1;

                do{
                    cout << "It's the player's turn, please make your move(choose wisely). Enter a number as row and column (like 02):  ";
                    char c;
                    cin >> c;
                    x = c - '0';
                    cin >> c;
                    y = c - '0';

                    fail = board[x][y] != '-';

                    //error checking code
                    if(fail){
                        cout<<endl;
                        cout<<"ERROR! Illegal Move!"<<endl<<endl;
                    }

                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } while (fail);

                cout<<endl;

                //symbol is entered into the desired position.
                board[x][y] = symbol;
            }

            if(player == 2){

                cout<<"CPU's Move: "<<endl<<endl;

                //optimal/best move is computed using the minimax algorithm.
                Move CPUMove = minimax(board);

                //symbol is entered into the desired position.
                board[CPUMove.x][CPUMove.y] = symbol;
            }

            flag = resultCheck(board);
            player++;

        }while(flag == -1);

        layout(board);

        if (flag == 10)                              // If flag is 10, the player is the winner
            cout << "Congratulations! you are the winner! Well done."<< endl<<endl;

        else if(flag == -10) //if flag is -10, the computer is the winner
            cout << "CPU wins. Better luck next time! " << endl<<endl;

        else //else game is a tie
            cout<< " Game ends in a tie."<< endl << endl;
    }

}

