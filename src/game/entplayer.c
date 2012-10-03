#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "entplayer.h"
#include "../font.h"
#include "../input.h"
#include "../SDLmain.h"
#include "../timer.h"
#include "../int/intersect.h"
#include "../int/physics.h"

typedef struct {
	int x[2];
	int y[2];
	void *next;
} vert;

void playerEnt_draw(Player *this){
	//this->x--; //Supress warnings.

	//drawText("@", (int)this->x, (int)this->y, &FontLarge);
	ellipseRGBA(screen,
			(int)this->x, (int)this->y,
			5, 5,
			255, 255, 255, 200);
	
	int i_, j_, a[4];
	i_ = this->x / TILE_SIZE;
	j_ = this->y / TILE_SIZE;
	getAdjacent(i_, j_, &a);

	if (a[0])
		lineRGBA(screen, i_*TILE_SIZE, j_*TILE_SIZE, (i_*TILE_SIZE) + TILE_SIZE, j_*TILE_SIZE, 255, 255, 255, 255);
	
	if (a[1])
		lineRGBA(screen, (i_*TILE_SIZE) + TILE_SIZE, j_*TILE_SIZE, (i_*TILE_SIZE) + TILE_SIZE, (j_*TILE_SIZE) + TILE_SIZE, 255, 255, 255, 255);
	
	if (a[2])
		lineRGBA(screen, i_*TILE_SIZE, (j_*TILE_SIZE) + TILE_SIZE, (i_*TILE_SIZE) + TILE_SIZE, (j_*TILE_SIZE) + TILE_SIZE, 255, 255, 255, 255);
	
	if (a[3])
		lineRGBA(screen, i_*TILE_SIZE, j_*TILE_SIZE, i_*TILE_SIZE, (j_*TILE_SIZE) + TILE_SIZE, 255, 255, 255, 255);
}

void playerEnt_logic(Player *this){
	//this->x++; //Supress warnings.
	/*this->x += SDL_JoystickGetAxis(joy, 0);
	this->y += SDL_JoystickGetAxis(joy, 1);*/
	int fx, fy;
	fx = (keystate[SDLK_LEFT]) ? -1 : (keystate[SDLK_RIGHT] ? 1 : 0);
	fy = (keystate[SDLK_UP]) ? -1 : (keystate[SDLK_DOWN] ? 1 : 0);

	this->ax = (fx*8) / this->mass;
	this->ay = (fy*8) / this->mass;
	
	this->sx += this->ax * frameScale;
	this->sy += this->ay * frameScale;
	
	this->sx -= (this->sx * 0.3) * frameScale;
	this->sy -= (this->sy * 0.3) * frameScale;
	
	/*float fix[4];
	
	int col = circleLineIntersect(0.f, 100.f, 100.f, 100.f, this->x, this->y, 6.f, &fix);
	
	if (col == 2) {
		applyForceTwoPoints(this, &fix);
	}*/
	
	playerCollision(this);
	
	this->x  += this->sx;
	this->y  += this->sy;

}

Entity *playerEnt_super(char *args) {
	Player *this = malloc(sizeof(Player));
	
	this->draw = (void*)playerEnt_draw;
	this->logic = (void*)playerEnt_logic;
	
	sscanf(args, "%f %f", &this->x, &this->y);
	
	this->x += 6;
	this->y += 6;
	
	this->ax = 0.f;
	this->ay = 0.f;
	
	this->sx = 0.f;
	this->sy = 0.f;
	
	this->elasticity = 1;
	
	this->mass = 5.f; //5kg mass
	
	this->collisionType = 1;
	
	return (Entity *)this;
}
