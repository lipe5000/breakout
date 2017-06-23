#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Defs.h"
#include "Globais.h"

void moveNPCBarra(NPC *p) {

	p->posX += p->stepX;

	if ( (p->posX + IMAGE_WIDTH_BARRA > SCREEN_WIDTH) ||
	     (p->posX < 0) ) {
		p->posX -= p->stepX;
	}
}

//Create NPC
NPC createNPC( int posX, int posY, int stepX, int stepY,
               SDL_Surface *image) {
    NPC p;

    p.posX = posX;
    p.posY = posY;
    p.stepX = stepX;
    p.stepY = stepY;
    p.image = image;
    return p;
}

int init() {
    //Initialization flag
    int success = true;

    srand(time(NULL));

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial: 06_moving_images", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Initialize JPG and PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }



    return success;
}

void closing() {
    //Free loaded image
    SDL_FreeSurface( gJPGSurface );
    gJPGSurface = NULL;

    SDL_FreeSurface( gPNGBloco );
    gPNGBloco = NULL;

    SDL_FreeSurface( gPNGBarra );
    gPNGBarra = NULL;

		SDL_FreeSurface(gPNGFundo);
    gPNGFundo = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    Mix_FreeChunk(sound1);
    Mix_FreeChunk(sound2);
    Mix_FreeChunk(sound3);
		Mix_CloseAudio();
    SDL_Quit();
}

SDL_Surface* loadSurface( char *path ) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {

		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

int loadMedia() {
    //Loading success flag
    int success = true;
    //uint32_t colorKey;

    //Load PNG surface
    gJPGSurface = loadSurface( "./circle.png" );
    if( gJPGSurface == NULL ) {
        printf( "Failed to load image circle! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    gPNGBarra = loadSurface( "./barra.png" );
    if( gPNGBarra == NULL ) {
        printf( "Failed to load image barra! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    gPNGBloco = loadSurface( "./bloco.png" );
    if( gPNGBarra == NULL ) {
        printf( "Failed to load image barra! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

		gPNGFundo = loadSurface( "./imagem_naruto.png" );
    if( gPNGFundo == NULL ) {
        printf( "Failed to load image Fundo! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    return success;
}

void moveNPC(NPC *p, short int **blocos) {
    p->posX += p->stepX;
    p->posY += p->stepY;

    int centroX;
    int centroY;
    int i, j;

    centroX = p->posX + (IMAGE_WIDTH / 2);
    centroY = p->posY + (IMAGE_HEIGHT / 2);

    if ( (p->posX + IMAGE_WIDTH > SCREEN_WIDTH) ||
         (p->posX < 0) ) {
        p->stepX = -p->stepX;
        p->posX += p->stepX;
        Mix_PlayChannel(-1, sound3, 0);
    }
    if ( p->posY + IMAGE_HEIGHT > SCREEN_HEIGHT ) {

        /*closing();*/

        p->stepY = -p->stepY;
        p->posY += p->stepY;
        Mix_PlayChannel(-1, sound1, 0);
    }
    if ( p->posY < 0 ) {
		p->stepY = -p->stepY;
		p->posY += p->stepY;
		Mix_PlayChannel(-1, sound2, 0);
	}

	if( (barra.posY - centroY < IMAGE_HEIGHT / 2) &&
		( (centroX > barra.posX) &&
	    (centroX < barra.posX + IMAGE_WIDTH_BARRA) )) {
		p->stepY = -p->stepY;
		p->posY += p->stepY;
	}
	for(i = 0; i < 5; i++){
		for(j = 0; j < 16; j++){
			if(blocos[i][j]){

				/* teste para checar se a bola esta em baixo */
				if(IMAGE_HEIGHT_BLOCO * (i + 1) <= centroY){
					if(((centroY - (IMAGE_HEIGHT_BLOCO * (i + 1))) < IMAGE_HEIGHT / 2) &&
					   (centroX > IMAGE_WIDTH_BLOCO * j) &&
					   (centroX < IMAGE_WIDTH_BLOCO * (j + 1))){
						blocos[i][j] -= 1;
						p->stepY = -p->stepY;
						p->posY += p->stepY;
					}

					/*else if((centroX < IMAGE_WIDTH_BLOCO * j) &&
					       ( sqrt( (IMAGE_WIDTH_BLOCO * i - centroX) * (IMAGE_WIDTH_BLOCO * i - centroX) + (centroY - IMAGE_HEIGHT_BLOCO * (i + 1)) * (IMAGE_WIDTH_BLOCO * (i + 1) - centroX) ) < IMAGE_HEIGHT / 2 )){
						blocos[i][j] -= 1;
						p->stepY = -p->stepY;
						p->posY += p->stepY;
						p->stepX = -p->stepX;
						p->posX += p->stepX;

					}

					else if((centroX > IMAGE_WIDTH_BLOCO * j) &&
					       (sqrt( ( centroX - IMAGE_WIDTH_BLOCO * (i + 1)) * ( centroX - IMAGE_WIDTH_BLOCO * (i + 1)) + (centroY - IMAGE_HEIGHT_BLOCO * (i + 1)) * (centroY - IMAGE_HEIGHT_BLOCO * (i + 1)) ) < IMAGE_HEIGHT / 2)){

						blocos[i][j] -= 1;
						p->stepY = -p->stepY;
						p->posY += p->stepY;
						p->stepX = -p->stepX;
						p->posX += p->stepX;
					}*/
				}

				/* teste para checar se a bola esta em cima */
				if(IMAGE_HEIGHT_BLOCO * i >= centroY){
					if(((IMAGE_HEIGHT_BLOCO * i - centroY) < IMAGE_HEIGHT / 2) &&
					   (centroX > IMAGE_WIDTH_BLOCO * j) &&
					   (centroX < IMAGE_WIDTH_BLOCO * (j + 1))){
						blocos[i][j] -= 1;
						p->stepY = -p->stepY;
						p->posY += p->stepY;
					}

					/*else if((centroX < IMAGE_WIDTH_BLOCO * j) &&
					       ( sqrt( (IMAGE_WIDTH_BLOCO * i - centroX) * (IMAGE_WIDTH_BLOCO * i - centroX) + (IMAGE_HEIGHT_BLOCO * i - centroY) * (IMAGE_HEIGHT_BLOCO * i - centroY) ) < IMAGE_HEIGHT / 2)){
						blocos[i][j] -= 1;
						p->stepY = -p->stepY;
						p->stepX = -p->stepX;
						p->posY += p->stepY;
						p->posX += p->stepX;

					}

					else if((centroX > IMAGE_WIDTH_BLOCO * (j + 1)) &&
					       (sqrt( (centroX - IMAGE_WIDTH_BLOCO * (i + 1)) * (centroX - IMAGE_WIDTH_BLOCO * (i + 1)) + (IMAGE_HEIGHT_BLOCO * i - centroY) * (IMAGE_HEIGHT_BLOCO * i - centroY) ) < IMAGE_HEIGHT / 2)){

						blocos[i][j] -= 1;
						p->stepY = -p->stepY;
						p->stepX = -p->stepX;
						p->posY += p->stepY;
						p->posX += p->stepX;
					}*/
				}
			}
		}
	}
}
