#include "../game/entplayer.h"
#include <math.h>
#include "intersect.h"
#include "physics.h"

void  applyForceTwoPoints(Player *this, float *fix){
	float nx, ny, x_, y_, px, py;
	float d, f;
	x_ = fix[3] - fix[1]; //swap x for y
	y_ = fix[2] - fix[0];
	
	px = fix[0] + fix[2]; px /= 2;
	py = fix[1] + fix[3]; py /= 2;
	
	d = sqrt((x_ * x_) + (y_ * y_));
	nx -= x_ / d;
	ny = y_ / d;
	
	nx *= (this->x - px < 0) ? -1: 1;
	ny *= (this->y - py < 0) ? 1: -1;
	
	f = sqrt((this->sx*this->sx)+(this->sy*this->sy));
	
	if (this->elasticity < 1)
	{
		float df = (px - this->x) * (px - this->x);
	
		df += (py - this->y) * (py - this->y);
		df = 6-sqrt(df);
	
		f *= (df*df);
		f *= this->elasticity;
	}
	
	//lineRGBA(screen, (int)px, (int)py, (int)(px + (nx*10)), (int)(py + (ny*10)), 255, 5, 5, 255);
	//lineRGBA(screen, (int)fix[0], (int)fix[1], (int)fix[2], (int)fix[3], 255, 5, 5, 255);
	
	this->sx += f * nx;
	this->sy += f * ny;
}

void selectFloat(int i,int tx, int ty, float *f, float *buf){
	float x,y,d;
	x = f[0]-f[2];
	x *= x;
	y = f[1]-f[3];
	y *= y;
	
	d = sqrt(x+y);
	
	
}

void collisionAdjacents(Player *this, int i, int j)
{
	int i_, j_, a[4];
	i_ = i;
	j_ = j;
	
	int c;
	float fix[4];
	
	getAdjacent(i_, j_, &a);
	
	if (a[0]) {
		c = circleLineIntersect((float)i_*TILE_SIZE, (float)j_*TILE_SIZE, (float)(i_*TILE_SIZE) + TILE_SIZE, (float)j_*TILE_SIZE, this->x, this->y, 6.f, &fix);
		if (c == 2)
			applyForceTwoPoints(this, &fix);
	}
	
	if (a[1]) {
		c = circleLineIntersect((float)(i_*TILE_SIZE) + TILE_SIZE, (float)j_*TILE_SIZE, (float)(i_*TILE_SIZE) + TILE_SIZE, (float)(j_*TILE_SIZE) + TILE_SIZE, this->x, this->y, 6.f, &fix);
		if (c == 2)
			applyForceTwoPoints(this, &fix);
	}
	
	if (a[2]) {
		c = circleLineIntersect((float)i_*TILE_SIZE, (float)(j_*TILE_SIZE) + TILE_SIZE, (float)(i_*TILE_SIZE) + TILE_SIZE, (float)(j_*TILE_SIZE) + TILE_SIZE, this->x, this->y, 6.f, &fix);
		if (c == 2)
			applyForceTwoPoints(this, &fix);
	}
	
	if (a[3]) {
		c = circleLineIntersect((float)i_*TILE_SIZE, (float)j_*TILE_SIZE, (float)i_*TILE_SIZE, (float)(j_*TILE_SIZE) + TILE_SIZE, this->x, this->y, 6.f, &fix);
		if (c == 2)
			applyForceTwoPoints(this, &fix);
	}
}

void playerCollision(Player *this) {
	int i_, j_, a[4];
	i_ = this->x / TILE_SIZE;
	j_ = this->y / TILE_SIZE;
	
	collisionAdjacents(this, i_, j_);
// 	collisionAdjacents(this, i_, j_-1);
// 	collisionAdjacents(this, i_+1, j_);
// 	collisionAdjacents(this, i_, j_+1);
// 	collisionAdjacents(this, i_-1, j_);
}

void getAdjacent(int x, int y, int* a){
	a[0] = (checkCollision(x,y-1) == COLLISION_SOLID);
	a[1] = (checkCollision(x+1,y) == COLLISION_SOLID);
	a[2] = (checkCollision(x,y+1) == COLLISION_SOLID);
	a[3] = (checkCollision(x-1,y) == COLLISION_SOLID);
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