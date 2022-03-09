# makefile for assignment 5
# Yibo Yang, 04/26/2016

EXE = vm
INCLUDES = TLB.h PageTable.h Memory.h Line.h FeistelNetwork.h
OBJS = TLB.cpp PageTable.cpp BackingStore.cpp Memory.cpp Line.cpp main.cpp FeistelNetwork.cpp
FLAGS = -g -Wall -std=c++11
CPP=g++

all: orig startgap feistel

orig:	$(OBJS) $(INCLUDES)
	$(CPP) $(FLAGS) -o bin/$(EXE) $(OBJS)

startgap: $(OBJS) $(INCLUDES)
	$(CPP) -DSTART_GAP $(FLAGS) -o bin/$@ $(OBJS)

feistel: $(OBJS) $(INCLUDES)
	$(CPP) -DFEISTEL $(FLAGS) -o bin/$@ $(OBJS)

test: $(EXE)
	./bin/vm -F sample_input.txt

clean:
	rm -f $(EXE)

dir:
	mkdir -p bin
