# Brainfuck Interpreter

This is a interpreter for the esoteric programming language Brainfuck.

## Instructions

### Compiling
```shell script
gcc main.cpp Interpreter.cpp Memory.cpp -lstdc++ -o bfInterpreter
```
You can replace `bfInterpreter` with any name for the outputted executable file. Make sure to use the correct file name when running the program.

### Running a brainfuck program
```shell script
./bfInterpreter /path/to/file.bf (input to the program)
```

#### examples

##### Hello World
This program outputs the line `Hello World!`
```shell script
./bfInterpreter ./examples/HelloWorld.bf
```

##### Mandelbrot
This program outputs the Mandelbrot set. This program was written by Erik Bosman.
```shell script
./bfInterpreter ./examples/mandelbrot.bf
```

##### Cat
This program just outputs the input string without changing it.
```shell script
./bfInterpreter ./examples/cat.bf This text is output!
```

###### Hello World Mk.2
This program will also output `Hello World!`
```shell script
./bfInterpreter ./examples/cat.bf Hello World!
```