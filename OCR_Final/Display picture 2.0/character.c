#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include <SDL2/SDL.h>
#include "pixel.h"
#include "matrix.h"
#include "SDL2_rotozoom.h"
#include "neurone.h"

char str[1000];
char str2[1000];

void LinesAllWhiteInRed (SDL_Surface *surface) /*Transform the line all white in red*/
 {
    

    SDL_LockSurface(surface); /*Here we lock the surface*/
    for (int y=0;y<surface->h;y++)
    {
        int AllWhite = 1;
      
        for (int x=0;x<surface->w;x++)
        {
	  Uint32 pixel = getpixel(surface,x, y);
	  Uint8 bleu;
	  Uint8 rouge;
	  Uint8 vert;
	  SDL_GetRGB(pixel, surface->format, &rouge, &vert, &bleu);
	  if(bleu!=255)
	    AllWhite = 0;
	    
        }
	if(AllWhite)
	  {  
	  for( int k = 0; k < surface->w; k++) /*Transform the line all white in red*/
	    {
              Uint32 pixelR = SDL_MapRGB(surface->format, 128, 0 ,0);
	      putpixel(surface, k, y, pixelR);	      
	    }
	  }    
    }
   
    SDL_UnlockSurface(surface); /*Here we unlock the surface, it can be used*/
 }

  
void BlockOfCharacter (SDL_Surface *surface, SDL_Surface *screen)
{
  size_t SIZE = 3;
  double tab_xor[SIZE];
  tab_xor[0] = xorn(0,0);
  tab_xor[1] = xorn(0,1);
  tab_xor[2] = xorn(1,1);
  int ymax = 0;
  int ymin = 0;
  int valid = 0;
  int isBloc = 0;
  int h = 0;
  SDL_Rect srcrect;
  SDL_Surface *newsurface;
  Uint32 pixel;
  Uint8 bleu;
  Uint8 rouge;
  Uint8 vert;
  char c[] = "A";
  for(int y = 0; y < surface->h; y++) /*browse the first column of the surface*/
  {
     
       pixel = getpixel(surface, 0, y);
       SDL_GetRGB(pixel, surface->format, &rouge,&vert, &bleu);
       if(rouge != 128)
	 {
	   valid = 1;
	   ymax = y;
	   ymin = y;
	   while(valid && ymax < surface->h)
	     {
	    ymax++;
	    pixel = getpixel(surface, 0, ymax);
	    SDL_GetRGB(pixel, surface->format, &rouge,&vert, &bleu);
	    if(rouge == 128)
	      valid = 0;
	     }

	   isBloc = 1;
	 }

       if(isBloc)
	 {

           SDL_UnlockSurface(surface);
	   h += 200;
	   srcrect.x = 0;
	   srcrect.y = ymin;
	   srcrect.w = surface->w;
	   srcrect.h = ymax - ymin;
	   newsurface = SDL_CreateRGBSurface(SDL_SWSURFACE, srcrect.w,srcrect.h, 32, 0, 0, 0, 0);
	   SDL_BlitSurface(surface, &srcrect, newsurface, NULL);
           ColumnsAllWhiteInRed(newsurface); /*Transform the columns all white in red*/
	   BlockOfColumn(newsurface, screen, h, c , tab_xor); /*split the characters of the block of text and display them on the screen*/
	   strcat(str, str2);
	   strcat(str, "\n");
	   isBloc = 0;
	   y = ymax;
	 }
  }
//SDL_FreeSurface(newsurface);
}



