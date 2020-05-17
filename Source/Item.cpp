#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"
#include "Lava_Rock_1.h"

game_framework::Item::Item()
{
	usage = 0;
	effect = 1;
	x = y = 0;
	isalive = false;
}
game_framework::Item::~Item()
{
}
void game_framework::Item::LoadBitmap()
{
	point.LoadBitmap(IDB_POINT, RGB(0, 0, 0));
}

void game_framework::Item::OnShow(Map* map)
{
	
	
	if (GetIsAlive()) {
		point.SetTopLeft(x,y);
		point.ShowBitmap();
	}
	else {
		return;
	}
	
}

void game_framework::Item::OnMove()
{
}


// 0 represents get points
// 1 for potion;
// 2 for ability upgrade;
int game_framework::Item::Usage()
{
	return usage;
}

int game_framework::Item::Effect()
{
	return effect;
}

int game_framework::Item::GetX1()
{
	return x;
}

int game_framework::Item::GetY1()
{
	return y;
}

int game_framework::Item::GetX2()
{
	return x + point.Width();
}

int game_framework::Item::GetY2()
{
	return y + point.Height();
}

void game_framework::Item::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
	
}

bool game_framework::Item::GetIsAlive()
{
	return isalive;
}

void game_framework::Item::SetIsAlive(bool flag)
{
	isalive = flag;
}



void game_framework::Potion::OnShow(Map * map)
{
	if (!GetIsAlive())
	{
		return;
	}
	else {
		potion.SetTopLeft(x, y);
		potion.ShowBitmap();
	}
}

void game_framework::Potion::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}



void game_framework::Potion::LoadBitmap()
{
	potion.LoadBitmap(IDB_APPLE, RGB(255, 255, 255));
}

int game_framework::Potion::Usage()
{
	return usage;
}

int game_framework::Potion::Effect()
{
	return effect;
}

int game_framework::Potion::GetX1()
{
	return x;
}

int game_framework::Potion::GetY1()
{
	return y;
}

int game_framework::Potion::GetX2()
{
	return x + potion.Width();
}

int game_framework::Potion::GetY2()
{
	return y + potion.Height();
}

bool game_framework::Potion::GetIsAlive()
{
	return isalive;
}

void game_framework::Potion::SetIsAlive(bool flag)
{
	isalive = flag;
}



void game_framework::Star::OnShow(Map * map)
{
	if (!GetIsAlive()) {
		return;
	}
	else {
		star.SetTopLeft(x, y);
		star.ShowBitmap();
	}
}

void game_framework::Star::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}

void game_framework::Star::LoadBitmap()
{
	star.LoadBitmap(IDB_STAR, RGB(0, 0, 0));
}

int game_framework::Star::Usage()
{
	return usage;
}

int game_framework::Star::Effect()
{
	return effect;
}

int game_framework::Star::GetX1()
{
	return x;
}

int game_framework::Star::GetY1()
{
	return y;
}

int game_framework::Star::GetX2()
{
	return x + star.Width();
}

int game_framework::Star::GetY2()
{
	return y + star.Height();
}

bool game_framework::Star::GetIsAlive()
{
	return isalive;
}

void game_framework::Star::SetIsAlive(bool flag)
{
	isalive = flag;
}

void game_framework::AbstractItem::OnMove()
{
}

game_framework::AttackUp::AttackUp()
{
	usage = 3;
	effect = 1;
	x = y = 0;
}

void game_framework::AttackUp::OnShow(Map * map)
{
	if (!GetIsAlive()) {
		return;
	}
	else {
		atk.SetTopLeft(x, y);
		atk.ShowBitmap();
	}
}

void game_framework::AttackUp::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}

void game_framework::AttackUp::LoadBitmap()
{
	atk.LoadBitmap(IDB_ATK, RGB(255, 255, 255));
}

int game_framework::AttackUp::Usage()
{
	return usage;
}

int game_framework::AttackUp::Effect()
{
	return effect;
}

int game_framework::AttackUp::GetX1()
{
	return x;
}

int game_framework::AttackUp::GetY1()
{
	return y;
}

int game_framework::AttackUp::GetX2()
{
	return x + atk.Width();
}

int game_framework::AttackUp::GetY2()
{
	return y + atk.Height();
}

bool game_framework::AttackUp::GetIsAlive()
{
	return isalive;
}

void game_framework::AttackUp::SetIsAlive(bool flag)
{
	isalive = flag;
}

game_framework::Shield::Shield()
{
	usage = 4;
	effect = 1;
	x = y = 0;
}

void game_framework::Shield::OnShow(Map * map)
{
	if (!GetIsAlive()) {
		return;
	}
	else {
		shield.SetTopLeft(x, y);
		shield.ShowBitmap();
	}
}

void game_framework::Shield::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}

void game_framework::Shield::LoadBitmap()
{
	shield.LoadBitmap(IDB_SHIELD, RGB(255, 255, 255));
}

int game_framework::Shield::Usage()
{
	return usage;
}

int game_framework::Shield::Effect()
{
	return effect;
}

int game_framework::Shield::GetX1()
{
	return x;
}

int game_framework::Shield::GetY1()
{
	return y;
}

int game_framework::Shield::GetX2()
{
	return x + shield.Width();
}

int game_framework::Shield::GetY2()
{
	return y + shield.Height();
}

bool game_framework::Shield::GetIsAlive()
{
	return isalive;
}

void game_framework::Shield::SetIsAlive(bool flag)
{
	isalive = flag;
}
