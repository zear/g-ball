#include "intersect.h"

float distanceTwoPoints(float x1, float y1, float x2, float y2)
{	
	return sqrt(((x2-x1) * (x2-x1)) + ((y2-y1) * (y2-y1)));
}

int inLine(float *p, float x1, float y1, float x2, float y2)
{
	float d[3];
	d[0] = distanceTwoPoints(x1, y1, x2, y2);
	d[1] = distanceTwoPoints(p[0], p[1], x1, y1);
	d[2] = distanceTwoPoints(p[0], p[1], x2, y2);
	
	return ((d[1]+d[2])-d[0] <= IMPRECISION);
}

int circleLineIntersect(float x1, float y1, float x2, float y2, float cx, float cy, float r, float *f) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	
	float a = dx * dx + dy * dy;
	float b = 2 * (dx * (x1 - cx) + dy * (y1 - cy));
	float c = cx * cx + cy * cy;
	
	c += x1 * x1 + y1 * y1;
	c -= 2 * (cx * x1 + cy * y1);
	c -= r * r;
	
	float delta = b * b - 4 * a * c;
	
	if (delta < 1) {  // Not intersecting or just tangent
    return 0;
	}
	else {
		
		float mu = (-b + sqrt( delta )) / (2*a);
		f[0] = x1 + mu*(dx);
		f[1] = y1 + mu*(dy);
		mu = (-b - sqrt( delta )) / (2*a);
		f[2] = x1 + mu*(dx);
		f[3] = y1 + mu*(dy);
		
		if(!inLine(&f[0], x1, y1, x2, y2))
		{
			if (inLine(&f[2], x1, y1, x2, y2))
			{
				f[0] = f[2];
				f[1] = f[3];
				return 1;
			}
			else
			{
				return 0;
			}
			
		}
		
		if(!inLine(&f[2], x1, y1, x2, y2))
		{
			return 1;
		}
		
		return (delta == 0) ? 1 : 2;
	}
}

/*
 * Clockwise adjacent collision detector.
 * Takes as argument:
 * 
 * Tile X, Y in ABSOLUTE TILE VALUE (12 in y counts as 1 j)
 */

void getAdjacents(int i, int j, int* a)
{
	a[0] = (checkCollision(i,j-1) == COLLISION_SOLID);
	a[1] = (checkCollision(i+1,j) == COLLISION_SOLID);
	a[2] = (checkCollision(i,j+1) == COLLISION_SOLID);
	a[3] = (checkCollision(i-1,j) == COLLISION_SOLID);
}

enum Collision checkCollision(int x, int y)
{
	int posX = x;
	int posY = y;
	
	if(posX < 0 || posX >= CurMap.w)
	{
		return COLLISION_SOLID;
	}
	if(posY < 0 || posY >= CurMap.h)
	{
		return COLLISION_SOLID;
	}
	
	switch(CurMap.array[posX][posY])
	{
		case 0: // gap
		case 1: // floor
			return COLLISION_NONE;
			break;
		case 2: // walls
			return COLLISION_SOLID;
			break;
			
		default:
			return COLLISION_NONE;
			break;
	}
}