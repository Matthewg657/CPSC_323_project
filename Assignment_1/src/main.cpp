#include "lexer.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "identfier test:" << endl;
    cout <<isIdentifier("fahr") << endl;

    cout << "Integer test:" << endl;
    cout <<isIdentifier("fahr") << endl;

    cout << "real test:" << endl;
    cout << isReal("23.00") << endl;

    cout << "keyboard test:" << endl;
    cout << isKeyword("while") << endl;

    return 0;
}