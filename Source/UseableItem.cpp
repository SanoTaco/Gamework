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

void game_framework::UseableItem::OnMove()
{
	
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


bool game_framework::UseableItem::IsAlive()
{
	return isAlive;
}

void game_framework::UseableItem::SetIsAlive(bool flag)
{
	isAlive = flag;
}

