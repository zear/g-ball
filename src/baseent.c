#include "baseent.h"
#include "SDLmain.h"
#include "input.h"
#include "baseent.h"

#define MAX_ENTITIES 256

__ENT *ENT_CLASSES[MAX_ENTITIES];


/*
 * Stub entity.
 */
void baseEnt_draw(Entity *this);
void baseEnt_logic(Entity *this);
Entity *baseEnt_super(char* args);

Entity *createEntity(char *class, char *args){
	Entity *ent = NULL;
	int i;
	for (i=0;i < MAX_ENTITIES;i++) {
		if (!ENT_CLASSES[i]) break;
		if (!strcmp(class, ENT_CLASSES[i]->class))
		{
			ent = ENT_CLASSES[i]->super(args);
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
}
//Example Entity

void baseEnt_draw(Entity *this){
	this->x--; //Supress warnings.
}

void baseEnt_logic(Entity *this){
	this->x++; //Supress warnings.
}

Entity *baseEnt_super(char* args) {
	Entity *this = malloc(sizeof(Entity));
	
	this->draw = baseEnt_draw;
	this->logic = baseEnt_logic;
	
	return this;
}