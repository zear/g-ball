#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include <math.h>
#include "../game/map.h"

#define IMPRECISION 0.1

enum Collision
{
	COLLISION_NONE,
	COLLISION_SOLID
};

typedef struct {
	int x[2];
	int y[2];
	void *next;
} Vertices;

int circleLineIntersect(float x1, float y1, float x2, float y2, float cx, float cy, float r, float *f);
float distanceTwoPoints(float x1, float y1, float x2, float y2);

void getAdjacent(int i, int j, int* a);
enum Collision checkCollision(int x, int y);

#endif //__INTERSECT_H__