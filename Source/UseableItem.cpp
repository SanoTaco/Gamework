#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "UseableItem.h"
#include "Lava_Rock_1.h"

game_framework::UseableItem::UseableItem()
{
	x = 0;
	y = 0;
	isAlive = false;
	is_used = false;
	isFaceToRight = true;
	
}

void game_framework::UseableItem::LoadBitmap()
{
	useable.AddBitmap(IDB_BOOMERANG_1, RGB(0, 255, 0));
	useable.AddBitmap(IDB_BOOMERANG_2, RGB(0, 255, 0));
	useable.AddBitmap(IDB_BOOMERANG_3, RGB(0, 255, 0));

}

void game_framework::UseableItem::OnMove(Map* map, CEraser* hero)
{
	const int DISTANCE = 200;
	const int STEP_SIZE = 20;
	
	
	if (GetIsUsed()) {
		if (IsFaceToRight()) {
			if (x < (hero->GetX2() + DISTANCE)) {
				x += STEP_SIZE;
			}
			else {
				Retrive(map, hero);
			}
			
		}
		else
		{
			if (x < (hero->GetX1() - DISTANCE)) {
				x -= STEP_SIZE;
			}
			else {
				Retrive(map, hero);
			}

		}
	}
}

void game_framework::UseableItem::Retrive(Map * map, CEraser * hero)
{
	if (hero->GetX2() < x) {
		x -= 8;
	}
	if (hero->GetX1() > x) {
		x += 8;
	}
}

void game_framework::UseableItem::OnShow(Map * map)
{
	if (IsAlive()) {
		useable.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		useable.OnShow();
	}
}

int game_framework::UseableItem::Usage()
{
	return usage;
}

int game_framework::UseableItem::Effect()
{
	return effect;
}

int game_framework::UseableItem::GetX1()
{
	return x;
}

int game_framework::UseableItem::GetY1()
{
	return y;
}

int game_framework::UseableItem::GetX2()
{
	return x +48;
}

int game_framework::UseableItem::GetY2()
{
	return y + 46;
}

void game_framework::UseableItem::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}

bool game_framework::UseableItem::GetIsUsed()
{
	return is_used;
}

void game_framework::UseableItem::SetIsUsed(bool flag)
{
	is_used = flag;
}

bool game_framework::UseableItem::IsFaceToRight()
{
	return isFaceToRight;
}

void game_framework::UseableItem::SetFaceToRight(bool flag)
{
	isFaceToRight = flag;
}



bool game_framework::UseableItem::IsAlive()
{
	return isAlive;
}

void game_framework::UseableItem::SetIsAlive(bool flag)
{
	isAlive = flag;
}

void game_framework::UseableItem::OnKeyDown(UINT nChar, CEraser * hero, Map * map)
{
	const int KEY_X = 0x58;

	if (nChar == KEY_X)
	{
		if (hero->GetIsFaceToRight() && nChar == KEY_X)      //若人物面向右边
		{
			SetFaceToRight(hero->GetIsFaceToRight());//则设置子弹方向为右边
			int i = hero->GetX2();
			int j = hero->GetY1();
			SetIsUsed(true);
			SetIsAlive(true);
			SetXY(i + 1, j );

		}
		if (nChar == KEY_X && hero->GetIsFaceToRight() == false)                           //若人物面向左边
		{
			SetFaceToRight(hero->GetIsFaceToRight());//则设置子弹方向为左边
			int i = hero->GetX1();
			int j = hero->GetY1();
			SetIsUsed(true);
			SetIsAlive(true);
			SetXY(i - useable.Width() , j );
		}
		
	}
}
