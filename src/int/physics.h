#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "intersect.h"
#include "../game/map.h"

enum Collision
{
	COLLISION_NONE,
	COLLISION_SOLID
};

enum Collision checkCollision(int x, int y);
void playerCollision(Player *this);
void applyForceTwoPoints(Player *this, float *fix);

void getAdjacent(int x, int y, int* a);

#endif //__PHYSICS_H__