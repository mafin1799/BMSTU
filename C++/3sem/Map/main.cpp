#include <iostream>
#include "Map.h"
#include <map>

using namespace std;

int main() {
    cout << "\n\n - User Map - \n";
    Map<int, string> name;

    name.push(2, "ABBA");
    name.push(6, "Queen");
    name.push(6, ".....");
    name.push(3, "Daft Punk");
    name.push(3, "-----");
    name.push(8, "Aboba");
    name[8] = "_";
    const Map<int, string> n(name);
    n.toJSON();
    cout << n[2];
    cout << (*name.find(6)).val;

    for (auto it = name.begin(); it != name.end(); ++it) {
        cout <<(*it).val;// = "hello";

    }
//    n.at(2) = "d";
//    n[2] = "5";
//    cout << n.toJSON();
//
//    n[8]="3";
//    n.at(3)="";

    cout << "\n\n - Standart Map - \n";
    map<int, string> t;
    t[2] = "ABBA";
    t[6] = "Queen";
    t[3] = "Daft Punk";
    t[8] = "Aboba";
    for (auto it = t.begin(); it != t.end(); ++it){
        cout << it->first << " : " << it->second << endl;
    }
    return 0;
}
