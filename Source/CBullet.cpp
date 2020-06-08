#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"



#include "CBullet.h"


namespace game_framework {



	CBullet::CBullet()
	{
		is_alive = false;
		isFaceToRight = true;
		x = y = 0;
	}

	bool CBullet::IsAlive()
	{
		return is_alive;
	}

	void CBullet::LoadBitmap()
	{
		bullet_0.LoadBitmap(IDB_BULLET_0, RGB(255, 255, 255));
		bullet_1.LoadBitmap(IDB_BULLET_1,RGB(255,255,255));
		//explosion.LoadBitmap(IDB_EXPLOSION,RGB(0,0,0));
	}

	void CBullet::OnMove( CEraser * hero)
	{
		const int STEP_SIZE = 10;
		const int DISTENCE = 200;
		
		
		if (IsAlive()) {
			
			if (isFaceToRight == true) {
				int i = hero->GetX2();
				
				if (this->x <= i+DISTENCE)
				{
					this->x += STEP_SIZE;
					SetFaceRight(true);
				}
				else {
					SetIsAlive(false);
				}
				

			}
			else {
				int i = hero->GetX1();
				if (this->x >i- DISTENCE) {
					this->x -= STEP_SIZE;
					SetFaceRight(false);
				}
				else {
					SetIsAlive(false);
				}
			}/*
			else if (isFaceToUp==true) { // facing up 
				int i = hero->GetY1();
				if (y >i- DISTENCE) {
					y -= STEP_SIZE;
					
				}
				else {
					SetIsAlive(false);
				}
			}
			else if(isFaceToDown ==true){
				int i = hero->GetY2();
				if (y <i+ DISTENCE) {
					y += DISTENCE;
					
				}
				else {
					SetIsAlive(false);
				}
			}*/
			
		}
		
	}

	void CBullet::OnShow(Map *m)
	{
		if(!IsAlive()) {
			//explosion.ShowBitmap();
			return;
		}
		if (IsAlive()) {
			if (GetIsFaceToRight() == true) {
				bullet_1.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				bullet_1.ShowBitmap();
			}
			else {
				bullet_0.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				bullet_0.ShowBitmap();
			}
			
		}
		//bullet_1.ShowBitmap();
	}
	void CBullet::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}
	void CBullet::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	int CBullet::GetX1()
	{
		return x;
	}
	int CBullet::GetY1()
	{
		return y;
	}
	int CBullet::GetX2()
	{
		return x + bullet_1.Width();
	}
	int CBullet::GetY2()
	{
		return y + bullet_1.Height();
	}
	void CBullet::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;

	}
	void CBullet::SetFaceRight(bool flag)
	{
		isFaceToRight = flag;
		//isFaceToLeft = !flag;

		//isFaceToDown = isFaceToUp = false;
	}

	void CBullet::SetFaceUp(bool flag)
	{
		isFaceToUp = flag;
		//isFaceToDown = !flag;
		//isFaceToLeft = isFaceToRight = false;
	}

	bool CBullet::GetIsFaceToRight()
	{
		return isFaceToRight;
	}

	bool CBullet::GetIsFaceToUp()
	{
		return isFaceToUp;
	}

	void CBullet::OnKeyDown(UINT nChar, CEraser *hero, Map *map)
	{
		const int KEY_SPACE = 0x20;

		if (nChar == KEY_SPACE)
		{
			if (hero->GetIsFaceToRight() && nChar == KEY_SPACE)      //若人物面向右边
			{
				SetFaceRight(hero->GetIsFaceToRight());//则设置子弹方向为右边
				int i = hero->GetX2();
				int j = hero->GetY1();
				SetIsAlive(true);
				//SetXY(i + 1, j + 20);
				
			}
			if(nChar == KEY_SPACE && hero->GetIsFaceToRight() == false)                           //若人物面向左边
			{
				SetFaceRight(hero->GetIsFaceToRight());//则设置子弹方向为左边
				int i = hero->GetX1();
				int j = hero->GetY1();
				SetIsAlive(true);
				//SetXY(i - bullet_1.Width() , j + 20);
			}
			if (hero->GetIsFaceToUp()&&nChar == KEY_SPACE) {
				SetFaceUp(true);
				int i = hero->GetX1();
				int j = hero->GetY1();
				SetXY(i-20, j);
			}
			if(nChar == KEY_SPACE && hero->GetIsFaceToUp()==false){
				SetFaceUp(false);
				int i = hero->GetX2();
				int j = hero->GetY1();
				SetXY(i+20, j);
			}
		}

	}

	

}