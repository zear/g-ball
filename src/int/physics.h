#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "intersect.h"

void playerCollision(Player *this);
void applyForceTwoPoints(Player *this, float *fix);

#endif //__PHYSICS_H__