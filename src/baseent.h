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

typedef struct {
	char *class;
	
	void (*super)(Entity *this, void *args);
} __ENT;

int __DECLARE_ENTITY(char *class, void *super);
Entity createEntity(char *class, void *args);

#endif //__BASE_ENT__
