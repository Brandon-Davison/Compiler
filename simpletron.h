#ifndef SIMPLETRON_H
#define SIMPLETRON_H

#include <iostream>
#include <array>
#include <map>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>

#define MEMSIZE 1000

typedef enum operation
{
    READ = 10, WRITE = 11,
    LOAD = 20, STORE = 21,
    ADD = 30, SUBTRACT = 31, DIVIDE = 32, MULTIPLY = 33, MOD = 34,
    BRANCH = 40, BRANCH_NEG = 41, BRANCH_ZERO = 42, HALT = 43
} Operation;

class Simpletron
{
public:
    explicit Simpletron();

private:
    std::array<int, 1000> mem;

    /* Used to map each operation to its corresponding op-code */
    typedef void (Simpletron::*func)();
    static std::map<int, func> map;

    int accumulator,         // accumulator register
        instructionCounter,  // Memory location (index of mem) of current performing operation
        operationCode,       // Current operation being performed
        operand,             // Memory location in which the current instruction operates
        instructionRegister; // contents of the memory location

    /* Calls a simpletron operation based on an opCode. */
    void invoke(const int &opCode);

    /* Operations */
    void read();
    void write();

    void load();
    void store();

    void add();
    void subtract();
    void divide();
    void multiply();
    void mod();

    void branch();
    void branchNeg();
    void branchZero();
    void halt();

    void runApp();

    /* split word into opCode and operand */
    void splitWord();

    /* load proram into memory */
    void loadProgram();
};


#endif // SIMPLETRON_H
