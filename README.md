# A simple C compiler
Archiving the results of a compiler course from university. The aim of this project was to create a simple compiler that accepts a code in a simplified and restricted version of C in three stages:
1. Syntax Parser
2. Creation of an abstract syntax tree (AST)
3. Generating code for the RISC-V architecture

## The Language
The language that is accepted by the compiler has a variety of restrictions, for example:
- No complex structs
- Very limited pointers (enough for implementing [Quake III's fast inverse square root algorithm](https://en.wikipedia.org/wiki/Fast_inverse_square_root), see `q_rsqrt.c` and `plot_q_rsqrt.c` in the example inputs)
- No function calls except for some built-in ones for e.g. printing or file handling. This depends on the target the code shoudld get generated for.
- No imports
- Variables need to be declared at the start of a function.

Even though these restrictions seem to put hard limitations on what can be achieved with this language, some of the [included examples are relatively complex](example_inputs/mandelbrot_ppm.c). 

## Simulator
To run the generated RISC-V assembly code you can use for example
- [RARS - RISC-V Assembler and Runtime Simulator](https://github.com/TheThirdOne/rars). A bit slow but excellent for debugging assembly, provides features like File I/O and has good portability
- [Spike](https://github.com/riscv-software-src/riscv-isa-sim). More advanced but a bit tricky to get everything running properly. 
- [Trireme](https://www.trireme-riscv.org/simulator/index.html). Simple with limited supported (e.g. no floating point operations)

## Usage
- Build using the makefile: `make`
- Run on a input source file: `./bin/simple-compiler -r -p -o out.s FILE.c`
	- `-r` compiles for the RARS simulator. Other options are `-s` for Spike and `-t` for Trireme
	- `-p` produces a `.dot` file of the AST that can be plotted using e.g. `dot -Grankdir=LR -Tpng FILE.dot > FILE.png`
	- `-o out.s` gives the name of the output file for the simulator
	- `FILE.c` is the simple C source file to compile
- The resulting file `out.s` can be used with the chosen simulator:
	- Trireme: Copy & paste code into editor
	- RARS: Simply open the file, assemble and run.
	- Spike: Needs some additional steps. Run: 
	```
	rustriscv64-unknown-elf-as out.s
	riscv64-unknown-elf-ld a.out -o b.out
	spike pk b.out
	```
