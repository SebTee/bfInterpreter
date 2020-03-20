#ifndef BRAINFUCKINTERPRETER_INTERPRETER_H
#define BRAINFUCKINTERPRETER_INTERPRETER_H


#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stack>
#include "Memory.h"

class Interpreter {
private:
    std::unordered_map <char, void(Interpreter::*)()> commands = {
            {'>', &Interpreter::nextMemoryLocation},
            {'<', &Interpreter::previousMemoryLocation},
            {'+', &Interpreter::increment},
            {'-', &Interpreter::decrement},
            {'.', &Interpreter::output},
            {',', &Interpreter::input},
            {'[', &Interpreter::whileBegin},
            {']', &Interpreter::whileEnd}
    };
    std::unordered_map <int, int> whileIndexes;
    Memory memory;
    std::stack <char> inputBuffer;
    std::string program;
    int programIndex;

public:
    explicit Interpreter(const std::string &filePath, const std::string &input);
    void loadInputBuffer(std::string input);
    void loadProgram(std::ifstream &bfFile);
    void run();
    void increment();
    void decrement();
    void output();
    void input();
    void nextMemoryLocation();
    void previousMemoryLocation();
    void whileBegin();
    void whileEnd();
    bool isValidCommand(char command);
};


#endif //BRAINFUCKINTERPRETER_INTERPRETER_H
