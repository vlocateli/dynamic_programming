
#WOrks only on Unix or Posix compatible systems
CC=gcc
FLAGS=-Wall -Wextra -Werror -pedantic -std=c11 -O2 -march=native 
FILES=src/main.c
INCLUDES=include/ep_1.h

all:lcs

lcs: $(FILES $(INCLUDES)
	$(CC) $(FLAGS) $(FILES) -o lcs

clean:
	rm -rf lcs
