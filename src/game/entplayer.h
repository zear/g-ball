#ifndef __ENTITY_PLAYER__
#define __ENTITY_PLAYER__

#include "../baseent.h"

typedef struct {
	char *class; //This is the class of our entity.
	
	void (*logic)(void *this); //pointer to function void camelCase_logic(Entity *this)
	void (*draw)(void *this);  //pointer to function void camelCase_draw(Entity *this)
	
	int collisionType;
	
	float x,y; // >> 16 .. Our x/y positions in fp16,16.
	int forces;
	float sx, sy, ax, ay, f[32];
	
	float mass;
	float elasticity;
} Player;

void playerEnt_draw(Player *this);
void playerEnt_logic(Player *this);
Entity *playerEnt_super(char *args);
void playerEnt_doForces(Player *this, int index);

#endif //__ENTITY_PLAYER__ 

