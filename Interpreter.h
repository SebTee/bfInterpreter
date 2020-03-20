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

    Memory memory = Memory();

    std::stack <char> inputBuffer;

    std::string program = "";

    int programIndex = 0;

public:
    explicit Interpreter(const std::string &filePath, const std::string &input) {
        std::ifstream bfFile (filePath, std::ios::in);
        if (!bfFile) {
            throw std::invalid_argument("file not found");
        }
        loadProgram(bfFile);
        bfFile.close();
        loadInputBuffer(input);
    }

    void loadInputBuffer(std::string input) {
        for (unsigned long i = input.length(); i > 0; i--) {
            inputBuffer.push(input.at(i - 1));
        }
    }

    void loadProgram(std::ifstream &bfFile) {
        char currChar;
        std::stack <int> whileBeginIndexStack;
        do {
            currChar = bfFile.get();
            if (isValidCommand(currChar)) {
                program.push_back(currChar);
                if (currChar == '[') {
                    whileBeginIndexStack.push(program.length() - 1);
                } else if (currChar == ']') {
                    if (whileBeginIndexStack.empty()) {
                        throw std::logic_error("while ending exists without a beginning");
                    }
                    whileIndexes[whileBeginIndexStack.top()] = program.length() - 1;
                    whileIndexes[program.length() - 1] = whileBeginIndexStack.top();
                    whileBeginIndexStack.pop();
                }
            }
        } while (currChar != -1);
        if (!whileBeginIndexStack.empty()) {
            throw std::logic_error("while beginning exists without an ending");
        }
    }

    void run() {
        while (programIndex < program.length()) {
            char command = program.at(programIndex);
            (this->*commands[command])();
            programIndex++;
        }
    }

    void increment() {
        memory.increment();
    }

    void decrement() {
        memory.decrement();
    }

    void output() {
        std::cout << memory.getValue();
    }

    void input() {
        if (inputBuffer.empty()) {
            memory.setValue(0);
        } else {
            memory.setValue(inputBuffer.top());
            inputBuffer.pop();
        }
    }

    void nextMemoryLocation() {
        memory.incrementMemoryIndex();
    }

    void previousMemoryLocation() {
        memory.decrementMemoryIndex();
    }

    void whileBegin() {
        if (memory.getValue() == 0) {
            programIndex = whileIndexes[programIndex];
        }
    }

    void whileEnd() {
        if (memory.getValue() != 0) {
            programIndex = whileIndexes[programIndex];
        }
    }

    bool isValidCommand(char command) {
        return !(commands.find(command) == commands.end());
    }
};


#endif //BRAINFUCKINTERPRETER_INTERPRETER_H
