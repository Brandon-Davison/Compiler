#ifndef COMPILER_H
#define COMPILER_H

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <functional>
#include <algorithm>
#include <map>
#include <exception>

#define MEMSIZE 1000

typedef enum command {
    REM, END, DATA, INPUT, PRINT, GOTO, IF, LET
} Command;

/* value corresponds to its representing ASCII value. */
typedef enum type {
    CONSTANT    = 67, // 'C'
    LINE_NUMBER = 76, // 'L'
    VARIABLE    = 86  // 'V'
} Type;

static const std::map<char, int> operators = {
    {'+', 30}, {'-', 31}, {'/', 32}, {'*', 33 }, {'%', 34}
};

typedef struct tableEntry
{
    int symbol;   // ASCII representation of variable, line number, or constant
    char type;    // 'C' constant, 'L' Simple line number, 'V' variable
    int location; // Simpletron address (000 to MEMSIZE-1)
} SymbolTable[MEMSIZE];

class Compiler
{
public:
    explicit Compiler() ;
    ~Compiler();

    void compile();

private:
    std::ifstream srcFile;
    std::ofstream outputFile;

    SymbolTable symbolTable = {};
    bool flags[MEMSIZE] = { false };

    /* Used to map each command to its corresponding instruction */
    typedef void (Compiler::*func)(const int&, std::queue<std::string>&);
    static std::map<std::string, func> map;

    int memory[MEMSIZE];
    int data[MEMSIZE];
    int ndata = 0;

    int nextInstrctionAddr   = 0;
    int nextConstOrVarAddr = MEMSIZE - 1; // Used for variables (next const or variable adress)
    int nextSymbolTableIdx   = 0; // used for index of symbol table insertions
    int nextData             = 0; // used for data

    void invoke(const std::string &cmd, const int &lineNumber,
        std::queue<std::string> &tokens);

    void firstPass();
    void secondPass();

    void insertRemSymbol(const int &smlLineNumber, std::queue<std::string> &tokens);
    void insertEndSymbol(const int &smlLineNumber, std::queue<std::string> &tokens);
    void insertDataSymbol(const int &smlLineNumber, std::queue<std::string> &tokens);
    void insertInputSymbol(const int &smlLineNumber, std::queue<std::string> &tokens);

    void insertSymbol(const int &symbol, const char &type, const int &location);

    static std::string convertToPostfix(const std::string &infix);

    /* Splits a simple command into individual tokens then places them into a queue. */
    std::queue<std::string> split(const std::string &str);

};

#endif // COMPILER_H
