#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"


namespace game_framework {









	Hero::Hero()
	{
		Initialize();
	}

	int Hero::GetX1()
	{
		return x;
	}

	int Hero::GetY1()
	{
		return y;
	}

	int Hero::GetX2()
	{
		return x + character.Width();
	}

	int Hero::GetY2()
	{
		return y + character.Height();
	}

	void Hero::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 380;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

	}

	void Hero::LoadBitmap()
	{
		character.AddBitmap(IDB_HERO,RGB(0,0,0));
	}

	void Hero::OnMove(Lava_Rock_1 *m)
	{
		const int STEP_SIZE = 2;
		character.OnMove();
		if (isMovingLeft) {
			if (m->IsEmpty(x-1,y) == true) {
				x -= STEP_SIZE;
			}
			else {
				x += 0;
			}
			
		}
			
		if (isMovingRight) {
			if (m->IsEmpty((x+character.Width()+1),y) == true) {
				x += STEP_SIZE;
			}
		}
			
		if (isMovingUp) {
			if (m->IsEmpty(x,y-1)== true){
				y -= STEP_SIZE;
			}
		}
			
		if (isMovingDown) {
			if (m->IsEmpty(x,y+1+character.Height()) == true) {
				y += STEP_SIZE;
			}
		}
			
	}

	void Hero::OnShow()
	{
		character.SetTopLeft(x, y);
		character.OnShow();
	}

	void Hero::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Hero::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Hero::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Hero::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Hero::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

}