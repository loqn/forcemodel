# Thomas Daley
# September 13, 2021

# A generic build template for C/C++ programs

# executable name
EXE = demo
# C++ compiler
CXX = g++
# linker
LD = g++

# C++ flags
CXXFLAGS = -std=c++17 -O3
# C/C++ flags
CPPFLAGS = -Wall

# dependency-generation flags
DEPFLAGS = -MMD -MP
# linker flags
LDFLAGS = 
# library flags
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -pthread

INCLUDE = -I./include -I./cxx

# build directories
BIN = bin
OBJ = obj
SRC = src

SOURCES := $(wildcard $(SRC)/*.c $(SRC)/*.cc $(SRC)/*.cpp $(SRC)/*.cxx)

OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp)) 


# include compiler-generated dependency rules
DEPENDS := $(OBJECTS:.o=.d)

# compile C++ source
COMPILE.cxx = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDE) -c -o $@
# link objects
LINK.o = $(LD) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

.DEFAULT_GOAL = all

.PHONY: all
all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(SRC) $(OBJ) $(BIN) $(OBJECTS)
	$(LINK.o)

$(OBJ):
	mkdir -p $(OBJ)

$(OBJ)/%.o:	$(SRC)/%.cpp
	$(COMPILE.cxx) $<

# force rebuild
.PHONY: remake
remake:	clean $(BIN)/$(EXE)

# execute the program
.PHONY: run
run: $(BIN)/$(EXE)
	./$(BIN)/$(EXE)

# profile run with gprof
.PHONY: profile
profile: $(BIN)/$(EXE)
	./$(BIN)/$(EXE) datasets/hollywood.csv
	gprof $(BIN)/$(EXE) gmon.out > profile_results.txt
	@echo "Profiling results saved to profile_results.txt"


# remove previous build and objects
.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(DEPENDS)
	$(RM) $(BIN)/$(EXE)

# remove everything except source
.PHONY: reset
reset:
	$(RM) -r $(OBJ)
	$(RM) -r $(BIN)

test:
	./build.sh
	./bin/demo datasets/hollywood.csv

-include $(DEPENDS)
