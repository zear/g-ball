#include <stdlib.h>
#include <stdio.h>
#include "entplayer.h"
#include "../font.h"
#include "../input.h"
#include "../SDLmain.h"

void playerEnt_draw(Player *this){
	//this->x--; //Supress warnings.
	drawText("@", this->x >> 16, this->y >> 16, &FontLarge);
}

void playerEnt_logic(Player *this){
	//this->x++; //Supress warnings.
	this->x += SDL_JoystickGetAxis(joy, 0);
	this->y += SDL_JoystickGetAxis(joy, 1);
}

Entity *playerEnt_super(char *args) {
	Player *this = malloc(sizeof(Player));
	
	this->draw = (void*)playerEnt_draw;
	this->logic = (void*)playerEnt_logic;
	
	sscanf(args, "%i %i", &this->x, &this->y);
	
	this->x = this->x << 16;
	this->y = this->y << 16;
	
	this->collisionType = 1;
	
	return (Entity *)this;
}
