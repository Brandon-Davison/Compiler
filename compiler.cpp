#include "Compiler.h"

std::map<std::string, Compiler::func> Compiler::map =
{
    {"rem", &Compiler::insertRemSymbol}, {"end", &Compiler::insertEndSymbol}
};

Compiler::Compiler()
{
    srcFile.open("source.txt");
    outputFile.open("sml.txt");

    nextInstrctionAddr = nextSymbolTableIdx = nextData = 0;
    nextConstOrVarAddr = MEMSIZE - 1;
}

Compiler::~Compiler()
{
    srcFile.close();
    outputFile.close();
}

void Compiler::compile()
{
    firstPass();
}

void Compiler::invoke(const std::string &cmd, const int &lineNumber,
    std::queue<std::string> &tokens)
{
    (this->*(map.find(cmd)->second))(lineNumber, tokens);
}

void Compiler::firstPass()
{
    std::string line, letBuffer, cmd;
    int lineNum;

    while (std::getline(srcFile, line))
    {
        /* split line into tokens. */
        std::queue<std::string> tokens = split(line);

        /* get line number */
        lineNum = std::stoi(tokens.front());
        tokens.pop();

        /* Get command */
        cmd = tokens.front();
        tokens.pop();

        /* Execute command */
        invoke(cmd, lineNum, tokens);
        return;
    }
}

/* Fill in 'holes' left from first pass by iterating through the flag array. */
void Compiler::secondPass()
{

}

/* Add line number to symbol table, and ignore the rest. */
void Compiler::insertRemSymbol(const int &smlLineNumber, std::queue<std::string> &tokens)
{
    /* nextSymbolTableIdx isn't incremented because 'rem' is ignored by the compiler. */
    insertSymbol(smlLineNumber, LINE_NUMBER, nextInstrctionAddr++);
}

/* terminate program. */
void Compiler::insertEndSymbol(const int &smlLineNumber, std::queue<std::string> &tokens)
{
    /* Add to symbol table, then increment nextSymbolTableIdx and nextInstructionAddr. */
    insertSymbol(smlLineNumber, LINE_NUMBER, nextInstrctionAddr++);
}

/*
 * Add the integer(last token) to the data array and increment ndata.
 * If there isn't enough room in the data array to add the element, throw an exception
 */
void Compiler::insertDataSymbol(const int &smlLineNumber, std::queue<std::string> &tokens)
{
    /// TODO: put cast in try block and throw an exception if invlalid cast (data isn't valid integer.)
    data[ndata++] = std::stoi(tokens.front());
}

void Compiler::insertInputSymbol(const int & smlLineNumber, std::queue<std::string>& tokens)
{
}


void Compiler::insertSymbol(const int &symbol, const char &type, const int &location)
{
    /* Add to symbolTable, then increment nextSymbolTableIdx for the next symbol. */
    symbolTable[nextSymbolTableIdx].symbol = symbol;
    symbolTable[nextSymbolTableIdx].type = type;
    symbolTable[nextSymbolTableIdx++].location = location;
}

std::string Compiler::convertToPostfix(const std::string &infix)
{
    std::stack<char> stack;
    stack.push('N');
    std::string postFix;
    const std::map<char, int> map{ { '+', 1 },{ '-', 1 },{ '*', 2 },{ '/', 2 },{ '%', 2 } };

    for (auto elem = std::begin(infix); elem != std::end(infix); ++elem)
    {
        if (map.count(*elem))
        {
            postFix.push_back(*elem);
        }
        else if (*elem == '(')
        {
            postFix.push_back('(');
        }
        /* pop to postFix until another '(' is found */
        else if (*elem == ')')
        {
            while (stack.top() != 'N' && stack.top() != '(')
            {
                const char c = stack.top();
                stack.pop();
                postFix += c;
            }
            if (stack.top() == '(')
            {
                stack.pop();
            }
        }
        else
        {
            while (stack.top() != 'N' && map.at(*elem) <= map.at(stack.top()))
            {
                const char c = stack.top();
                stack.pop();
                postFix += c;
            }
            stack.push(*elem);
        }
    }
    /* Pop all remaining elements from the stack. */
    while (stack.top() != 'N')
    {
        char c = stack.top();
        stack.pop();
        postFix += c;
    }
    return postFix;
}

/* Splits a simple command into individual tokens then places them into a queue. */
std::queue<std::string> Compiler::split(const std::string &str)
{
    std::queue<std::string> queue;
    std::string token;
    std::stringstream ss(str);

    while (ss >> token)
    {
        queue.push(token);
    }
    return queue;
}
