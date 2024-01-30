.ONESHELL:

PROG    := simple-compiler

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE     := $(BIN_DIR)/$(PROG)
SRC     := $(wildcard $(SRC_DIR)/*.c)
OBJ     := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ     := $(OBJ) $(OBJ_DIR)/parser.tab.o $(OBJ_DIR)/lex.yy.o

# Compiler
CC      := gcc

# C PreProcessor
CPPFLAGS   := -Iinclude -MMD -MP
CFLAGS     := -Wall -pedantic -std=iso9899:2018
LDFLAGS    := 
LDLIBS     := -lm

DOT_FILES  := $(wildcard *.dot)
PNG_FILES  := $(patsubst %.dot,%.png,$(DOT_FILES))

# RISCV related programs
RISCV_AS   := riscv64-unknown-elf-as
RISCV_LD   := riscv64-unknown-elf-ld
SPIKE      := spike pk

# Directories for testing the compiler
INPUT_DIR  := inputs
OUTPUT_DIR := outputs

.PHONY: all clean

all: $(PNG_FILES)

%.png: %.dot
	dot -Tpng $< -o $@

all: $(EXE)

# Linking
$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Create Parser
$(SRC_DIR)/parser.tab.c: $(SRC_DIR)/parser.y
	bison -d -o $(SRC_DIR)/parser.tab.c $<

# Create Scanner
$(SRC_DIR)/lex.yy.c: $(SRC_DIR)/scanner.l
	flex -o $(SRC_DIR)/lex.yy.c $<

# Create directory for binary and object files
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@


# Clean artifacts
clean:
	rm -rvf $(OBJ_DIR)
	rm -rvf $(BIN_DIR)
	rm -rvf $(SRC_DIR)/lex.yy.c $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h $(SRC_DIR)/*.lis 
	make clean_outputs

clean_outputs:
	rm -vf $(INPUT_DIR)/*.s
	rm -vf $(OUTPUT_DIR)/*.s
	rm -vf $(OUTPUT_DIR)/*.o
	rm -vf $(OUTPUT_DIR)/*.out
	rm -vf $(OUTPUT_DIR)/*.ppm


# Build the given examples for Trireme simulator
trireme: 
	make clean_outputs

	./$(EXE)    $(INPUT_DIR)/expression.c      -t -o $(OUTPUT_DIR)/expression.s
	./$(EXE)    $(INPUT_DIR)/sqrt.c            -t -o $(OUTPUT_DIR)/sqrt.s


# Build for RARS
rars: 
	make clean_outputs

	./$(EXE)    $(INPUT_DIR)/expression.c      -r -o $(OUTPUT_DIR)/expression.s
	./$(EXE)    $(INPUT_DIR)/sqrt.c            -r -o $(OUTPUT_DIR)/sqrt.s
	./$(EXE)    $(INPUT_DIR)/primes.c          -r -o $(OUTPUT_DIR)/primes.s
	./$(EXE)    $(INPUT_DIR)/float_sqrt.c      -r -o $(OUTPUT_DIR)/float_sqrt.s
	./$(EXE)    $(INPUT_DIR)/mandelbrot_asci.c -r -o $(OUTPUT_DIR)/mandelbrot_asci.s
	./$(EXE)    $(INPUT_DIR)/mandelbrot_ppm.c  -r -o $(OUTPUT_DIR)/mandelbrot_ppm.s


# Build for Spike & Run
spike:
	make clean_outputs

	./$(EXE)    $(INPUT_DIR)/mandelbrot_asci.c -s -o $(OUTPUT_DIR)/mandelbrot_asci.s
	./$(EXE)    $(INPUT_DIR)/mandelbrot_ppm.c  -s -o $(OUTPUT_DIR)/mandelbrot_ppm.s

	$(RISCV_AS) $(OUTPUT_DIR)/mandelbrot_asci.s   -o $(OUTPUT_DIR)/mandelbrot_asci.o
	$(RISCV_AS) $(OUTPUT_DIR)/mandelbrot_ppm.s    -o $(OUTPUT_DIR)/mandelbrot_ppm.o

	$(RISCV_LD) $(OUTPUT_DIR)/mandelbrot_asci.o   -o $(OUTPUT_DIR)/mandelbrot_asci.out
	$(RISCV_LD) $(OUTPUT_DIR)/mandelbrot_ppm.o    -o $(OUTPUT_DIR)/mandelbrot_ppm.out

	cd          $(OUTPUT_DIR)               && $(SPIKE)            mandelbrot_asci.out
	cd          $(OUTPUT_DIR)               && $(SPIKE)            mandelbrot_ppm.out
