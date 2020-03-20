#include "Interpreter.h"

int main(int argc, char *argv[]) {
    std::string filePath;
    std::string input;
    if (argc < 2) {
        throw std::invalid_argument("no bf file path supplied");
    } else {
        filePath = argv[1];
        if (argc > 2) {
            for (int i = 2; i < argc; i++) {
                input += argv[i];
                if (i < argc - 1) {
                    input += ' ';
                }
            }
        }
    }
    Interpreter interpreter = Interpreter(filePath, input);
    interpreter.run();
    return 0;
}