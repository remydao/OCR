#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "character.h"
#include <SDL2/SDL.h>
#include "pixel.h"
#include "matrix.h"


void return_mat(SDL_Surface *surface, int myArray[][25])
{
           int a = surface->w;
	   int b = surface->h;
	   
           Uint32 pixel;
           Uint8 bleu;
           Uint8 rouge;
           Uint8 vert;
           for(int i = 0; i<b;i++)
           {
               for(int j = 0; j<a; j++)
               { 
                   pixel = getpixel(surface,j,i);
                   SDL_GetRGB(pixel,surface->format,&rouge,&bleu,&vert);
                   //printf("%i %i %i ", rouge, vert, bleu);
                   //printf("\n");
                   if (bleu > 128)
                   {
                        myArray[j][i] = 0;
                   }
                   else
                   {
                       myArray[j][i] = 1;
                   }
//utiliser le xor pour trouver la lettre
                   //printf("%i",myArray[j][i]);
               }
               //printf("\n");
           }

}


int xornn(int x, int y)
{
  if (x==y)
    {
      return 0;
    }
  else
    return 1;
}


void print_mat(SDL_Surface *surface)
{
           int a = surface->w;
	   int b = surface->h;
	   int myArray[25][25];
           Uint32 pixel;
           Uint8 bleu;
           Uint8 rouge;
           Uint8 vert;
           for(int i = 0; i<b;i++)
           {
               for(int j = 0; j<a; j++)
               { 
                   pixel = getpixel(surface,j,i);
                   SDL_GetRGB(pixel,surface->format,&rouge,&bleu,&vert);
                   //printf("%i %i %i ", rouge, vert, bleu);
                   //printf("\n");
                   if (bleu > 128 || rouge == 128)
                   {
                        myArray[j][i] = 0;
                   }
                   else
                   {
                       myArray[j][i] = 1;
                   }
//utiliser le xor pour trouver la lettre
                   printf("%i",myArray[j][i]);
               }
               printf("\n");
           }
           printf("\n");

}




char compare (SDL_Surface *surface,double tab_xor[])
{
	
	char path[]="alphabet/ ";
        int myArray[25][25];
        return_mat(surface, myArray);
        int lettre[25][25];
        int cpt_max = 0;
        int cpt;
        char c;
        SDL_Surface *tmp;
        
	// char alpha[]= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	for(path[9] = 'A'; path[9] <= 'Z'; path[9]++)
	{
           
           cpt = 0;
           tmp = SDL_LoadBMP(path);
	   return_mat(tmp, lettre);
           for(int i = 0; i<25;i++)
           {
               for(int j = 0; j<25; j++)
               { 
                    if(tab_xor[myArray[j][i] + lettre[j][i]] < 0.5)
                    {
                        cpt += 1;
                    }             
               }
                   
//utiliser le xor pour trouver la lettre
              
           }
           if(cpt > cpt_max)
           {               
               cpt_max = cpt;
               c = path[9];
           }
            
	}
        for(path[9] = 'a'; path[9] <= 'z'; path[9]++)
	{
           
           cpt = 0;
           tmp = SDL_LoadBMP(path);
	   return_mat(tmp, lettre);
           for(int i = 0; i<25;i++)
           {
               for(int j = 0; j<25; j++)
               { 
		 if(tab_xor[myArray[j][i] + lettre[j][i]] < 0.5)
                    {
                        cpt += 1;
                    }             
               }
                   
//utiliser le xor pour trouver la lettre
              
           }
           if(cpt > cpt_max)
           {               
               cpt_max = cpt;
               c = path[9];
           }
            
	}
	//printf("%i\n", cpt_max);
	if(cpt_max< 480)
	  {
	    c = ' ';
	  }
        //str[cpt];
        return c;

}
