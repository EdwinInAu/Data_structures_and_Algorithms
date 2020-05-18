CC=dcc
CFLAGS=-O3
puzzle: puzzle.o boardADT.o
	$(CC) $(CFLAGS) -o puzzle puzzle.o boardADT.o

puzzle.o: puzzle.c boardADT.h
	$(CC) $(CFLAGS) -c puzzle.c

boardADT.o: boardADT.c boardADT.h
	$(CC) $(CFLAGS) -c boardADT.c

clean:
	rm -f client puzzle.o boardADT.o core