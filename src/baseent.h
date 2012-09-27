#ifndef __BASE_ENT__
#define __BASE_ENT__

#include "tile.h"

typedef struct {
	char *class;
	
	void (*logic)(void *this);
	void (*draw)(void *this);
	
	int x,y; // >> 16
	
	Tile tile;
} Entity;

Entity createEntity(char *ent);

#endif //__BASE_ENT__
