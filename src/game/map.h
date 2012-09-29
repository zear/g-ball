#ifndef _MAP_H_
#define _MAP_H_

#include <SDL.h>

typedef struct MapStruct
{
	char *title;
	int w;
	int h;
	int **array;
	SDL_Surface *bitmap;
} Map;

extern Map CurMap;

#endif /* _MAP_H_ */
