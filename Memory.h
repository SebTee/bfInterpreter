#ifndef BRAINFUCKINTERPRETER_MEMORY_H
#define BRAINFUCKINTERPRETER_MEMORY_H


#include <stdexcept>

class Memory {
private:
    char memory[30000] = {};
    char *ptr = memory;

public:
    void incrementMemoryIndex();
    void decrementMemoryIndex();
    void increment();
    void decrement();
    char getValue();
    void setValue(char value);
    bool indexInRange();
};


#endif //BRAINFUCKINTERPRETER_MEMORY_H
