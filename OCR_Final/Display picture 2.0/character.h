#ifndef CHARACTER_H
#define CHARACTER_H
#include <SDL2/SDL.h>

//variable global
extern char str[1000];
extern char str2[1000];

void LinesAllWhiteInRed (SDL_Surface *surface);
void BlockOfCharacter (SDL_Surface *surface, SDL_Surface *screen );
void ColumnsAllWhiteInRed (SDL_Surface *surface);
void BlockOfColumn (SDL_Surface *surface, SDL_Surface *screen, int k, char c[], double a[]);
unsigned long ligne(SDL_Surface *surface);
SDL_Surface* RognerCharacter(SDL_Surface *surface);


#endif
