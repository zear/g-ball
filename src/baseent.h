#ifndef __BASE_ENT__
#define __BASE_ENT__

#include <stdarg.h>

typedef struct {
	char *class; //This is the class of our entity.
	
	void (*logic)(void *this); //pointer to function void camelCase_logic(Entity *this)
	void (*draw)(void *this);  //pointer to function void camelCase_draw(Entity *this)
	
	int collisionType;
	
	float x,y; // >> 16 .. Our x/y positions in fp16,16.
} Entity;

typedef struct {
	char *class;
	
	Entity *(*super)(char *args);
} __ENT;

int __DECLARE_ENTITY(char *class, void *super);
void initEntities();

Entity *createEntity(char *class, char *args);
void killEntities();
void drawEntities();
void logicEntities();

extern Entity *ents[512];

#endif //__BASE_ENT__
