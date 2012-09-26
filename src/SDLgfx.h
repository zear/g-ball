#ifndef _SDLGFX_H_
#define _SDLGFX_H_

#include <SDL.h>

SDL_Surface *loadImage(char *fileName);
void clipImage(SDL_Rect *source, int tileWidth, int tileHeight, int rows, int numOfTiles);
void applySurface(SDL_Surface *source, SDL_Surface *destination, int x, int y, SDL_Rect *clip);
int updateScreen();

#endif /* _SDLGFX_H_ */
