#ifndef FUNCOES_H
#define FUNCOES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include "Defs.h"
#include "Globais.h"

int init();

//Frees media and shuts down SDL
void closing();

//Loads individual image
SDL_Surface* loadSurface( char *path );

//Loads media
int loadMedia();

//Create NPC
NPC createNPC( int posX, int posY, int stepX, int stepY, SDL_Surface *image);

//Move NPC
void moveNPC(NPC *p, short int **blocos);
void moveNPCBarra(NPC *p);

#endif
