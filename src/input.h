#ifndef _INPUT_H_
#define _INPUT_H_

struct JoystateStruct
{
	int x;
	int y;
};

extern _Bool keystate[2048];
extern struct JoystateStruct Joystate;

void input();

#endif /* _INPUT_H_ */
