#include "Simpletron.h"

/* Map each function to its corresponding function. */
std::map<int, Simpletron::func> Simpletron::map =
{
    { READ, &Simpletron::read }, { WRITE, &Simpletron::write },
    { LOAD, &Simpletron::load }, { STORE, &Simpletron::store },
    { ADD, &Simpletron::add }, { SUBTRACT, &Simpletron::subtract },
    { DIVIDE, &Simpletron::divide }, { MULTIPLY, &Simpletron::multiply },
    { MOD, &Simpletron::mod }, { BRANCH, &Simpletron::branch },
    { BRANCH_NEG, &Simpletron::branchNeg }, { BRANCH_ZERO, &Simpletron::branchZero },
    { HALT, &Simpletron::halt }
};

Simpletron::Simpletron()
{
    /* Initlize all registers and mem */
    accumulator = instructionCounter = operationCode
        = operand = instructionRegister = 0;
    for (auto &elem : mem)
    {
        elem = 2424;
    }
}

/* Calls a simpletron operation based on an opCode. */
void Simpletron::invoke(const int &operation)
{
    (this->*(map.find(operation)->second))();
}

void Simpletron::runApp()
{
    loadProgram();

    while (operationCode != HALT)
    {
        splitWord();
        instructionCounter += 1;
        invoke(operationCode);
    }
}

/* split word into opCode and operand */
void Simpletron::splitWord()
{
    instructionRegister = mem[instructionCounter];
    operationCode = instructionRegister / 100;
    operand = instructionRegister % 100;
}

/* Operations */
void Simpletron::read()
{
    std::cout << "? ";
    std::cin >> mem[operand];
}

void Simpletron::write()
{
    std::cout << "FROM WRITE: " << mem[operand] << std::endl;
}

void Simpletron::load()
{
    accumulator = mem[operand];
}

void Simpletron::store()
{
    mem[operand] = accumulator;
}

void Simpletron::add()
{
    accumulator += mem[operand];
}

void Simpletron::subtract()
{
    accumulator -= mem[operand];
}

void Simpletron::divide()
{
    accumulator /= mem[operand];
}

void Simpletron::multiply()
{
    accumulator *= mem[operand];
}

void Simpletron::mod()
{
    accumulator %= mem[operand];
}

void Simpletron::branch()
{
    instructionCounter = operand;
}

void Simpletron::branchNeg()
{
    if (accumulator < 0)
    {
        instructionCounter = operand;
    }
}

void Simpletron::branchZero()
{
    if (accumulator == 0)
    {
        instructionCounter = operand;
    }
}

/* Terminate program then perform a memory dump. */
void Simpletron::halt()
{

}

/* load proram into memory */
void Simpletron::loadProgram()
{
    std::ifstream inFile("program.txt", std::ifstream::in);
    std::string str;

    for (int i = 0; std::getline(inFile, str); ++i)
    {
        mem[i] = std::stoi(str);
    }
    inFile.close();
}
