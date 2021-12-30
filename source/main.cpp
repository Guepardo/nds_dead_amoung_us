/*
-------------------------------------------------

	NightFox's Lib Template

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por NightFox
	http://www.nightfoxandco.com
	Inicio 10 de Octubre del 2009

	(c)2009 - 2011 NightFox & Co.

-------------------------------------------------
*/

/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

#include <stdio.h>
#include <nds.h>
#include <nf_lib.h>
#include <stdlib.h>
#include <time.h>

#include "enemy.cpp"

#define TOP_SCREEM 0
#define BOTTOM_SCREEM 1

#define SCREEM_MODE 0

/*
-------------------------------------------------
	Main() - Bloque general del programa
-------------------------------------------------
*/

void initConsole()
{
	consoleDemoInit();
	consoleClear();

	NF_Set2D(TOP_SCREEM, 0);
	NF_SetRootFolder("NITROFS");

	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(TOP_SCREEM);
	NF_InitTiledBgSys(BOTTOM_SCREEM);

	NF_InitSpriteBuffers();
	NF_InitSpriteSys(TOP_SCREEM);
	NF_InitSpriteSys(BOTTOM_SCREEM);

	srand(time(NULL));
}

int main(int argc, char **argv)
{

	initConsole();

	NF_LoadTiledBg("backgrounds/bg", "bg", 256, 256);
	NF_CreateTiledBg(TOP_SCREEM, 3, "bg");
	NF_LoadTiledBg("backgrounds/bg", "bg", 256, 256);
	NF_CreateTiledBg(BOTTOM_SCREEM, 3, "bg");

	NF_LoadSpriteGfx("sprites/tile", 0, 8, 8);
	NF_LoadSpritePal("palettes/segment", 0);
	NF_LoadSpritePal("palettes/apple", 1);
	NF_LoadSpritePal("palettes/segment_dropshadow", 2);
	NF_LoadSpritePal("palettes/apple_dropshadow", 3);

	NF_VramSpriteGfx(TOP_SCREEM, 0, 0, false);
	NF_VramSpritePal(TOP_SCREEM, 0, 0);
	NF_VramSpritePal(TOP_SCREEM, 1, 1);
	NF_VramSpritePal(TOP_SCREEM, 2, 2);
	NF_VramSpritePal(TOP_SCREEM, 3, 3);

	NF_VramSpriteGfx(BOTTOM_SCREEM, 0, 0, false);
	NF_VramSpritePal(BOTTOM_SCREEM, 0, 0);
	NF_VramSpritePal(BOTTOM_SCREEM, 1, 1);
	NF_VramSpritePal(BOTTOM_SCREEM, 2, 2);
	NF_VramSpritePal(BOTTOM_SCREEM, 3, 3);

	NF_InitTextSys(TOP_SCREEM);

	NF_LoadTextFont("fonts/font", "default", 256, 256, 0);
	NF_CreateTextLayer(TOP_SCREEM, 0, 0, "default");

	NF_WriteText(TOP_SCREEM, 0, 2, 2, "SCORE: 0");
	NF_UpdateTextLayers();

	int x = 50;
	int y = 50;

	NF_CreateSprite(TOP_SCREEM, 1, 0, 1, x, y);
	NF_CreateSprite(BOTTOM_SCREEM, 1, 0, 1, x, y);

	const short ENEMIES = 40;
	const short SPRITE_OFFSET = 2;

	Enemy enemies[ENEMIES];

	for (int i = 0; i < ENEMIES; i++)
	{
		short screen = (i < (ENEMIES / 2)) ? BOTTOM_SCREEM : TOP_SCREEM;

		enemies[i].init(i);
		enemies[i].setSpriteId(SPRITE_OFFSET + i);
		enemies[i].setScreenId(screen);

		NF_CreateSprite(screen, enemies[i].spriteId, 0, 0, enemies[i].x, enemies[i].y);
	}

	while (1)
	{
		scanKeys();

		for (int i = 0; i < ENEMIES; i++)
		{
			enemies[i].move();

			NF_MoveSprite(enemies[i].screenId, enemies[i].spriteId, enemies[i].x, enemies[i].y);
		}

		if (keysHeld() & KEY_UP)
		{
			y--;

			if (y <= 0)
			{
				y = 192;
			}
		}

		if (keysHeld() & KEY_DOWN)
		{
			y++;

			if (y >= 192)
			{
				y = 0;
			}
		}

		if (keysHeld() & KEY_LEFT)
		{
			x--;

			if (x <= 0)
			{
				x = 256;
			}
		}

		if (keysHeld() & KEY_RIGHT)
		{
			x++;

			if (x >= 256)
			{
				x = 0;
			}
		}

		iprintf("x %d, y : %d", x, y);

		NF_MoveSprite(TOP_SCREEM, 1, x, y);
		NF_MoveSprite(BOTTOM_SCREEM, 1, x, y);

		NF_SpriteOamSet(TOP_SCREEM);
		NF_SpriteOamSet(BOTTOM_SCREEM);

		swiWaitForVBlank();

		consoleClear();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}

	return 0;
}
