CC = gcc
CFLAGS = -Wall -g -MMD
OBJS = ice40.o
PROG = ice40

all: $(PROG)

$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

valgrind: $(PGM)
	valgrind --track-origins=yes $(PGM)
clean:
	rm -f *.o ice40
