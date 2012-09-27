#include "SDLgfx.h"
#include "font.h"
#include "SDLmain.h"
#include <SDL.h>

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

SDL_Surface *loadImage(char *fileName)
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
