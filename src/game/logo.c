#include "logo.h"
#include "../SDLmain.h"
#include "../SDLgfx.h"

void logoLogic()
{
	int i;

	int posX = 40;

	if(Logo.bitmap == NULL)
	{
		Logo.bitmap = loadImage("./data/gfx/logo.bmp");
		clipImage(Logo.clip, 67, 67, 6, 6);

		Logo.tile[0].Pos.x = posX;
		Logo.tile[0].Pos.y = -70;
		Logo.tile[0].v = 0;
		Logo.tile[0].bump = 0;
		Logo.tile[1].Pos.x = posX + 50;
		Logo.tile[1].Pos.y = -80;
		Logo.tile[1].v = 0;
		Logo.tile[1].bump = 0;
		Logo.tile[2].Pos.x = posX + 50 + 40;
		Logo.tile[2].Pos.y = -90;
		Logo.tile[2].v = 0;
		Logo.tile[2].bump = 0;
		Logo.tile[3].Pos.x = posX + 50 + 40 + 40;
		Logo.tile[3].Pos.y = -100;
		Logo.tile[3].v = 0;
		Logo.tile[3].bump = 0;
		Logo.tile[4].Pos.x = posX + 50 + 40 + 40 + 20;
		Logo.tile[4].Pos.y = -110;
		Logo.tile[4].v = 0;
		Logo.tile[4].bump = 0;
		Logo.tile[5].Pos.x = posX + 50 + 40 + 40 + 20 + 10;
		Logo.tile[5].Pos.y = -120;
		Logo.tile[5].v = 0;
		Logo.tile[5].bump = 0;
	}

	for(i = 0; i < 6; i++)
	{
		Logo.tile[i].v++;

		if(Logo.tile[i].Pos.y > 25 && Logo.tile[i].v > 0)
		{
			if(Logo.tile[i].bump < 5)
			{
				Logo.tile[i].bump++;
			}

			switch(Logo.tile[i].bump)
			{
				case 1:
					Logo.tile[i].v-= 40;
					break;
				case 2:
					Logo.tile[i].v-= 25;
					break;
				case 3:
					Logo.tile[i].v-= 15;
					break;
				case 4:
					Logo.tile[i].v-= 10;
					break;
				case 5:
					Logo.tile[i].v = 0;
					break;

				default:
					break;
			}

		}

		if(Logo.tile[i].v > 1)
		{
			Logo.tile[i].v = 1;
		}

		if(Logo.tile[i].v > 0)
		{
			Logo.tile[i].Pos.y++;
		}
		if(Logo.tile[i].v < 0)
		{
			Logo.tile[i].Pos.y--;
		}

		//Logo.tile[i].Pos.y+= Logo.tile[i].v;
	}
}

void logoDraw()
{
	int i;

	for(i = 5; i >= 0; i--)
	{
		applySurface(Logo.bitmap, screen, Logo.tile[i].Pos.x, Logo.tile[i].Pos.y, &Logo.clip[i]);
	}
}
