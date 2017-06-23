#ifndef GLOBAIS_H
#define GLOBAIS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Defs.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int false;
extern const int true;

extern const int IMAGE_WIDTH;
extern const int IMAGE_HEIGHT;

extern const int IMAGE_WIDTH_BARRA;
extern const int IMAGE_HEIGHT_BARRA;

extern const int IMAGE_WIDTH_BLOCO;
extern const int IMAGE_HEIGHT_BLOCO;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The imagem character
extern NPC ball;
extern NPC barra;
extern NPC bloco;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//Current displayed PNG image
extern SDL_Surface* gPNGFundo;
extern SDL_Surface* gJPGSurface;
extern SDL_Surface* gPNGBarra;
extern SDL_Surface* gPNGBloco;

extern Mix_Chunk* sound1;
extern Mix_Chunk* sound2;
extern Mix_Chunk* sound3;
extern Mix_Music* Trilha_sonora;

#endif
