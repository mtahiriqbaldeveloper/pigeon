flags=-O2 -Wall -std=c2x
ldflags=birchutils.so

.PHONY: all clean

all: clean pigeon client

pigeon: pigeon.o
	cc $(flags) $^ -o $@ $(ldflags)

pigeon.o: pigeon.c pigeon.h
	cc $(flags) -c $<

client: client.o
	cc $(flags) $^ -o $@ $(ldflags)

client.o: client.c pigeon.h
	cc $(flags) -c $<
clean:
	rm -f *.o pigeon client