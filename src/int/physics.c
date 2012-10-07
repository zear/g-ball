#include "../game/entplayer.h"
#include <math.h>
#include "intersect.h"
#include "physics.h"

void  applyForceTwoPoints(Player *this, float *fix){
	float p[2], n[2];
	float d, f;
	
	p[0] = fix[0] + fix[2]; p[0] /= 2;
	p[1] = fix[1] + fix[3]; p[1] /= 2;
	
	d = distanceTwoPoints(fix[0], fix[1], fix[2], fix[3]);
	
	n[0] = (fix[3] - fix[1]) / d;
	n[1] = (fix[2] - fix[0]) / d;
	
	n[0] *= (this->x - p[0] < 0) ? 1: -1;
	n[1] *= (this->y - p[1] < 0) ? 1: -1;
	
	f = distanceTwoPoints(0,0, this->sx, this->sy);
	
	if (this->elasticity < 1)
	{
		float df = 6-distanceTwoPoints(p[0], p[1], this->x, this->y);
		
		f *= (df*df);
		f *= this->elasticity;
	}
	
	this->sx = f * n[0];
	this->sy = f * n[1];
}

void playerCollision(Player *this) {
	int i, j;
	i = this->x / TILE_SIZE;
	j = this->y / TILE_SIZE;
	
}