# Executable names:
EXE = fp
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o 

OBJS += 

# Generated files
CLEAN_RM = gridtest-actual.png test_result_*.kd

# Use the cs225 makefile template:
include cs225/make/cs225.mk