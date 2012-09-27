#include "tile.h"
#include "baseent.h"
#include "SDLmain.h"

Entity createEntity(char *ent, void *args){
	
}

__ENT *ENT_CLASSES[256];

int __DECLARE_ENTITY(char *class, void *super){
	int i;
	while (ENT_CLASSES[i] == NULL)
		i++;
	
	ENT_CLASSES[i] = malloc(sizeof(__ENT));
	ENT_CLASSES[i]->class = class;
	ENT_CLASSES[i]->super = super;
}

//STUB ENTITY

void baseEnt_draw(Entity *this){
	SDL_Rect rct = {
		.h = 100,
		.w = 100,
		.x = this->x >> 16,
		.y = this->y >> 16,
	};
	SDL_FillRect(screen, &rct, 0xFFFFFFFF);
}

void baseEnt_logic(Entity *this){
	//DO NOTHING;
}

Entity *baseEnt_super(void *args) {
	Entity *this = malloc(sizeof(Entity));
	
	this->draw = baseEnt_draw;
	this->logic = baseEnt_logic;
	
	this->x = 100 << 16;
	this->y = 100 << 16;
	
	return this;
}

//TODO: Move the following to another file

void initEntities(){
	int i;
	for (i=0;i<256;i++) {
		ENT_CLASSES[i] = NULL;
	}
	__DECLARE_ENTITY("ent_base", baseEnt_super);
}