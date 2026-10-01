#include "lexer.h"
#include <iostream>
#include <cctype> // character checking function

using namespace std;

bool isIdentifier(const string& lexeme)
{
    int state = 0;
    
    for (char ch : lexeme)
    {
        switch (state)
        {
            case 0:
            if (isalpha(ch))
            {
                state = 1;
            }
            else{
                return false;
            }
            break;

            case 1:
            if (isalnumch(ch) || ch == '_')
            {
                state =1;
            }
            else
            {
                return false;
            }
            break;
        }
    }
    return state == 1;
}

bool isKeyword(const string& lexeme)
{
    string keywords[] = 
    {
        "integer",
        "boolean",
        "real",
        "if",
        "else",
        "fi",
        "while",
        "return",
        "get",
        "put",
        "function",
        "true",
        "false",
    };

    for (const string& keyworkd : keywords)
    {
        if (lexeme == keyword)
        {
            return true;
        }
    }
    return false;
}