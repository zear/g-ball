#include <stdlib.h>
#include <stdio.h>
#include "baseent.h"
#include "SDLmain.h"
#include "SDLgfx.h"
#include "input.h"
#include "baseent.h"

/*
 * Game-related entity includes.
 * Remove these in order to code your game differently.
 */

#include "game/entplayer.h"

/*~	~	~	~	~	~	~	*/

#include "font.h"

#define MAX_ENTITIES 512

__ENT *ENT_CLASSES[MAX_ENTITIES];
Entity *ents[MAX_ENTITIES];


/*
 * Stub entity.
 */
void baseEnt_draw(Entity *this);
void baseEnt_logic(Entity *this);
Entity *baseEnt_super(char *args);

int getLastEntityIndex() {
	int i;
	for (i=0;i < MAX_ENTITIES;i++) {
		if (!ents[i]) return i;
	}
	
	return -1;
}

void drawEntities(){
	int i;
	for (i=0;i < MAX_ENTITIES;i++) {
		if (!ents[i]) continue;
		
		ents[i]->draw(ents[i]);
	}	
}

void logicEntities(){
	int i;
	for (i=0;i < MAX_ENTITIES;i++) {
		if (!ents[i]) continue;
		
		ents[i]->logic(ents[i]);
	}	
}

void killEntities(){
	int i;
	for (i=0;i < MAX_ENTITIES;i++) {
		if (!ents[i]) continue;
		
		free(ents[i]);
	}
}

Entity *createEntity(char *class, char *args){
	Entity *ent = NULL;
	int i;
	for (i=0;i < MAX_ENTITIES;i++) {
		if (!ENT_CLASSES[i]) break;
		if (!strcmp(class, ENT_CLASSES[i]->class))
		{
			int index = getLastEntityIndex();
			if (index == -1) printf ("Could not create entity %s, maximum entity reached.\nAsk a developer to raise the MAX_ENTITIES cap.\n", class);
			else
			{
				ent = ENT_CLASSES[i]->super(args);
				ents[index] = ent;
			}
		}
	}	
	if (!ent)
	{
		printf("Could not create entity %s, class is non-existant.\n", class);
		return NULL;
	}
	else
	{
		printf("Created entity %s\n", class);
	}
	
	return ent;
}

int __DECLARE_ENTITY(char *class, void *super){
	int i = 0;
	for (i=0; i<MAX_ENTITIES; i++) {
		if (!ENT_CLASSES[i]) break;
	}
	
	if (ENT_CLASSES[i])
	{
		printf("Could not create entity class %s.\n", class);
		return 0;
	}
	
	ENT_CLASSES[i] = malloc(sizeof(__ENT));
	ENT_CLASSES[i]->class = class;
	ENT_CLASSES[i]->super = super;
	
	return 1;
}

void initEntities(){
	int i;
	for (i=0;i<MAX_ENTITIES;i++) {
		ENT_CLASSES[i] = NULL;
	}
	
	__DECLARE_ENTITY("ent_base", baseEnt_super);
	__DECLARE_ENTITY("ent_player", playerEnt_super);
}
//Example Entity

void baseEnt_draw(Entity *this){
	//this->x--; //Supress warnings.
	drawText("Test Entity", this->x >> 16, this->y >> 16, &FontLarge);
}

void baseEnt_logic(Entity *this){
	//this->x++; //Supress warnings.
}

Entity *baseEnt_super(char* args) {
	Entity *this = malloc(sizeof(Entity));
	
	this->draw = (void *)baseEnt_draw;
	this->logic = (void *)baseEnt_logic;
	
	sscanf(args, "%i %i", &this->x, &this->y);
	
	this->x = this->x << 16;
	this->y = this->y << 16;
	
	this->collisionType = 0;
	
	return this;
}
