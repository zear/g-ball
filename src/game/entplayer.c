#include "entplayer.h"

void playerEnt_draw(Player *this){
	//this->x--; //Supress warnings.
	//drawText("Test Entity", this->x >> 16, this->y >> 16, &FontLarge);
}

void playerEnt_logic(Player *this){
	//this->x++; //Supress warnings.
}

Entity *playerEnt_super(va_list args) {
	Player *this = malloc(sizeof(Player));
	
	this->draw = playerEnt_draw;
	this->logic = playerEnt_logic;
	
	this->x = va_arg(args, int) << 16;
	this->y = va_arg(args, int) << 16;
	
	return this;
}