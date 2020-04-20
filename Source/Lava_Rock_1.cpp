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
	int gx = x / 64; // �D�Q�������(��������)
	int gy = y / 48; // �D�Q�������(��������)
	return lavaMap[gx][gy] == 0; // ���O 0 ����յ�
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
	//int x1 = 1855;				//�ŵ����Ͻ�x����
	int x1 = 576;				//�ŵ����Ͻ�x����
	//int y1 = 359;				//�ŵ����Ͻ�y����
	int y1 = 288;				//�ŵ����Ͻ�y����
	//int x2 = 1919;	// �ŵ����½�x����
	int x2 = 640;	// �ŵ����½�x����
	//int y2 = 433;	// �ŵ����½�y����
	int y2 = 432;	// �ŵ����½�y����
								//
								// �z���ǵľ����c���������Ƿ��н���
								//
	return (tx1 >= x1 && tx2 <= x2 && ty1 >= y1 && ty2 <= y2);//������ͼ�ε��ĸ��ǣ���ȫ�����ſ�ʱ�������ǽ����ˡ�
}
