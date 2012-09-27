#ifndef __BASE_ENT__
#define __BASE_ENT__

typedef struct {
	char *class; //This is the class of our entity.
	
	void (*logic)(void *this); //pointer to function void camelCase_logic(Entity *this)
	void (*draw)(void *this);  //pointer to function void camelCase_draw(Entity *this)
	
	int x,y; // >> 16 .. Our x/y positions in fp16,16.
} Entity;

typedef struct {
	char *class;
	
	Entity *(*super)(char *args);
} __ENT;

int __DECLARE_ENTITY(char *class, void *super);
Entity *createEntity(char *class, char *args);
void initEntities();

#endif //__BASE_ENT__
