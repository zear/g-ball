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

void drawAdjacents(Player *this)
{
	Vertices firstEdge;
	int i, j, adj[4], adjs[4][4];
	i = this->x / TILE_SIZE;
	j = this->y / TILE_SIZE;
	getAdjacents(i,j, adj);
}

void playerEnt_draw(Player *this){
	//this->x--; //Supress warnings.

	//drawText("@", (int)this->x, (int)this->y, &FontLarge);
	ellipseRGBA(screen,
			(int)this->x, (int)this->y,
			5, 5,
			255, 255, 255, 200);
	
	drawAdjacents(this);
}

void playerEnt_logic(Player *this){
	//this->x++; //Supress warnings.
	/*this->x += SDL_JoystickGetAxis(joy, 0);
	this->y += SDL_JoystickGetAxis(joy, 1);*/
	this->forces = 1;
	int fx, fy;
	fx = (keystate[SDLK_LEFT]) ? -5 : (keystate[SDLK_RIGHT] ? 5 : 0);
	fy = (keystate[SDLK_UP]) ? -5 : (keystate[SDLK_DOWN] ? 5 : 0);
	
	this->f[0] = fx - (this->sx / this->mass) * 0.1;
	this->f[1] = fy - (this->sy / this->mass) * 0.1;
	
	int i;
	for (i=0;i<this->forces;i++){
		this->ax += this->f[i*2];
		this->ay += this->f[(i*2)+1];
	}
	
	playerCollision(this);
	
	this->ax /= this->mass;
	this->ay /= this->mass;
	
	this->x += (this->sx + this->ax * frameScale) * frameScale;
	this->y += (this->sy + this->ay * frameScale) * frameScale;
	
	this->sx += this->ax;
	this->sy += this->ay;
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
