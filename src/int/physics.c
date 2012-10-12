#include "../game/entplayer.h"
#include <math.h>
#include "intersect.h"
#include "physics.h"

void  applyForceTwoPoints(Player *this, float *fix){
	float p[2], n[2];
	float d;
	
	p[0] = fix[0] + fix[2]; p[0] /= 2;
	p[1] = fix[1] + fix[3]; p[1] /= 2;
	
	d = distanceTwoPoints(fix[0], fix[1], fix[2], fix[3]);

	n[0] = (fix[3] - fix[1]) / d;
	n[1] = (fix[2] - fix[0]) / d;	
	
	n[0] *= (this->x - p[0] < 0) ? 1.f: -1.f;
	n[1] *= (this->y - p[1] < 0) ? 1.f: -1.f;
	
	this->f[this->forces*2] = n[0] * (this->sx/this->mass);
	this->f[(this->forces*2)+1] = n[1] * (this->sy/this->mass);
	
	d = distanceTwoPoints(p[0], p[1], this->x, this->y);
	
	d = 6 - d;
	
	this->x += d * n[0];
	this->y += d * n[1];
	
	this->forces++;
}

void doForces(Player *this, int i, int j) {
	int c[4], nf;
	nf = 0;
	float f[8], f_[4];
	if (checkCollision(i,j) != COLLISION_SOLID)
		return;
	
	c[0] = circleLineIntersect((float)i*TILE_SIZE, (float)j*TILE_SIZE, (float)(i*TILE_SIZE) + TILE_SIZE, (float)j*TILE_SIZE, this->x, this->y, 6.f, &f[0]);
	c[1] = circleLineIntersect((float)(i*TILE_SIZE) + TILE_SIZE, (float)j*TILE_SIZE, (float)(i*TILE_SIZE) + TILE_SIZE, (float)(j*TILE_SIZE) + TILE_SIZE, this->x, this->y, 6.f, &f[2]);
	c[2] = circleLineIntersect((float)i*TILE_SIZE, (float)(j*TILE_SIZE) + TILE_SIZE, (float)(i*TILE_SIZE) + TILE_SIZE, (float)(j*TILE_SIZE) + TILE_SIZE, this->x, this->y, 6.f, &f[4]);
	c[3] = circleLineIntersect((float)i*TILE_SIZE, (float)j*TILE_SIZE, (float)i*TILE_SIZE, (float)(j*TILE_SIZE) + TILE_SIZE, this->x, this->y, 6.f, &f[6]);

	int n;
	for (n=0;n<4;n++)
	{
		if (c[n] == 2)
		{
			applyForceTwoPoints(this, &f[n*2]);
		}
		else if (c[n] == 1)
		{
			if (nf < 2)
			{
				f_[nf*2] = f[nf*2];
				f_[(nf*2)+1] = f[(nf*2)+1];
				nf++;
			}
		}
	}
	
	if (nf == 2)
	{
		applyForceTwoPoints(this, f_);
	}
}

void playerCollision(Player *this) {
	int i, j;
	i = this->x / TILE_SIZE;
	j = this->y / TILE_SIZE;
	
	doForces(this, i, j-1); // UP
	doForces(this, i+1, j-1); // UP RIGHT
	doForces(this, i-1, j-1); // UP LEFT
	doForces(this, i, j+1); // DOWN
	doForces(this, i+1, j+1); // DOWN RIGHT
	doForces(this, i-1, j+1); // DOWN LEFT 
	doForces(this, i+1, j); // RIGHT
	doForces(this, i-1, j); // LEFT 
}