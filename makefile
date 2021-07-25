# makefile for assignment 5
# Yibo Yang, 04/26/2016

EXE = vm
OBJS = TLB.cpp PageTable.cpp BackingStore.cpp Memory.cpp Byte.cpp main.cpp
FLAGS = -g -Wall -std=c++11

$(EXE):	$(OBJS)
	g++ $(FLAGS) -o $(EXE) $(OBJS)
clean:
	rm -f $(EXE)
