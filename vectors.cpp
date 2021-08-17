#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

    vector<vector<string>> catalogue { {"Jujutsu Kaisen", "Gege Akutami"},
                                       {"Tokyo Ghoul", "Sui Ishida"},
                                       {"Attack on Titan", "Hajime Isayama"},
                                       {"Demon Slayer", "Koyoharu Gotouge"},
                                       {"Chihayafuru", "Yuki Suetsugu"},
                                       {"Fullmetal Alchemist", "Hiromu Arakawa"},
    };

int main()
{
    string title;
    cout << "Enter keywords to search catalogue: " << endl;
    for(string search; getline(cin, search); ) {
        auto it =  find_if(catalogue.begin(), catalogue.end(), [&search](const vector<string>& entry)
            {
                // Search each "column" of a book entry
                return find_if(entry.begin(), entry.end(),[&search](const string &s) {
                        return s.find(search) != string::npos;
                }) != entry.end();
            } );
        cout << search << ": " << ((it == catalogue.end()) ? "NOT FOUND" : "FOUND") << "\n";
    }
}
