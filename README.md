# A simple C compiler
Archiving the results of a compiler course from university. The aim of this project was to create a simple compiler that accepts a code in a simplified and restricted version of C in three stages:
1. Syntax Parser
2. Creation of an abstract syntax tree (AST)
3. Generating code for the RISC-V architecture

## The Language
The language that is accepted by the compiler has a variety of restrictions, for example:
- No complex structs
- No pointers (however, e.g. strings can be handled to some degree)
- No function calls except for some built-in ones for e.g. printing or file handling. This depends on the target the code shoudld get generated for.
- No imports
- Variables need to be declared at the start of a function.

Even though these restrictions seem to put hard limitations on what can be achieved with this language, some of the [included examples are relatively complex](example_inputs/mandelbrot_ppm.c). 

## Simulator
To run the generated RISC-V assembly code you can use for example
- [RARS - RISC-V Assembler and Runtime Simulator](https://github.com/TheThirdOne/rars). A bit slow but excellent for debugging assembly, provides features like File I/O and has good portability
- [Spike](https://github.com/riscv-software-src/riscv-isa-sim). More advanced but a bit tricky to get everything running properly. 
