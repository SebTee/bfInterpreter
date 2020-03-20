#ifndef BRAINFUCKINTERPRETER_MEMORY_H
#define BRAINFUCKINTERPRETER_MEMORY_H


#include <stdexcept>


class Memory {
private:
    char memory[30000] = {};

    char *ptr = memory;

public:
    void incrementMemoryIndex() {
        ptr++;
    }

    void decrementMemoryIndex() {
        ptr--;
    }

    void increment() {
        if(indexInRange()) {
            ++*ptr;
        } else {
            throw std::out_of_range("index out of range");
        }
    }

    void decrement() {
        if(indexInRange()) {
            --*ptr;
        } else {
            throw std::out_of_range("index out of range");
        }
    }

    char getValue() {
        if(indexInRange()) {
            return *ptr;
        } else {
            throw std::out_of_range("index out of range");
        }
    }

    void setValue(char value) {
        if(indexInRange()) {
            *ptr = value;
        } else {
            throw std::out_of_range("index out of range");
        }
    }

    bool indexInRange() {
        return ptr >= memory && ptr < memory + (sizeof(memory) / sizeof(memory[0]));
    }
};


#endif //BRAINFUCKINTERPRETER_MEMORY_H
