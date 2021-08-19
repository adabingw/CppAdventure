#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

    struct Book {
        string title;
        string author;
        string publisher;
        string status;
        int year;
    };

    vector<string> loans;

    void searchCatalogue(Book* pc);
    void borrowBooks(Book *pc);
    void choiceDirector(Book *pc);
    void reviewLoans(Book *pc);
    void returnBooks(Book *pc);
    bool returnVal(string s);

    int main() {
        Book catalogue[] = { {"Percy Jackson and the Lightning Thief", "Rick Riordan", "Puffin Books", "available", 2005},
                 {"Jane Eyre", "Charlotte Brontë", "Smith, Elder & Co.", "available", 1847},
                 {"Pride and Prejudice", "Jane Austen", "T. Egerton, Whitehall", "available", 1813},
                 {"Pride and Prejudice and Zombies", "Seth Grahame-Smith", "Quirk Books", "available", 2009},
                 {"Harry Potter and the Philosopher's Stone", "J.K Rowling", "Bloomsbury (UK)", "available", 1997},
                 {"Harry Potter and the Chamber of Secrets", "J.K Rowling", "Bloomsbury (UK)", "available", 1998},
                 {"Harry Potter and the Prisoner of Azkaban", "J.K Rowling", "Bloomsbury (UK)", "available", 1999},
                 {"Harry Potter and the Goblet of Fire", "J.K Rowling", "Bloomsbury (UK)", "available", 2000},
                 {"Harry Potter and the Order of the Phoenix", "J.K Rowling", "Bloomsbury (UK)", "available", 2003},
                 {"Harry Potter and the Half-Blood Prince", "J.K Rowling", "Bloomsbury (UK)", "available", 2005},
                 {"Harry Potter and the Deathly Hallows", "J.K Rowling", "Bloomsbury (UK)", "available", 2007}
                };
        Book* pc;
        pc = catalogue;
        choiceDirector(pc);
    }

    void searchCatalogue(Book* pc) {
        int counts = 0;
        string key;
        cout << "Enter keyword to search: " << endl;
        cin.ignore();
        getline(cin, key);
        cout << "----------------------------" << endl;
        for (int i = 0; i < 11; i++) {
            string name = (pc + i)->title;
            string author = (pc + i)->author;
            int found = name.find(key);
            int found2 = author.find(key);
            if (found != string::npos || found2 != string::npos) {
                cout << (pc + i)->title << " -- " << (pc + i)->status << endl;
                counts ++;
            }
        }
        cout << "----------------------------" << endl;
        cout << counts << (counts == 1 ? " result " : " results ") << "found." << endl;
        choiceDirector(pc);
    }

    void borrowBooks(Book *pc) {
        string searchTitle;
        int borrowed = 0;
        cout << "Enter full title of book to borrow:" << endl;
        cin.ignore();
        getline(cin, searchTitle);
        for (int i = 0; i < 11; i++) {
            if (searchTitle == (pc + i)->title && (pc + i)->status == "available") {
                string yesNo;
                cout << "Borrow " << (pc + i)->title << " by " << (pc + i)->author << " ?" << endl;
                cin >> yesNo;
                if (yesNo == "Yes") {
                    loans.push_back((pc + i)->title);
                    cout << (pc + i)->title << " successfully added to your loans." << endl;
                    borrowed = 1;
                    (pc + i)->status = "unavailable";
                    cout << "----------------------------" << endl;
                } else if (yesNo == "No") {
                    choiceDirector(pc);
                }
            } else if (searchTitle == (pc + i)->title && (pc + i)->status != "available") {
                borrowed = 1;
                cout << "Book is currently unavailable." << endl;
            }
        }
        if (borrowed == 0) {
            cout << "Book not found. Please check your spelling." << endl;
        }
        choiceDirector(pc);
    }

    void reviewLoans(Book *pc) {
        cout << "LOANS" << endl;
        cout << "----------------------------" << endl;
        for(int j=0; j < loans.size(); j++) {
            cout << loans.at(j) << endl;
        }
        cout << "----------------------------" << endl;
        choiceDirector(pc);
    }

    void returnBooks(Book *pc) {
        cout << "LOANS" << endl;
        cout << "----------------------------" << endl;
        for(int j=0; j < loans.size(); j++) {
            cout << loans.at(j) << endl;
        }
        cout << "----------------------------" << endl;
        string searchTitle;
        int borrowed = 0;
        cout << "Enter full title of book to return:" << endl;
        cin.ignore();
        getline(cin, searchTitle);
        for (int i = 0; i < loans.size(); i++) {
            if (searchTitle == loans.at(i)) {
                string title;
                string yesNo;
                cout << "Return " << loans.at(i) << "?" << endl;
                cin >> yesNo;
                if (yesNo == "Yes") {
                    title = loans.at(i);
                    auto it = find_if(loans.begin(), loans.end(), returnVal);
                    loans.erase(it);
                    cout << title << " successfully returned to library." << endl;
                    (pc + i)->status = "available";
                    borrowed = 1;
                    cout << "----------------------------" << endl;
                    reviewLoans(pc);
                } else if (yesNo == "No") {
                    reviewLoans(pc);
                    choiceDirector(pc);
                }
            }
        }
        if (borrowed == 0) {
            cout << "Book not found. Please check your spelling." << endl;
        } choiceDirector(pc);
    }

    bool returnVal(string s) {
        return true;
    }

    void choiceDirector(Book *pc) {
        char in;
        cout << "Press x to exit, s to search catalogue, b to borrow books, r to return books, l to review your loans." << endl;
        cin >> in;
        switch(in) {
        case 'x':
            exit(0);
            break;
        case 's':
            searchCatalogue(pc);
            break;
        case 'b':
            borrowBooks(pc);
            break;
        case 'r':
            returnBooks(pc);
            break;
        case 'l':
            reviewLoans(pc);
            break;
        default:
            cout << "ERROR" << endl;
            exit(0);
        }
    }
