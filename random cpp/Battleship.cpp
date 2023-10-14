#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

    void clearBoard(string board[10][10], int numShips, int ships[3][2]);
    int rando();
    void playAgain();
    bool attack(int ships[3][2], int rows, int cols);

    int main() {
        cout << "Welcome aboard, fellow enemy! My name is Nemesis and I am a threat posed to your country!" << endl;
        cout << "Your job is to destroy my boats based on the matrix map given to you. All you have to do is enter the row number, then the column number!" << endl;
        cout << "You've got 10 tries to prove yourself as not a disappointment! If you sink one of my ships, I'll even tell you!" << endl;
        cout << "In fact, I'll tell you that there are three ships in this matrix. Are you up for the challenge, coward? (y/n)" << endl;

        string board[10][10]; // initializes the board
        for (int r = 0; r < 10; r++) {
            for (int c = 0; c < 10; c++) {
                *(*(board + r) + c) = "-";
            }
        }

        int ships[3][2]; // stores coordinates of the ships
        int numShips = 3; // has 3 ships

        srand ( time(NULL) );

        for (int r = 0; r < 3; r++) { // generates random values for coordinates
            for (int c = 0; c < 2; c++) {
                int random = rand() % 9;
                ships[r][c] = random;
//                cout << ships[r][c] << endl;
            }
        }

        char c;
        cin >> c;

        int tries = 10; // player gets 10 tries

        if (c == 'y') { 
            cout << "Aye aye, cowardly companion. Good luck, you'll need it!" << endl;
            clearBoard(board, numShips, 0);

            while(tries > 0) {
                int guessCoor, guessRow, guessCol;
                cout << "Number of tries: " << tries << endl;
                cout << "Enter the row number, then the column number, to make an idiotic guess: ";
                cin >> guessCoor;
                guessCol = guessCoor % 10; // because the coordinates are entered together, it reads as a whole number
                guessCoor /= 10;           // the number must be split into digits and tens in order to get the row col coordinates
                guessRow = guessCoor % 10;
                cout << "Row: " << guessRow << " Column: " << guessCol << endl;
                tries--;
                bool attackShip = attack(ships, guessRow, guessCol);

                if (attackShip == false) {
                    cout << "AHAHAHA SUCKS, guess again!" << endl;
                } else if (attackShip == true) {
                    board[guessRow][guessCol] = "x";
                    cout << "Oops, you sunk my ship!" << endl;
                    numShips--;
                    if (numShips == 0) {
                        cout << "Shiver me timbers! You have won!" << endl;
                        playAgain();
                    }
                    system("CLS");
                    clearBoard(board, numShips, ships);
                }

            } if (tries == 0) {
                cout << "SIKE! YOU LOST, PEASANT! BETTER LUCK NEXT TIME!" << endl;
                playAgain();
            }

        } else if (c == 'n') {
            cout << "BOO U SUCK." << endl;
            exit(0);
        }
    }

    void clearBoard(string board[10][10], int numShips, int ships[3][2]) {
        cout << "   ";
        for (int i = 0; i < 10; i++) {
            cout << i << " ";
        } cout << endl;
        for (int r = 0; r < 10; r++) {
            cout << r;
            cout << "  ";

            for (int c = 0; c < 10; c++) {
                cout << *(*(board + r) + c) << " ";
                if (c == 9) {
                    cout << endl;
                }
            }
        } cout << "Number of ships not sunk: " << numShips << endl;
    }

    bool attack(int ships[3][2], int rows, int cols) {
        for (int r = 0; r < 3; r++) {
            if (*(*(ships + r) + 0) == rows && *(*(ships + r) + 1) == cols) {
//                cout << *(*(ships + r) + 0) << "   " << *(*(ships + r) + 1) << endl;
//                cout << rows << "   " << cols << endl;
                *(*(ships + r) + 0) = -1;
                *(*(ships + r) + 1) = -1;
                return true;
            }
        }
    }

    void playAgain() {
        cout << "Play again? (y/n)" << endl;
        string enter = "";
        string yn;
        cin >> yn;
        if (yn == "y") {
            system("CLS");
            main();
        } else if (yn == "n") {
            exit(0);
        }
    }
