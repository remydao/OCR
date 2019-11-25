#include "Greyscal.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include "pixel.h"

void makeitgrey(SDL_Surface *surface, int maxx, int maxy)
{
  for(int x=0; x!=maxx; x++)
    {
      for(int y=0; y!=maxy; y++)
	{ 
	  Uint8 red;
	  Uint8 blue;
	  Uint8 green;
	  Uint32 pixel = getpixel(surface, x, y);
	  SDL_GetRGB(pixel, surface->format, &red, &blue, &green);
	  uint8_t grey = (red + green + blue) / 3;
	  Uint32 pixel2= SDL_MapRGB(surface->format, grey, grey, grey);
	  putpixel(surface,x,y,pixel2);	  
	}
    }
}
void makeitblackandwhite(SDL_Surface *surface, int maxx, int maxy)
{
  for(int x=0; x!=maxx; x++)
    {
      for(int y=0; y!=maxy; y++)
	{
	  Uint8 red;
	  Uint8 blue;
	  Uint8 green;
	  Uint32 pixel = getpixel(surface, x, y);
	  SDL_GetRGB(pixel, surface->format, &red, &blue, &green);
	  if(red < 254)
	    {
	      Uint32 noir= SDL_MapRGB(surface->format, 0,0,0);
	      putpixel(surface,x,y,noir);
	    }
	  else
	    {
	      Uint32 blanc= SDL_MapRGB(surface->format,255,255,255);
	      putpixel(surface,x,y,blanc);
	    }
	}
    }
}
