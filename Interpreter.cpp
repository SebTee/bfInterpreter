#include "Interpreter.h"

Interpreter::Interpreter(const std::string &filePath, const std::string &input)  {
    programIndex = 0;
    std::ifstream bfFile (filePath, std::ios::in);
    if (!bfFile) {
        throw std::invalid_argument("file not found");
    }
    loadProgram(bfFile);
    bfFile.close();
    loadInputBuffer(input);
}

void Interpreter::loadInputBuffer(std::string input) {
    for (unsigned long i = input.length(); i > 0; i--) {
        inputBuffer.push(input.at(i - 1));
    }
}

void Interpreter::loadProgram(std::ifstream &bfFile) {
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

void Interpreter::run() {
    while (programIndex < program.length()) {
        char command = program.at(programIndex);
        (this->*commands[command])();
        programIndex++;
    }
    std::cout << '\n';
}

void Interpreter::increment() {
    memory.increment();
}

void Interpreter::decrement() {
    memory.decrement();
}

void Interpreter::output() {
    std::cout << memory.getValue();
}

void Interpreter::input() {
    if (inputBuffer.empty()) {
        memory.setValue(0);
    } else {
        memory.setValue(inputBuffer.top());
        inputBuffer.pop();
    }
}

void Interpreter::nextMemoryLocation() {
    memory.incrementMemoryIndex();
}

void Interpreter::previousMemoryLocation() {
    memory.decrementMemoryIndex();
}

void Interpreter::whileBegin() {
    if (memory.getValue() == 0) {
        programIndex = whileIndexes[programIndex];
    }
}

void Interpreter::whileEnd() {
    if (memory.getValue() != 0) {
        programIndex = whileIndexes[programIndex];
    }
}

bool Interpreter::isValidCommand(char command) {
    return !(commands.find(command) == commands.end());
}