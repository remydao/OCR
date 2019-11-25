# Simple Makefile

# Compilers vars

all: xor

xor: main.o neurone.o
	gcc -o Xor.exe main.o neurone.o -Wall -Wextra -Werror -std=c99 -lm

main.o: main.c neurone.c neurone.h
	gcc -c main.c neurone.c neurone.h -Wall -Wextra -Werror -std=c99 -lm

neurone.o: main.c neurone.c neurone.h
	gcc -c neurone.c main.c neurone.h -Wall -Wextra -Werror -std=c99 -lm



clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.gch

# END Makefile
