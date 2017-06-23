#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Defs.h"
#include "Globais.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int false = 0;
const int true = 1;

const int IMAGE_WIDTH = 30;
const int IMAGE_HEIGHT = 30;

const int IMAGE_WIDTH_BARRA = 155;
const int IMAGE_HEIGHT_BARRA = 13;

const int IMAGE_WIDTH_BLOCO = 40;
const int IMAGE_HEIGHT_BLOCO = 30;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The imagem character
NPC ball;
NPC barra;
NPC bloco;
  
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gJPGSurface = NULL;
SDL_Surface* gPNGBarra = NULL;
SDL_Surface* gPNGBloco = NULL;

Mix_Chunk* sound1;
Mix_Chunk* sound2;
Mix_Chunk* sound3;
