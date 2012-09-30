#include "entplayer.h"

void playerEnt_draw(Player *this){
	//this->x--; //Supress warnings.
	//drawText("Test Entity", this->x >> 16, this->y >> 16, &FontLarge);
}

void playerEnt_logic(Player *this){
	//this->x++; //Supress warnings.
}

Entity *playerEnt_super(char *args) {
	Player *this = malloc(sizeof(Player));
	
	this->draw = playerEnt_draw;
	this->logic = playerEnt_logic;
	
	sscanf(args, "%i %i", &this->x, &this->y);
	
	this->x = this->x << 16;
	this->y = this->y << 16;
	
	this->collisionType = 1;
	
	return this;
}