#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Defs.h"
#include "Globais.h"
#include "funcoes.h"

int main( int argc, char* args[] ) {
    SDL_Rect srcRect, dstRect;

    int inicio = 0;
    int i, j;
    short int **blocos;

    blocos = (short int **) calloc(5, sizeof(short int *));
    if (!blocos) {
        printf("Erro ao alocar memoria");
		return 10;
    }
    for (i = 0; i < 5; i++) {
        blocos[i] = (short int *) calloc(16, sizeof(short int));
        if (!blocos[i]) {
            printf("Erro ao alocar memoria");
            return 11;
        }
    }

    for(i = 0; i < 5; i++){
		for(j = 0; j < 16; j++){
			blocos[i][j] = 1;
		}
	}

    //Start up SDL and create window
    if( !init() ) {
        printf( "Failed to initialize!\n" );
    }
    else {
        //Load media
        if( !loadMedia() ) {
            printf( "Failed to load media!\n" );
        }
        else {
            //Create NPC
            ball = createNPC((SCREEN_WIDTH - IMAGE_WIDTH)/2,
                             SCREEN_HEIGHT - IMAGE_HEIGHT - 2 * IMAGE_HEIGHT_BARRA,
                             0,
                             0,
                             gJPGSurface);

            barra = createNPC((SCREEN_WIDTH - IMAGE_WIDTH_BARRA) / 2,
							  (SCREEN_HEIGHT - 2 * IMAGE_HEIGHT_BARRA),
							  0,
							  0,
							  gPNGBarra);

			bloco = createNPC(0,
							  0,
							  0,
							  0,
							  gPNGBloco);

            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
            Mix_AllocateChannels(16);

      sound1 = Mix_LoadWAV("sound1.wav");
			if (!sound1) {
				printf("Wav: SDL error=%s\n", SDL_GetError());
				printf("Failed to load sound1");
			}

			sound2 = Mix_LoadWAV("sound2.wav");
			if (!sound2) {
				printf("Wav: SDL error=%s\n", SDL_GetError());
				printf("Failed to load sound1");
			}

			sound3 = Mix_LoadWAV("sound3.wav");
			if (!sound3) {
				printf("Wav: SDL error=%s\n", SDL_GetError());
				printf("Failed to load sound1");
			}
      Trilha_sonora = Mix_LoadMUS("The_Raising_Fighting_Spirit.mp3");
			if (!Trilha_sonora) {
				printf("Wav: SDL error=%s\n", SDL_GetError());
				printf("Failed to load Trilha_sonora'");
			}

      Mix_PlayMusic(Trilha_sonora,-1);
            //Main loop flag
            int quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit ) {
                while( SDL_PollEvent( &e ) != 0 ) {
                    switch (e.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_KEYDOWN:
                            if (e.key.keysym.sym == SDLK_ESCAPE) {
                                quit = true;
                            }
                        break;
                    }
                    if( e.type == SDL_KEYDOWN ) {
						switch ( e.key.keysym.sym ) {
							case SDLK_RIGHT:
									barra.stepX = 2;
								if(!inicio){
									ball.stepX = 2;
								}
								break;

							case SDLK_LEFT:
									barra.stepX = -2;
								if(!inicio){
									ball.stepX = -2;
								}
								break;
							case SDLK_SPACE:
								if(!inicio){
									ball.stepX = 2;
									ball.stepY = 2;
								}
								inicio = 1;
								break;

							default:
								break;
						}
					}
					if( e.type == SDL_KEYUP ) {
						switch ( e.key.keysym.sym ) {
							case SDLK_RIGHT:
								barra.stepX = 0;
								if(!inicio){
									ball.stepX = 0;
								}
								break;

							case SDLK_LEFT:
								barra.stepX = 0;
								if(!inicio){
									ball.stepX = 0;
								}

							default:
								break;
						}
					}
                }

                //Fill the surface white
                SDL_FillRect( gScreenSurface, NULL,
                              SDL_MapRGB( gScreenSurface->format,
                              0xFF, 0xFF, 0xFF ) );



                if( SDL_BlitSurface( gPNGFundo, NULL,
                                     gScreenSurface, NULL ) < 0 ) {
                    printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
                    quit = true;
                }

                moveNPC(&ball, blocos);

                srcRect.x = 0; srcRect.y = 0;
                srcRect.w = IMAGE_WIDTH;
                srcRect.h = IMAGE_HEIGHT;
                dstRect.x = ball.posX;
                dstRect.y = ball.posY;

                if( SDL_BlitSurface( ball.image, &srcRect,
                                     gScreenSurface, &dstRect ) < 0 ) {
                    printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
                    quit = true;
                }

                moveNPCBarra(&barra);

                srcRect.x = 0; srcRect.y = 0;
                srcRect.w = IMAGE_WIDTH_BARRA;
                srcRect.h = IMAGE_HEIGHT_BARRA;
                dstRect.x = barra.posX;
                dstRect.y = barra.posY;

                if( SDL_BlitSurface( barra.image, &srcRect,
                                     gScreenSurface, &dstRect ) < 0 ) {
                    printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
                    quit = true;
                }

                for(i = 0; i < 5; i++){
					for(j = 0; j < 16; j++){
						if(blocos[i][j]){
							srcRect.x = 0; srcRect.y = 0;
							srcRect.w = IMAGE_WIDTH_BLOCO;
							srcRect.h = IMAGE_HEIGHT_BLOCO;
							dstRect.x = IMAGE_WIDTH_BLOCO * j;
							dstRect.y = IMAGE_HEIGHT_BLOCO * i;

							if( SDL_BlitSurface( bloco.image, &srcRect,
										 gScreenSurface, &dstRect ) < 0 ) {
								printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
								quit = true;
							}
						}
					}
				}

                //Update the surface
                SDL_UpdateWindowSurface( gWindow );

                // Not so good solution, depends on your computer
                SDL_Delay(5);
            }
        }
    }

    //Free resources and closing SDL
    closing();

    return 0;
}
