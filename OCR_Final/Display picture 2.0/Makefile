# Simple Makefile

all: OCR NEURON

NEURON: neurone.o main_neurone.o
	gcc -o Neurone.exe neurone.o main_neurone.o -Wextra -Wall -std=c99 -lm

OCR: character.o Greyscal.o main.o pixel.o SDL2_rotozoom.o matrix.o neurone.o
	gcc -o Ocr.exe main.o pixel.o Greyscal.o character.o SDL2_rotozoom.o matrix.o neurone.o -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

main_neurone.o: neurone.c neurone.h main_neurone.c
	gcc -c neurone.c neurone.h main_neurone.c -Wall -Wextra -std=c99 -lm

character.o: neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h
	gcc -c neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

Greyscal.o: neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h
	gcc -c neurone.c neurone.h Greyscal.c character.c character.h Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

main.o: neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h
	gcc -c neurone.c neurone.h main.c Greyscal.c character.c character.h Greyscal.h pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

pixel.o: neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h
	gcc -c neurone.c neurone.h pixel.c main.c Greyscal.c character.c character.h Greyscal.h pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

SDL2_rotozoom.o: neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h
	gcc -c neurone.c neurone.h pixel.c main.c Greyscal.c character.c character.h Greyscal.h pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

matrix.o: neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h
	gcc -c neurone.c neurone.h pixel.c main.c Greyscal.c character.c character.h Greyscal.h pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

neurone.o: neurone.c neurone.h character.c character.h Greyscal.c Greyscal.h main.c pixel.c pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h
	gcc -c neurone.c neurone.h pixel.c main.c Greyscal.c character.c character.h Greyscal.h pixel.h SDL2_rotozoom.c SDL2_rotozoom.h matrix.c matrix.h -Wextra -Wall -std=c99 -lSDL2 -lm `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -f *.o
	rm -f *.gch
	rm -f *.exe
	rm -f *~
	rm -f *.c~


# END Makefile
