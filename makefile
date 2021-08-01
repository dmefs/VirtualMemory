# makefile for assignment 5
# Yibo Yang, 04/26/2016

EXE = vm
OBJS = TLB.cpp PageTable.cpp BackingStore.cpp Memory.cpp Line.cpp main.cpp FeistelNetwork.cpp
FLAGS = -g -Wall -std=c++11

$(EXE):	$(OBJS)
	g++ $(FLAGS) -o $(EXE) $(OBJS)

test: $(EXE)
	./vm -F sample_input.txt

clean:
	rm -f $(EXE)
