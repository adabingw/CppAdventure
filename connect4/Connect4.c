#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// template of empty spaces that shall be printed
// char ptemplate[6][8] = {
//                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
//                     };

int header[7] = {1, 2, 3, 4, 5, 6, 7};

typedef char player;
player p1 = 'x';
player p2 = 'o';

int one = 0, two = 0, three = 0, four = 0, five = 0, six = 0, seven = 0;

char** createBoard();
void emptyBoard(char** ptemplate);
void initialize(char** ptemplate);
bool scanTemplate(char** ptemplate, int playerNum, player p);
bool scanBoard(char** ptemplate);
bool scanRow(char** ptemplate, player p);
bool scanColumn(char** ptemplate, player p);
bool scanDiag(char** ptemplate, player p);
void choosePlayer(char** ptemplate, player p);
void playMove(char** ptemplate, player p);
void go(char** ptemplate, int m, int col, player p, int pNum);

int main() {
    char** ptemplate = createBoard();
    initialize(ptemplate); // prints the empty board
    playMove(ptemplate, p1);
}

char** createBoard() {
  char** board = malloc(sizeof(char*) * 6);
  for (int i = 0; i < 6; i++) {
    board[i] = malloc(sizeof(char*) * 7);
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = ' ';
    }
  } return board;
}

void emptyBoard(char** ptemplate) {
  for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            ptemplate[i][j] = ' ';
        }
  }
  one = 0; two = 0; three = 0; four = 0; five = 0; six = 0; seven = 0;
}

void initialize(char** ptemplate) {
    for (int i = 0; i < 7; i++) {
        printf(" %d", header[i]);
    } printf("\n");
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 8; i++) {
            printf("|%c", ptemplate[j][i]);
        } printf("\n");
    }
    printf("```````````````");
    printf("\n");
}

void playAgain(char** ptemplate) {
    char yesNo;
    scanf("%c", &yesNo);
    // fgets(&yesNo, 1, stdin);
    yesNo = getchar();
    if (yesNo == 'y') {
      system("clear");
      emptyBoard(ptemplate);
      initialize(ptemplate);
      playMove(ptemplate, p1);
    } else if (yesNo == 'n') {
      free(ptemplate);
      exit(0);
    } else {
        printf("Sorry, response not valid. Please enter again.\n");
        playAgain(ptemplate);
    }
}

bool scanTemplate(char** ptemplate, int playerNum, player p) {
    bool notFull = scanBoard(ptemplate);
    bool fourInARow = scanRow(ptemplate, p);
    bool fourInACol = scanColumn(ptemplate, p);
    bool fourInADiag = scanDiag(ptemplate, p);
    if (notFull == true && fourInARow == false && fourInACol == false && fourInADiag == false) {
        initialize(ptemplate);
        return true;
    } else if (notFull == false) {
        initialize(ptemplate);
        printf("Board is full, play again? (y/n)\n");
        playAgain(ptemplate);
        return false;
    } else if (fourInARow == true || fourInACol == true || fourInADiag == true) {
        initialize(ptemplate);
        printf("Player %d has won. Play again? (y/n)\n", playerNum);
        playAgain(ptemplate);
        return false;
    }
}

// this scans the board to see if there are any empty spaces to be filled
// if there are no empty spaces (isEmpty == 0) game is terminated
bool scanBoard(char** ptemplate) {
    int numEmpty = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (ptemplate[i][j] == ' ') {
                numEmpty++;
            }
        }
    }
    if (numEmpty > 0) {
        return true;
    } else if (numEmpty == 0) {
        return false;
    }
}

bool scanRow(char** ptemplate, player p){
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 3; x++) {
      if (ptemplate[x][y] == p && ptemplate[x+1][y] == p && ptemplate[x+2][y] == p && ptemplate[x+3][y] == p) {
        return true;
      }
    }
  }
  return false;
}

bool scanColumn(char** ptemplate, player p) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 6; x++) {
      if (ptemplate[x][y] == p && ptemplate[x][y+1] == p && ptemplate[x][y+2] == p && ptemplate[x][y+3] == p) {
        return true;
      }
    }
  }
  return false;
}

bool scanDiag(char** ptemplate, player p) {
  for (int y = 3; y < 7; y++) {
    for (int x = 0; x < 3; x++) {
      if (ptemplate[x][y] == p && ptemplate[x+1][y-1] == p && ptemplate[x+2][y-2] == p && ptemplate[x+3][y-3] == p) {
        return true;
      }
    }
  }

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 3; x++) {
      if (ptemplate[x][y] == p && ptemplate[x+1][y+1] == p && ptemplate[x+2][y+2] == p && ptemplate[x+3][y+3] == p) {
        return true;
      }
    }
  }
  return false;
}

void choosePlayer(char** ptemplate, player p) {
    if (p == p1) {
        p = p2; // toggles
        playMove(ptemplate, p);
    } else if (p == p2) {
        p = p1; // toggles
        playMove(ptemplate, p);
    }
}

void playMove(char** ptemplate, player p) {
    int theInput;
    int playerNum;

    switch(p) {
        case 'x':
            playerNum = 1; // translates so that it's easier to print out
            break;
        case 'o':
            playerNum = 2;
            break;
    }

    printf("Player %d, choose column to play.\n", playerNum);
    if(scanf("%d", &theInput)) {
        switch(theInput) {
          case 1:
            {
              one++;
              go(ptemplate, one, 1, p, playerNum); // move is executed
              break;
            }
          case 2:
            {
              two++;
              go(ptemplate, two, 2, p, playerNum); // move is executed
              break;
            }
          case 3:
            {
              three++;
              go(ptemplate, three, 3, p, playerNum); // move is executed
              break;
            }
          case 4:
            {
              four++;
              go(ptemplate, four, 4, p, playerNum); // move is executed
              break;
            }
          case 5:
            {
              five++;
              go(ptemplate, five, 5, p, playerNum); // move is executed
              break;
            }
          case 6:
            {
              six++;
              go(ptemplate, six, 6, p, playerNum); // move is executed
              break;
            }
          case 7:
            {
              seven++;
              go(ptemplate, seven, 7, p, playerNum); // move is executed
              break;
            }
          default:
              printf("ERROR: invalid column number.\n");
              system("clear");
              initialize(ptemplate);
              playMove(ptemplate, p); // player not penalized for entering an invalid column number
          }
    } else {
      printf("Error: input not a number\n");
      initialize(ptemplate);
      playMove(ptemplate, p);
    }
}

void go(char** ptemplate, int m, int col, player p, int pNum) {
  if (m > 5){ 
    printf("Column full.");
    system("clear");
    bool cont = scanTemplate(ptemplate, pNum, p);
    if (cont == true){
        playMove(ptemplate, p);
    } else if (cont == false) {
        free(ptemplate);
        exit(0);
    }
  } else {
    ptemplate[6 - m][col-1] = p;
    system("clear");
    bool cont = scanTemplate(ptemplate, pNum, p);
    if (cont == true){
        choosePlayer(ptemplate, p); // next player
    } else if (cont == false) {
        free(ptemplate);
        exit(0);
    } // new board will be printed
  }
}


