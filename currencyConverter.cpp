#include <iostream>

using namespace std;

    // declaring variables
    string root, child, rootRate, childRate, rootCurr, childCurr, currRate, childName, rootName;
    double rr, cr, rootMoney, childMoney;
    const char *curr[][3] = {{"Australian Dollar", "AUD", "1.35711"},
                 {"Canada Dollar", "CAD", "1.25"},
                 {"Great Britain Pound", "GBP", "0.722453"},
                 {"Euro", "EUR", "0.849113"},
                 {"Japan Yen", "JPY", "109.215"},
                 {"Switzerland Franc", "CHF", "0.91226"},
                 {"USD", "USA Dollar", "1"},
                 {"India Rupee", "INR", "74.1705"},
                 {"Mexico Peso", "MXN", "19.9208"},
                 {"New Zealand Dollar", "NZD", "1.42572"},
                 {"Norway Kroner", "NOK", "8.83354"},
                 {"Venezuelan Bolívares", "VES", "4149310"},
                 {"South Korean Won", "KRW", "1166.56"},
                 {"China Yuan/Renminbi", "KRW", "1166.56"},
                };
    int j = sizeof(curr)/sizeof(curr[0]);

    // declaring functions
    void inputMoney(string* a, string *b);
    bool isNull(string name);
    void start();

    // functions
    string findName(string x) {
        string currName;
        for (int i = 0; i < j; i ++) {
            if (curr[i][1] == x) {
                currName = curr[i][0];
            }
        }
        if (currName == "\0") {
            cout << "Error: currency not found" << endl;
            start();
        } else return currName;
    }

    string findRate(string x) {
        for (int i = 0; i < j; i ++) {
            if (curr[i][1] == x) {
                currRate = curr[i][2];
            }
        }
        return currRate;
    }

    int main() {
        start();
        return 0;
    }

    void start() {
        cout << "Convert from ";
        cin >> root;
        cout << "Convert to ";
        cin >> child;
        rootName = findName(root);
        childName = findName(child);
        rootRate = findRate(root);
        childRate = findRate(child);
        string rootData[2];
        rootData[0] = rootName;
        rootData[1] = rootRate;
        string childData[2];
        childData[0] = childName;
        childData[1] = childRate;
        inputMoney(rootData, childData);
    }

    void inputMoney(string* a, string* b) {
        cout << "Insert amount of currency to be converted ";
        cin >> rootMoney;
        rr = 1/stod(a[1]);
        cr = stod(b[1]);
        childMoney = (rootMoney * rr * cr);
        cout << a[0] << "  ->  " << b[0] << endl;
        cout << "     " << rootMoney << "        ->        " << childMoney << "     " << endl;
        start();
    }
