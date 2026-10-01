#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <fstream>

using namespace std;

// Holds the Token tyoe and its actual lexeme
struct Token
{
    string token;
    string lexeme;
};

//Reads the input file and returns the next token
Token lexer(ifstream& inputFile);

#endif