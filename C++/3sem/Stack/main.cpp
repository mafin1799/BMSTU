#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <utility>

#include "stack.hpp"
using namespace std;

struct TempStruct {
    string key;
    int value2 = 0;

    TempStruct() = default;

    TempStruct(string v1, int v2)
    {
        this->key = v1;
        this->value2 = v2;
    }

    friend std::ostream& operator<< (std::ostream& out, const TempStruct& tempStruct)
    {
        return out  << tempStruct.key << " " << tempStruct.value2;
    }
};
int main() {

std::stack<TempStruct> stackSTRUCT;

TempStruct structura1;
structura1.key = "Cash";
structura1.value2 = 200;

TempStruct structura2;
structura1.key = "Mash";
structura1.value2 = 451;



stackSTRUCT.push(structura1);
stackSTRUCT.push(structura2);



}

