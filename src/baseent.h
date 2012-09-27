#ifndef __BASE_ENT__
#define __BASE_ENT__

#include "sprite.h"

typedef struct {
	char *class; //This is the class of our entity.
	
	void (*logic)(void *this); //pointer to function void camelCase_logic(Entity *this)
	void (*draw)(void *this);  //pointer to function void camelCase_draw(Entity *this)
	
	int x,y; // >> 16 .. Our x/y positions in fp16,16.
	
	Sprite sprite;
} Entity;

typedef struct {
	char *class;
	
	void (*super)(Entity *this, void *args);
} __ENT;

int __DECLARE_ENTITY(char *class, void *super);
Entity createEntity(char *class, void *args);

#endif //__BASE_ENT__
