CC=gcc
FLAGS= -Wall -g


all:connections

connections: Graph.o
	$(CC) $(FLAGS) -o  connections Graph.o
Graph.o: Graph.c  Graph.h
	$(CC) $(FLAGS) -c Graph.c 

.PHONY: clean all

clean:
	rm -f *.o *.a *.so connections