void BlockOfColumn (SDL_Surface *surface, SDL_Surface *screen, int k,char c[], double xorr[]) /*split the block of column of a surface and display them in the screen*/
{
  int xmax = 0;
  int xmin = 0;
  int valid = 0;
  int isBloc = 0;
  int h = 0;
  double a;
  double b;
  int index = 0;
  char string[1000];
  int espace;
  int pos_char1 = 0;
  SDL_Surface *newsurface;
  SDL_Surface *newsurface2;
  SDL_Surface *newsurface3;
  SDL_Rect srcrect;
  SDL_Rect s2;
  Uint32 pixel;
  Uint8 bleu;
  Uint8 rouge;
  Uint8 vert;

  for(int x = 0; x < surface->w; x++)
  {
     
       pixel = getpixel(surface, x, 0);
       SDL_GetRGB(pixel, surface->format, &rouge,&vert, &bleu);
       if(rouge != 128)
	 {
	   valid = 1;
	   xmax = x;
	   xmin = x;
	   while(valid && xmax < surface->w)
	     {
	    xmax++;
	    pixel = getpixel(surface, xmax, 0);
	    SDL_GetRGB(pixel, surface->format, &rouge,&vert, &bleu);
	    if(rouge == 128)
	      valid = 0;
	     }

	   isBloc = 1;
	 }

       if(isBloc)
	 {

           SDL_UnlockSurface(surface);
	   h += 100;
           espace = xmin - pos_char1;
	   srcrect.x = xmin;
	   srcrect.y = 0;
	   srcrect.w = xmax - xmin;
	   srcrect.h = surface->h;
	   newsurface = SDL_CreateRGBSurface(SDL_SWSURFACE, srcrect.w,srcrect.h, 32, 0, 0, 0, 0); /*create a new surface with a size equal to srcrect*/
	   SDL_BlitSurface(surface, &srcrect, newsurface, NULL);
	   LinesAllWhiteInRed(newsurface);
	   newsurface2 = RognerCharacter(newsurface);
	   s2.x = h;
	   s2.y = k;
           a = (double)25/ (double)newsurface2->w;
           b = (double)25/ (double)newsurface2->h;
           newsurface3 = rotozoomSurfaceXY(newsurface2, 0, a, b, 0);
           SDL_FreeSurface(newsurface);
           SDL_FreeSurface(newsurface2);
           //SDL_SaveBMP(newsurface3, c);
           if(c[0] == 'Z')
           {
               c[0] = 'a';
           }
           else
           {
              c[0]++;
           }
           SDL_ConvertSurface(newsurface3, surface->format, 0);
           //print_mat(newsurface3);
           if(espace > 25)
           {
               string[index] = ' ';
               index++;
           }
           string[index] = compare(newsurface3,xorr);
	   SDL_UnlockSurface(surface);
	   SDL_BlitSurface(newsurface3, NULL, screen, &s2);/*display the new surface on the screen*/
	   isBloc = 0;
	   x = xmax;
           index++;
           pos_char1 = xmax;
	 }
  }
  string[index] = '\0';
  strcpy(str2, string);
}
  
unsigned long ligne(SDL_Surface *surface)/*count the number of blocks of lines in a surface*/
{
  Uint32 pixel;
  Uint8 bleu;
  Uint8 rouge;
  Uint8 vert;
  unsigned long cpt=0;
  unsigned long cptb=0;
  for(long  y=0; y<surface->h;y++) /* We browse all the y surface */
    {
      pixel = getpixel(surface, 0, y);
      SDL_GetRGB(pixel, surface->format, &rouge ,&vert, &bleu); /*We store the RGB value in the value created previously*/
      if(rouge!=128)
	{
	  cptb=0;
	}
      else
	{
	  cptb+=1;
	}
      if(cptb==1)
	{
	  cpt+=1;
	}
    }
  return cpt;
}
              
    
      
void ColumnsAllWhiteInRed (SDL_Surface *surface) /*Transform the lines all white in red*/
  {

    Uint32 pixel;
    Uint8 bleu;
    Uint8 rouge;
    Uint8 vert;
    int AllWhite;
    Uint32 pixelR;
    SDL_LockSurface(surface); /*Here we lock the surface*/
    for (int x=0;x<surface->w;x++)
    {
        AllWhite = 1;
      
        for (int y=0;y<surface->h;y++)
        {
	  pixel = getpixel(surface,x, y);
	  SDL_GetRGB(pixel, surface->format, &rouge, &vert, &bleu);
	  if(bleu == 0 && vert == 0)
	    AllWhite = 0;
        }
	if(AllWhite)
	  {
	  for(int k = 0; k < surface->h; k++) /*Transform the line all white in red*/
	    {
              pixelR = SDL_MapRGB(surface->format, 128, 0 ,0);
	      putpixel(surface, x, k, pixelR);
	    }
	  }
    }
    

    SDL_UnlockSurface(surface); /*Here we unlock the surface, it can be used*/
 }
 
 
 SDL_Surface* RognerCharacter(SDL_Surface *newsurface)
 {
  int yfin = 0;
  int ydebut = 0;
  SDL_Rect srcrect;
  SDL_Surface *newsurface2;
  Uint32 pixel;
  Uint8 bleu;
  Uint8 rouge;
  Uint8 vert;

  for(int y = 0; y < newsurface->h; y++) /*browse the first column of the surface*/
  {
     
       pixel = getpixel(newsurface, 0, y);
       SDL_GetRGB(pixel, newsurface->format, &rouge,&vert, &bleu);
       if(rouge != 128)
	 {
	   ydebut = y;
	   y = newsurface->h;
	 }
  }
  for(int y = newsurface->h - 1; y > ydebut; y--) /*browse the first column of the surface*/
  {
     
       pixel = getpixel(newsurface, 0, y);
       SDL_GetRGB(pixel, newsurface->format, &rouge,&vert, &bleu);
       if(rouge != 128)
	 {
	   yfin = y;
	   y = ydebut;
	 }	 
  }
  SDL_UnlockSurface(newsurface);
  srcrect.x = 0;
  srcrect.y = ydebut;
  srcrect.w = newsurface->w;
  srcrect.h = yfin - ydebut;
  newsurface2 = SDL_CreateRGBSurface(SDL_SWSURFACE, srcrect.w,srcrect.h, 32, 0, 0, 0, 0);
  SDL_BlitSurface(newsurface, &srcrect, newsurface2, NULL);
	 
  return newsurface2;
//SDL_FreeSurface(newsurface);
}


