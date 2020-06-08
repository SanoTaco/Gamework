#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "EnenyBullet.h"
#include "Boss.h"



namespace game_framework {

	EnemyBullet::EnemyBullet() {
		is_alive = false;
		isFaceToLeft = true;
		x = y = 0;
	}
	bool EnemyBullet::IsAlive() {
		return is_alive;
	}

	void EnemyBullet::LoadBitmap()
	{
		leftbullet.LoadBitmap(IDB_BOSSFIRE_LEFT, RGB(0, 0, 0));
		rightbullet.LoadBitmap(IDB_BOSSFIRE_RIGHT, RGB(0, 0, 0));
	}

	void EnemyBullet::OnMove(AbstractBoss* boss, int ymove)
	{
		const int STEP_SIZE = 15;
		const int DISTANCE = 300;
		int currentCoordinateOnLeft = boss->GetX1();
		int currentCoordinateOnRight = boss->GetX2();
		if (boss->IsAlive()) {
			if (boss->IsFaceLeft()) {
				// determine if bullet move overrange
				//	face left
				if (this->x >= (currentCoordinateOnLeft - DISTANCE)) {
					this->x -= STEP_SIZE;
					this->y -= 15 * ymove;
					SetIsFaceToLeft(true);
				}
				else {
					SetIsAlive(false);
				}

			}
			else {
				// face right 
				if (this->x <= (currentCoordinateOnRight + DISTANCE)) {
					this->x += STEP_SIZE;
					this->y += ymove * 15;
					SetIsFaceToLeft(false);
				}
				else {
					SetIsAlive(false);
				}
			}
		}
	}

	void EnemyBullet::OnShow(Map * m)
	{
		if (IsAlive()) {
			if (GetIsFaceToLeft()) {
				leftbullet.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				leftbullet.ShowBitmap();
			}
			else {
				rightbullet.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				rightbullet.ShowBitmap();
			}
		}
	}
	void EnemyBullet::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}
	void EnemyBullet::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	int EnemyBullet::GetX1()
	{
		return x;
	}
	int EnemyBullet::GetY1()
	{
		return y;
	}
	int EnemyBullet::GetX2()
	{
		return x + leftbullet.Width();
	}
	int EnemyBullet::GetY2()
	{
		return y + leftbullet.Height();
	}
	void EnemyBullet::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void EnemyBullet::SetIsFaceToLeft(bool flag)
	{
		isFaceToLeft = flag;
	}
	bool EnemyBullet::GetIsFaceToLeft() {
		return isFaceToLeft;
	}

















}




