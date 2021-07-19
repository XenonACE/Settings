CC = tcc

all: settings

settings: main.c
	$(CC) -Wall -Wextra -o $@ `pkg-config gtk+-3.0 --cflags --libs` $^

install: settings
	mv $^ /usr/local/bin

.PHONY: clean

clean:
	rm -f settings
