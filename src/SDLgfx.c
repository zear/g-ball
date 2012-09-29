#include "SDLgfx.h"
#include <SDL.h>
#include <stdlib.h>
#include "font.h"
#include "SDLmain.h"
#include "game/map.h"

typedef struct {
	SDL_Surface *surface;
	char *fileName;
	
	void *next;
} __SURFACE;

__SURFACE *firstSurface;

SDL_Surface *__loadImage(char *fileName)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;
	
	if(fileName == NULL)
	{
		fprintf(stderr, "ERROR (loadImage): File name not specified!\n");
		return NULL;
	}
	
	loadedImage = SDL_LoadBMP(fileName);
	
	if(loadedImage == NULL)
	{
		fprintf(stderr, "ERROR (loadImage): Failed to load image file: %s\n", fileName);
		return NULL;
	}
	else
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	
	if(optimizedImage == NULL)
	{
		fprintf(stderr, "ERROR (loadImage): Failed to optimize image file: %s\n", fileName);
		return NULL;
	}
	else
	{
		// set transparency to magenta
		Uint32 colorKey = SDL_MapRGB(optimizedImage->format, 255, 0, 255);
		SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorKey);
	}
	
	return optimizedImage;
}

__SURFACE *allocSurface(char *fileName) {
	__SURFACE *surf = malloc(sizeof(__SURFACE));
	
	surf->surface = __loadImage(fileName);
	surf->next = NULL;
	surf->fileName = fileName;
	
	return surf;
}

void drawText(char *text, int x, int y, Font *Font)
{
	int c; // current character
	int posX = x;
	int posY = y;

	for(c = 0; text[c] != '\0'; c++)
	{
		if(text[c] == '\n')
		{
			y++;
			posY += Font->height;
		}
		else
		{
			applySurface(Font->bitmap, screen, posX, posY, &Font->clip[(int)text[c]]);
			posX += Font->width;
		}
	}
}

void drawBackground(int r, int g, int b)
{
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, r, g, b));
}

void drawMap()
{
	int i;
	int j;
	int x;
	int y;

	// this should depend on camera implementation in the future
	for(j = 0, y = 0; j < CurMap.h; j++, y+=TILE_SIZE)
	{
		for(i = 0, x = 0; i < CurMap.w; i++, x+=TILE_SIZE)
		{
			applySurface(CurMap.bitmap, screen, x, y, &CurMap.clip[CurMap.array[i][j]]);
		}
	}
}

SDL_Surface *loadImage(char *fileName) {
	__SURFACE *surf = firstSurface;
	__SURFACE *prev;
	if (!surf) {
		firstSurface = allocSurface(fileName);
		
		return firstSurface->surface;
	}
	
	while(surf) {
		if (!strcmp(surf->fileName, fileName))
		{
			if (!surf->surface)
			printf("File registered, but no surface loaded (missing file %s?).\n", fileName);
		
			return surf->surface;
		}
		
		if (surf->next)
		{
			prev = surf;
			surf = prev->next;
		}
		else
			break;	
	}

	__SURFACE *new = allocSurface(fileName);
	surf->next = new;
		
	return new->surface;
		
}

void clipImage(SDL_Rect *source, int tileWidth, int tileHeight, int rows, int numOfTiles)
{
	int i = 0; // current tile pos y
	int j = 0; // current tile pos x
	int k = 0; // current tile number
	int l = 0; // current tile row

	for(i = 0; k < numOfTiles; i+= tileHeight)
	{
		for(j = 0; l < rows; j+= tileWidth)
		{
			source[k].x = j;
			source[k].y = i;
			source[k].w = tileWidth;
			source[k].h = tileHeight;
			++k;
			++l;
		}

		l = 0;
	}
}

void applySurface(SDL_Surface *source, SDL_Surface *destination, int x, int y, SDL_Rect *clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

int updateScreen()
{
	if(SDL_Flip(screen) == -1)
	{
		fprintf(stderr, "ERROR (updateScreen): Failed to flip screen surface!\n");
		return 1;
	}

	return 0;
}
