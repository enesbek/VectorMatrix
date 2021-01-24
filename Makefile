# compiler
GCC = g++

# flags
FLAGS = -Wall -g

# lib file
LIB = lal.cpp

# source file
SOURCE = test.cpp

# out file
OUT = test.x

all:
	$(GCC) $(FLAGS) $(LIB) $(SOURCE) -o $(OUT)
	./test.x

clean:
	rm -rf $(OUT)
