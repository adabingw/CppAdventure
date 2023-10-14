#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

    void guess(int *f, int *s);
    void analysis(int *f, int *s);

    int main() {
        int first[4];
        int second[4];
        int *f, *s;
        f = first;
        s = second;
        srand ( time(NULL) );
        for (int i = 0; i < 4; i++) {
            int random = rand() % 9;
            first[i] = random;
            cout << first[i] << endl;
        }
        guess(f, s);
    }

    void guess(int *f, int *s) {
        int guess;
        cout << "Enter number: " << endl;
        cin >> guess;
        for (int i = 3; i >= 0; i--) {
            *(s + i) = guess % 10;
            guess /= 10;
            cout << *(s + i) << endl;
        }
        analysis(f, s);
    }

    void playAgain(int *f, int *s) {
        cout << "Play again? (YES/NO)" << endl;
        string yesNo;
        cin >> yesNo;
        if (yesNo == "YES") {
            system("CLS");
            main();
        } else if (yesNo == "NO") {
            exit(0);
        } else {
            cout << "Sorry, response not valid. Please enter again." << endl;
            playAgain(f, s);
        }
    }

    void analysis(int *f, int *s) {
         int rightNum = 0;
         int rightPos = 0;
         int index;
         vector<bool> skip;
         vector<bool> skipNum;
         bool exist = false;

         for (int i = 0; i < 4; i++)
         {
             skip.push_back(false);
             skipNum.push_back(false);
         }

         for (int i = 0; i < 4; i++) {
             if (*(f + i) == *(s + i)) {
                rightPos++;
                skip.at(i) = true;
             }
         }

         for (int i = 0; i < 4; i++) {
             if (skip.at(i) != true) {
                for (int j = 0; j < 4; j++) {
                    if (skip.at(j) != true && i != j) {
                       if (*(f + i) == *(s + j) && skipNum.at(j) != true) {
                          exist = true;
                          index = j;
                       }
                    }
                }

                if (exist)
                {
                   rightNum++;
                   exist = false;
                   skipNum.at(index) = true;
                }
             }
        }

        cout << rightPos << (rightPos == 1 ? " number " : " numbers ") << "in the right position, "
             << rightNum << (rightNum == 1 ? " number " : " numbers ") << "in the wrong position. "
             << endl;

        if (rightPos != 4) {
            cout << "Guess again: " << endl;
            guess(f, s);
        } else {
            cout << "YAY, YOU WIN!" << endl;
            playAgain(f, s);
        }
    }
