#include <stdio.h>
#include <conio.h>

char gameChar(int i){
    switch(i){
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void changeBoard(int b[9]){
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", gameChar(b[0]), gameChar(b[1]), gameChar(b[2]));

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", gameChar(b[3]), gameChar(b[4]), gameChar(b[5]));

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", gameChar(b[6]), gameChar(b[7]), gameChar(b[8]));

    printf("     |     |     \n");
}

int win(const int board[9]){
	int i;
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
   
    for(i = 0; i < 8; ++i){
        if(board[wins[i][0]] != 0 && board[wins[i][0]] == board[wins[i][1]] && board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;//if player has not won returns 0
}

int minimax(int board[9], int player){//minimax function positions on board
    int move = -1, score = -2;
    int i;
    int winner = win(board);
    if(winner != 0) return winner*player;
  
    for(i = 0; i < 9; ++i){
        if(board[i] == 0){
            board[i] = player;
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0;//Resetting the board
        }
    }
    
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]){
    int move = -1, score = -2;
    int i;
    for(i = 0; i < 9; ++i){
        if(board[i] == 0){
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score){
                score = tempScore;
                move = i;
            }
        }
    }//returns a score based on minimax tree
    board[move] = 1;
}

void humanMove(int board[9]){
    int move = 0;
    do{
        printf("\nChoose your move place (From 0 to 8): ");
        scanf("%d", &move);
        printf("\n");
    }while (move >= 9 || move < 0 || board[move] != 0);//while loop will execute faster
    board[move] = -1;
}

int main(){
    int player = 0;
	int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	
    printf("--Welcome to Tic Tac Toe Game--\n\n");
    printf("COMPUTER: O YOU: X\n");
    printf("Play as (1st or 2nd player): ");
    scanf("%d", &player);
    printf("\n");
    unsigned turn;
    
    for(turn = 0; turn < 9 && win(board) == 0; turn++) {
        if((turn+player) % 2 == 0)
            computerMove(board);
        else{
            changeBoard(board);
            humanMove(board);
        }
    }
    
    switch(win(board)){
        case 0:
            printf("There is no winner!\n");
            break;
        case 1:
            changeBoard(board);
            printf("Computer wins!\n");
            break;
        case -1:
            printf("You win!\n");
            break;
    }
}
