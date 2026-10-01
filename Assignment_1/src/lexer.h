//include guards prevents everything from being defined in lexer.h more than once
#ifndef LEXER_H
#define LEXER_H
// using fstream because we need it to reed rat26 source files
#include <string>
#include <fstream>

using namespace std;

// Holds the Token tyoe and its actual lexeme
//token is a custom data type
struct Token
{
    string token;
    string lexeme;
};

//Reads the input file and returns the next token
//function declaration that takes in ifstream& inputfile
//will return Token
Token lexer(ifstream& inputFile);

#endif