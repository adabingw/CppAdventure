#include <iostream>
#include <time.h>
#include <vector>
#include <cctype>
#include <cstring>
#include <string.h>
#include <algorithm>

using namespace std;

    void printMan(int x, string w);
    void initialize(string* pd);
    void checkInput(string w, int numChars, int x);
    void re();

    vector<char> wrongGuesses;
    vector<string> thread;

    int main()
    {
        srand ( time(NULL) );
        string dictionary[] = { "PREPARATION", "TREPIDATION", "RWANDA", "ZIMBABWE", "FASTIDIOUS", "LANDSCAPE", "ANNIVERSARY", "PARACHUTE", "CATHEDRAL",
                                "ALLIGATOR", "JOGGING", "SUPERNOVA", "NEPTUNE", "HIPPOPOTAMUS", "CICIDA", "PERSNICKETY", "ELECTROCHEMISTRY",
                                "OXYTOCIN", "HANGMAN", "PTERODACTYL", "OUAGADOUGOU", "OXYPHENBUTAZONE", "EGG", "BOROUGH", "ZIGZAG", "VOLDEMORT", "DUMBLEDORE",
                                "PREZELS", "JOHN", "EASTER", "NECESSARY", "DEFINITELY", "PRESIDENT", "VICE", "PENCE", "PRIVY", "AIBOHPHOBIA", "PALINDROME",
                                "TURTLE", "FISH", "LIMITED", "PHOENIX", "MASSACHUSETTS", "PHILADELPHIA", "ALASKA", "VIETNAM", "MELBOURNE", "INTERSTELLAR",
                                "MEAD", "TRY"
        }; // sorry if some of these vocabs cause you pain :)
      
        string *pd;
        pd = dictionary;
        initialize(pd);
    }

    void initialize(string* pd) {
        int i = rand() % 50;
        string word = *(pd + i);
//        cout << word << endl;
        int numChars = (pd + i)->size();
        printMan(0, word);
        cout << " " << endl;
        cout << "Wrong guesses: " << endl;
        cout << " " << endl;
        for (int j = 0; j < numChars; j++) {
            thread.push_back("_ ");
            cout << thread.at(j);
        }
        cout << " " << endl;
        checkInput(word, numChars, 0);
    }

    void checkInput(string w, int numChars, int x) {
        int numBlanks;
        char guess;
        cout << "Enter letter to guess" << endl;
        cin >> guess;
        char upperGuess = toupper(guess);
        int found = w.find(upperGuess);
        system("CLS");
        if (found != string::npos) {
            printMan(x, w);
            cout << "Wrong guesses: ";
            for(int j = 0; j < wrongGuesses.size(); j++) {
                    cout << wrongGuesses.at(j) << " ";
                }
            cout << " " << endl;
            cout << " " << endl;
            for (int i = 0; i < w.size(); i++) {
                if (w.at(i) == upperGuess) {
                    string s(1, upperGuess);
                    thread.at(i) = s + " ";
                }

                if (thread.at(i) == "_ ") {
                    numBlanks ++;
                }
            }
            for (int j = 0; j < thread.size(); j++) {
                cout << thread.at(j);
            }

            if (numBlanks == 0) {
                system("CLS");
                printMan(7, w);
                cout << " " << endl;
                for (int j = 0; j < thread.size(); j++) {
                    cout << thread.at(j);
                }
                cout << " " << endl;
                cout << "YOU WIN, MAN SAVED!" << endl;
                thread.clear();
                cout << " " << endl;
                re();
            } else {
                cout << " " << endl;
                checkInput(w, numChars, x);
            }

        } else {
            wrongGuesses.push_back(upperGuess);
            printMan(x + 1, w);
            if (x+1 != 6) {
                cout << "Wrong guesses: ";
                for(int j = 0; j < wrongGuesses.size(); j++) {
                    cout << wrongGuesses.at(j) << " ";
                }
                cout << " " << endl;
                cout << " " << endl;
                for (int j = 0; j < numChars; j++) {
                    cout << thread.at(j);
                }
                cout << " " << endl;
                checkInput(w, numChars, x+1);
            }
        }
    }

    void printMan(int x, string w) {
        switch(x) {
        case 0:
            cout << "____" << endl;
            cout << "|   |" << endl;
            for (int i = 0; i < 4; i++) {
                cout << "|" << endl;
            }
            cout << "|____" << endl;
            break;
        case 1:
            cout << "____" << endl;
            cout << "|   |" << endl;
            cout << "|   O" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "|" << endl;
            }
            cout << "|____" << endl;
            break;
        case 2:
            cout << "____" << endl;
            cout << "|   |" << endl;
            cout << "|   O" << endl;
            cout << "|   |" << endl;
            cout << "|" << endl;
            cout << "|____" << endl;
            break;
        case 3:
            cout << "____" << endl;
            cout << "|   |" << endl;
            cout << "|   O" << endl;
            cout << "|  -|" << endl;
            cout << "|" << endl;
            cout << "|____" << endl;
            break;
        case 4:
            cout << "____" << endl;
            cout << "|   |" << endl;
            cout << "|   O" << endl;
            cout << "|  -|-" << endl;
            cout << "|" << endl;
            cout << "|____" << endl;
            break;
        case 5:
            cout << "____" << endl;
            cout << "|   |" << endl;
            cout << "|   O" << endl;
            cout << "|  -|-" << endl;
            cout << "|  /" << endl;
            cout << "|____" << endl;
            break;
        case 6:
            cout << "____" << endl;
            cout << "|   |" << endl;
            cout << "|   O" << endl;
            cout << "|  -|-" << endl;
            cout << "|  / \\" << endl;
            cout << "|____" << endl;
            cout << w << endl;
            cout << "MAN IS NOW HUNG, GAME OVER :( " << endl;
            re();
            break;
        case 7:
            cout << "____" << endl;
            cout << "|   |" << endl;
            cout << "|" << endl;
            cout << "|   O < YAY!" << endl;
            cout << "|  `|-" << endl;
            cout << "|__/ \\" << endl;
            break;
        }
    }

    void re() {
        string choice;
        cout << "PLAY AGAIN? (YES/NO)" << endl;
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
        if (choice == "YES") {
            system("CLS");
            main();
        } else {
            exit(0);
        }
    }
