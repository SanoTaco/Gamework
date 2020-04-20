#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Lava_Rock_1.h"


game_framework::Lava_Rock_1::Lava_Rock_1():X(0), Y(0), MW(64), MH(48)
{
	
	int map_init[10][10] = { {1,1,1,1,1,1,1,1,1,1} ,    //row 1
							 {1,0,0,0,0,0,1,1,1,1} ,	//row 2
							 {1,0,0,0,0,0,0,0,0,1} ,	//row 3
							 {1,0,0,0,0,0,0,0,0,1} ,	//row 4
						     {1,0,0,0,1,1,0,0,0,1} ,	//row 5
							 {1,0,0,0,1,1,0,0,0,1} ,	//row 6
							 {1,0,0,0,0,0,0,0,0,0} ,	//row 7
							 {1,0,0,0,0,0,0,0,0,0} ,	//row 8
							 {1,1,1,1,0,0,0,0,0,0} ,	//row 9
							 {1,1,1,1,1,1,1,1,1,1} };	//row 10

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
		lavaMap[i][j] = map_init[j][i];

		}
	}


}

void game_framework::Lava_Rock_1::OnMove()
{
}

void game_framework::Lava_Rock_1::LoadBitmap()
{
	lava.LoadBitmap(IDB_LAVA_1);
	rock.LoadBitmap(IDB_ROCK);
}

void game_framework::Lava_Rock_1::OnShow()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (lavaMap[i][j]) {
			case -1:
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

bool game_framework::Lava_Rock_1::IsEmpty(int x, int y)
{
	int gx = x / 64; // 轉換為格座標(整數除法)
	int gy = y / 48; // 轉換為格座標(整數除法)
	return lavaMap[gx][gy] == 0; // 假設 0 代表空的
}



int game_framework::Lava_Rock_1::ScreenX(int & x)
{
	return x;
}

int game_framework::Lava_Rock_1::ScreenY(int & y)
{
	return y;
}

bool game_framework::Lava_Rock_1::IsEnterTheDoor(CEraser * hero)
{
	return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
}

bool game_framework::Lava_Rock_1::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	//int x1 = 1855;				//门的左上角x坐标
	int x1 = 576;				//门的左上角x坐标
	//int y1 = 359;				//门的左上角y坐标
	int y1 = 288;				//门的左上角y坐标
	//int x2 = 1919;	// 门的右下角x坐标
	int x2 = 640;	// 门的右下角x坐标
	//int y2 = 433;	// 门的右下角y坐标
	int y2 = 432;	// 门的右下角y坐标
								//
								// 檢主角的矩形與參數矩形是否有交集
								//
	return (tx1 >= x1 && tx2 <= x2 && ty1 >= y1 && ty2 <= y2);//当主角图形的四个角，完全进入门框时，才算是进门了。
}
