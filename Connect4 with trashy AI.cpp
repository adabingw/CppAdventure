/*
 * ai basically chooses a random column to play in
 * not a great ai
 * but yeah
*/

#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <time.h>
#include <time.h>

using namespace std;

    // template of empty spaces that shall be printed
    string ptemplate[6][8] = {
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "}
                        };

    string emptyTemplate[6][8] = {
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "},
                         {" ", " ", " ", " ", " ", " ", " ", " "}
                        };

    // this tells the players the column numbers to enter
    string header[7] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7"};

    // corresponding vector to each column
    vector<int> one, two, three, four, five, six, seven;

    // 2 players of type player char
    typedef char player;
    player p1 = 'x';
    player ai = 'o';

    void initialize(); // prints the board each time a move is made
    bool scanTemplate(string playerNum); // scans for overall wins and board condition (is full/empty?)
    bool scanBoard(); // scans if board is full
    bool scanRow(); // scans if there is a win in a row
    bool scanColumn(); // scans if there is a win in a column
    bool scanDiag(); // scans if there is a win in a diagonal
    void choosePlayer(player p); // toggles between player 1 and player 2
    void playMove(player p); // player chooses move
    void choiceMaker(player p, int c, string playerNum);
    void go(int m, int col, player p, string pNum); // move executed

    int main() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                ptemplate[i][j] = emptyTemplate[i][j]; // refreshes the array as an empty array
            }
        }
        initialize(); // prints the empty board
        playMove(p1);
    }

    void initialize() {
        for (int i = 0; i < 7; i++) {
            cout << header[i];
        } cout << " " << endl;
        for (int j = 0; j < 6; j++) {
            for (int i = 0; i < 8; i++) {
                cout << "|" << ptemplate[j][i]; // prints the slots sort of thing
            }   cout << " " << endl;
        }
        cout << "```````````````" << endl; // prints the bottom of the board
    }

    void playAgain() {
        string yesNo;
        cin >> yesNo;
        if (yesNo == "YES") {
            system("CLS");
            main();
        } else if (yesNo == "NO") {
            exit(0);
        } else {
            cout << "Sorry, response not valid. Please enter again." << endl;
            playAgain();
        }
    }

    bool scanTemplate(string playerNum) {
        bool notFull = scanBoard();
        bool fourInARow = scanRow();
        bool fourInACol = scanColumn();
        bool fourInADiag = scanDiag();
        if (notFull == true && fourInARow == false && fourInACol == false && fourInADiag == false) { // no wins / not full
            initialize();
            return true;
        } else if (notFull == false) {
            initialize();
            cout << "Board is full, play again? (YES/NO)" << endl;
            playAgain();
            return false;
        } else if (fourInARow == true || fourInACol == true || fourInADiag == true) {
            initialize();
            cout << "Player has won. Play again?" << endl;
            playAgain();
            return false;
        }
    }

    // this scans the board to see if there are any empty spaces to be filled
    // if there are no empty spaces (isEmpty == 0) game is terminated
    bool scanBoard() {
        int numEmpty = 0;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (ptemplate[i][j] == " ") {
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

    bool scanRow() {
        for (int i = 5; i >= 0; i--) { // starts from bottom row, moves up
            int rowCountX = 0;
            int rowCountO = 0;
            for (int j = 0; j < 6; j++) { // starts from column 1, moves right
                if (ptemplate[i][j] == "x") {
                    rowCountX++;
                } else {
                    rowCountX = 0;
                }
                if (ptemplate[i][j] == "o") {
                    rowCountO++;
                } else {
                    rowCountO = 0;
                }
            if (rowCountX == 4 || rowCountO == 4) {
                return true;
            }
            }
        }
    }

    bool scanColumn() {
        for (int j = 0; j < 7; j++) { // starts from column 1, moves right
            int colCountX = 0;
            int colCountO = 0;
            for (int i = 5; i >= 0; i--) { // starts from bottom row, moves up
                if (ptemplate[i][j] == "x") {
                    colCountX++;
                } else {
                    colCountX = 0;
                }
                if (ptemplate[i][j] == "o") {
                    colCountO++;
                } else {
                    colCountO = 0;
                }
            if (colCountX == 4 || colCountO == 4) {
                return true;
            }
            }
        }
    }

    bool scanDiag() {
        for (int row = 6; row > 0; row--) {
            for (int col = 0; col < 6; col++) {

                if (ptemplate[row][col] == "x") {
                    if (!(((row - 1) < 0) || ((col + 1) > 6))) {
                        if (ptemplate[row-1][col+1] == "x") {
                            if (!(((row - 2) < 0) || ((col + 2) > 6))) {
                                if (ptemplate[row-2][col+2] == "x") {
                                    if (!(((row - 3) < 0) || ((col + 3) > 6))) {
                                        if (ptemplate[row-3][col+3] == "x") {
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (ptemplate[row][col] == "x") {
                    if (!(((row - 1) < 0) || ((col - 1) < 0))) {
                        if (ptemplate[row-1][col-1] == "x") {
                            if (!(((row - 2) < 0) || ((col - 2)) < 0)) {
                                if (ptemplate[row-2][col-2] == "x") {
                                    if (!(((row - 3) < 0) || ((col - 3) < 0))) {
                                        if (ptemplate[row-3][col-3] == "x") {
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (ptemplate[row][col] == "o") {
                    if (!(((row - 1) < 0) || ((col + 1) > 6))) {
                        if (ptemplate[row-1][col+1] == "o") {
                            if (!(((row - 2) < 0) || ((col + 2) > 6))) {
                                if (ptemplate[row-2][col+2] == "o") {
                                    if (!(((row - 3) < 0) || ((col + 3) > 6))) {
                                        if (ptemplate[row-3][col+3] == "o") {
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (ptemplate[row][col] == "o") {
                    if (!(((row - 1) < 0) || ((col - 1) < 0))) {
                        if (ptemplate[row-1][col-1] == "o") {
                            if (!(((row - 2) < 0) || ((col - 2)) < 0)) {
                                if (ptemplate[row-2][col-2] == "o") {
                                    if (!(((row - 3) < 0) || ((col - 3) < 0))) {
                                        if (ptemplate[row-3][col-3] == "o") {
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void choosePlayer(player p) {
        if (p == p1) {
            p = ai; // toggles
            playMove(p);
        } else if (p == ai) {
            p = p1; // toggles
            playMove(p);
        }
    }

    void playMove(player p) {
        int choice;
        string theInput;
        string playerNum;
        string enter = "";

        if (p == p1) {
            cout << "Player, choose column to play." << endl;

            getline(cin, theInput);

            while(cin.fail() || cin.eof() || theInput.find_first_not_of("0123456789") != string::npos || theInput == enter) { // checks if input is a number
                cout << "Error: input not a number" << endl;
                chrono::seconds dura(1);
                this_thread::sleep_for( dura );
                if( theInput.find_first_not_of("0123456789") == string::npos) {
                    cin.clear();
                    cin.ignore(256,'\n');
                }
                system("CLS");
                initialize();
                playMove(p); // allows the player to play their move again/doesn't skip because of an invalid input
            }

            string::size_type st;
            choice = stoi(theInput,&st); // has to be converted to a string
            choiceMaker(p, choice, playerNum);
        }

        else if (p == ai) {
            srand ( time(NULL) );
            choice = rand() % 7;
            choiceMaker(p, choice, playerNum);
        }
    }

    void choiceMaker(player p, int c, string playerNum) {
        switch(c) {
        case 1:
            {
                one.push_back(0); // adds 0 to vector one (which corresponds to column one)
                int maxNum = *max_element(one.begin(), one.end()); // gets max number in vector
                one.push_back(maxNum + 1); // adds max number + 1 to one
                go(maxNum, 1, p, playerNum); // move is executed
                break;
            }
            // this is done to stack the inputs up
        case 2:
            {
                two.push_back(0);
                int maxNum = *max_element(two.begin(), two.end());
                two.push_back(maxNum + 1);
                go(maxNum, 2, p, playerNum);
                break;
            }
        case 3:
            {
                three.push_back(0);
                int maxNum = *max_element(three.begin(), three.end());
                three.push_back(maxNum + 1);
                go(maxNum, 3, p, playerNum);
                break;
            }
        case 4:
            {
                four.push_back(0);
                int maxNum = *max_element(four.begin(), four.end());
                four.push_back(maxNum + 1);
                go(maxNum, 4, p, playerNum);
                break;
            }
        case 5:
            {
                five.push_back(0);
                int maxNum = *max_element(five.begin(), five.end());
                five.push_back(maxNum + 1);
                go(maxNum, 5, p, playerNum);
                break;
            }
        case 6:
            {
                six.push_back(0);
                int maxNum = *max_element(six.begin(), six.end());
                six.push_back(maxNum + 1);
                go(maxNum, 6, p, playerNum);
                break;
            }
        case 7:
            {
                seven.push_back(0);
                int maxNum = *max_element(seven.begin(), seven.end());
                seven.push_back(maxNum + 1);
                go(maxNum, 7, p, playerNum);
                break;
            }
        default:
            cout << "ERROR: invalid column number." << endl;
            chrono::seconds dura(1);
            this_thread::sleep_for( dura );
            system("CLS");
            initialize();
            playMove(p); // player not penalized for entering an invalid column number
        }
    }

    void go(int m, int col, player p, string pNum) {
        if (m > 5){ // if max number exceeds 5, that means column is full, and so no inputs are allowed in that column anymore
            cout << "Column full." << endl;
            chrono::seconds dura(1);
            this_thread::sleep_for( dura );
            system("CLS");
            bool cont = scanTemplate(pNum); // checks if board is full/there's a win
            if (cont == true){
                playMove(p);
            } else if (cont == false) {
                exit(0);
            }
        } else {
            ptemplate[5 - m][col-1] = p; // whatever the player is (x or o) is stored in the array where the row is 5 - max (since we work from bottom -> up)
                                            // and column - 1 (because of array indices)
            system("CLS");
            bool cont = scanTemplate(pNum); // checks for full board / wins
            if (cont == true){
                choosePlayer(p); // next player
            } else if (cont == false) {
                exit(0);
            } // new board will be printed
        }
    }


