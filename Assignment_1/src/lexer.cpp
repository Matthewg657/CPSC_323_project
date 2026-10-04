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
            if (isalnum(ch) || ch == '_')
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

    for (const string& keyword : keywords)
    {
        if (lexeme == keyword)
        {
            return true;
        }
    }
    return false;
}
bool isInteger(const string& lexeme)
{
    int state = 0;
    for (char ch : lexeme)
    {
        switch (state)
        {
            case 0:
            if (isdigit(ch))
            {
                state = 1;
            }
            else
            {
                return false;
            }
            break;

             case 1:
        if (isdigit(ch))
        {
            state = 1;
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

bool isReal(const string& lexeme)
{
    int state = 0;

    for (char ch : lexeme)
    {
        switch (state)
        {
            case 0:
            if (isdigit(ch))
            {
                state = 1;
            }
            else if (ch == '.')
            {
                state = 2;
            }
            else
            {
                return false;
            }
            break;

            case 1:
            if (isdigit(ch))
            {
                state = 1;
            }
            else if (ch == '.')
            {
                state = 2;
            }
            else
            {
                return false;
            }
            break;

            case 2:
            if (isdigit(ch))
            {
                state = 3;
            }
            else
            {
                return false;
            }
            break;

            case 3:
        if (isdigit(ch))
        {
            state = 3;
        }
        else
        {
            return false;
        }
        break;
        }

    }
    return state == 3;
}

bool isSeparator(char ch)
{
    return ch == '(' ||
           ch == ')' ||
           ch == '{' ||
           ch == '}' ||
           ch == ',' ||
           ch == ';' ||
           ch == '@';
}

bool isOperator(const string& lexeme)
{
    return lexeme == "=" ||
    lexeme == "+" ||
    lexeme == "-" ||
    lexeme == "*" ||
    lexeme == "/" ||
    lexeme == "==" ||
    lexeme == "!=" ||
    lexeme == ">" ||
    lexeme == "<" ||
    lexeme == "<=" ||
    lexeme == ">=";
    
}

Token lexer(ifstream& inputFile)
{
    Token result;
    char ch;

    //skips whitespace
    while (inputFile.get(ch))
    {
        if (!isspace(ch))
        {
            break;
        }
    }

    if(inputFile.eof())
    {
        result.token = "EOF";
        result.lexeme = "";
        return result;
    }

    if(ch == '!')
    {
        while (inputFile.get(ch) && ch != '!')
        {
            // ignores evrything inside the comments
        }
        return lexer(inputFile);
    }

    if (isalpha(ch))
    {
        string lexeme;
        lexeme += ch;

        while(inputFile.get(ch))
        {
            if (isalnum(ch) || ch == '_')
            {
                lexeme += ch;
            }
            else
            {
                inputFile.unget();
                break;
            }
        }

        if (isKeyword(lexeme))
        {
            result.token = "keyword";
        }
        else
        {
            result.token="identifier";
        }

        result.lexeme = lexeme;
        return result;
    }

    if (isdigit(ch)|| ch == '.')
    {
        string lexeme;
        lexeme += ch;

        bool hasDecimal = (ch == '.');

        while (inputFile.get(ch))
        {
            if (isdigit(ch))
            {
                lexeme += ch;
            }
            else if (ch == '.' && !hasDecimal)
            {
                lexeme += ch;
                hasDecimal = true;
            }
            else
            {
                inputFile.unget();
                break;
            } 
        }
        if (isReal(lexeme))
            {
                result.token = "real";   
            }
            else if(isInteger(lexeme))
            {
                result.token = "integer";
            }
            else 
            {
                result.token = "unknown";
            }
            result.lexeme = lexeme;
            return result;
    }
    if (isSeparator(ch))
    {
        result.token = "separator";
        result.lexeme = string(1, ch);
        return result;
    }
    string op;
    op += ch;

    if (ch == '=' || ch == '<' || ch == '>' || ch == '!')
    {
        char next;
        if (inputFile.get(next))
        {
            string twoCharOp = op + next;

            if (isOperator(twoCharOp))
            {
                result.token = "operator";
                result.lexeme = twoCharOp;
                return result;
            }
            else{
                inputFile.unget();
            }
        }
    }
    if (isOperator(op))
    {
        result.token = "operator";
        result.lexeme = op;
        return result;
    }

    result.token = "unknown";
    result.lexeme = string(1,ch);

    return result;
    }