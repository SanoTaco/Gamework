#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Lava_Rock_2.h"

game_framework::Lava_Rock_2::Lava_Rock_2() :X(0), Y(0), MW(64), MH(48)
{
	int map_init[10][10] = {		 {1,1,1,1,1,1,1,1,1,1} ,    //row 1
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 2
									 {1,0,1,1,0,0,1,1,0,1} ,	//row 3
									 {1,0,1,0,0,0,0,1,0,1} ,	//row 4
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 5
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 6
									 {0,0,1,0,0,0,0,1,0,1} ,	//row 7
									 {0,0,1,1,0,0,1,1,0,1} ,	//row 8
									 {1,1,1,1,1,1,1,1,1,1} ,	//row 9
									 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} };	//row 10

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			lavaMap[i][j] = map_init[j][i];

		}
	}
}


void game_framework::Lava_Rock_2::OnShow()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (lavaMap[i][j]) {
			case -1:
				blackground.SetTopLeft(X + MW * i, Y + MH * j);
				blackground.ShowBitmap();
				break;
			case 0:
				rock.SetTopLeft(X + MW * i, Y + MH * j);
				rock.ShowBitmap();
				break;
			case 1:
				lava.SetTopLeft(X + MW * i, Y + MH * j);
				lava.ShowBitmap();
				break;
			default:
				ASSERT(-1);



			}
		}
	}
}

void game_framework::Lava_Rock_2::LoadBitmap()
{
	rock.LoadBitmap(IDB_ROCK);
	lava.LoadBitmap(IDB_LAVA_1);
	blackground.LoadBitmap(IDB_BLACKGROUND);
}

bool game_framework::Lava_Rock_2::IsEmpty(int x, int y)
{
	int gx = x / 64; // 轉換為格座標(整數除法)
	int gy = y / 48; // 轉換為格座標(整數除法)
	return lavaMap[gx][gy] == 0; // 假設 0 代表空的
}

int game_framework::Lava_Rock_2::ScreenX(int & x)
{
	return x;
}

int game_framework::Lava_Rock_2::ScreenY(int & y)
{
	return y;
}
