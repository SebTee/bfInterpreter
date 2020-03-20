#include "Memory.h"

void Memory::incrementMemoryIndex()  {
    ptr++;
}

void Memory::decrementMemoryIndex()  {
    ptr--;
}

void Memory::increment() {
    if(indexInRange()) {
        ++*ptr;
    } else {
        throw std::out_of_range("index out of range");
    }
}

void Memory::decrement() {
    if(indexInRange()) {
        --*ptr;
    } else {
        throw std::out_of_range("index out of range");
    }
}

char Memory::getValue()  {
    if(indexInRange()) {
        return *ptr;
    } else {
        throw std::out_of_range("index out of range");
    }
}

void Memory::setValue(char value)  {
    if(indexInRange()) {
        *ptr = value;
    } else {
        throw std::out_of_range("index out of range");
    }
}

bool Memory::indexInRange() {
        return ptr >= memory && ptr < memory + (sizeof(memory) / sizeof(memory[0]));
}