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

	CBullet::~CBullet()
	{
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
			}
			
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

	

	void Boomerang::LoadBitmap()
	{
		boomerang.AddBitmap(IDB_BOOMERANG_1,RGB(0, 255, 0));
		boomerang.AddBitmap(IDB_BOOMERANG_2,RGB(0, 255, 0));
		boomerang.AddBitmap(IDB_BOOMERANG_3,RGB(0, 255, 0));
		boomerang.AddBitmap(IDB_BOOMERANG_4,RGB(0, 255, 0));
	}

	void Boomerang::OnKeyDown(UINT nChar, CEraser * hero, Map * map)
	{
		const int KEY_SPACE = 0x58;

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
			if (nChar == KEY_SPACE && hero->GetIsFaceToRight() == false)                           //若人物面向左边
			{
				SetFaceRight(hero->GetIsFaceToRight());//则设置子弹方向为左边
				int i = hero->GetX1();
				int j = hero->GetY1();
				SetIsAlive(true);
				//SetXY(i - bullet_1.Width() , j + 20);
			}
			if (hero->GetIsFaceToUp() && nChar == KEY_SPACE) {
				SetFaceUp(true);
				int i = hero->GetX1();
				int j = hero->GetY1();
				SetXY(i - 20, j);
			}
			if (nChar == KEY_SPACE && hero->GetIsFaceToUp() == false) {
				SetFaceUp(false);
				int i = hero->GetX2();
				int j = hero->GetY1();
				SetXY(i + 20, j);
			}
		}
	}

	void Boomerang::OnShow(Map * m)
	{
		if (!IsAlive()) {
			//explosion.ShowBitmap();
			return;
		}
		if (IsAlive()) {
			if (GetIsFaceToRight() == true) {
				boomerang.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				boomerang.OnShow();
			}
			else {
				boomerang.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				boomerang.OnShow();
			}

		}
	}

	void Boomerang::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Boomerang::OnMove(CEraser * hero)
	{
		const int STEP_SIZE = 10;
		const int DISTENCE = 300;


		if (IsAlive()) {
			
			if (isFaceToRight == true) {
				int i = hero->GetX2();

				if (this->x <= i + DISTENCE)
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
				if (this->x > i - DISTENCE) {
					this->x -= STEP_SIZE;
					SetFaceRight(false);
				}
				else {
					SetIsAlive(false);
				}
			}

		}
		
	}

	void Boomerang::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	int Boomerang::GetX1()
	{
		return x;
	}

	int Boomerang::GetY1()
	{
		return y;
	}

	int Boomerang::GetX2()
	{
		return x + boomerang.Width();
	}

	int Boomerang::GetY2()
	{
		return y + boomerang.Height();
	}

	void Boomerang::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool Boomerang::IsAlive()
	{
		return is_alive;
	}

	void Boomerang::SetFaceRight(bool flag)
	{
		isFaceToRight = flag;
	}

	void Boomerang::SetFaceUp(bool flag)
	{
		isFaceToUp = flag;
	}

	bool Boomerang::GetIsFaceToRight()
	{
		return isFaceToRight;
	}

	Boomerang::Boomerang()
	{
		is_alive = false;
		isFaceToRight = true;
		x = y = 0;
	}

	Boomerang::~Boomerang()
	{
	}

	CBulletForMonster::CBulletForMonster()
	{
		is_alive = false;
		isFaceToRight = true;
		x = y = 0;
	}

	bool CBulletForMonster::touchHero(CEraser * hero)
	{
		if (!(is_alive))      //若子弹死了，就碰不到英雄
		{
			return false;
		}
		else                  //若子弹没死，检测是否碰到英雄
		{
			if (hero->GetIsInvincible())//如果英雄处于无敌状态就打不中英雄
			{
				return false;
			}
			else                        //英雄不处于无敌状态，子弹可以打中英雄
			{
				return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
			}
		}
	}

	bool CBulletForMonster::IsAlive()
	{
		return is_alive;
	}

	void CBulletForMonster::LoadBitmap()
	{
		bulletForMonsterBmp.LoadBitmap(IDB_BOSSFIRE_RIGHT, RGB(0, 0, 0));
		bulletForMonsterBmp2.LoadBitmap(IDB_BOSSFIRE_LEFT, RGB(0, 0, 0));
	}

	void CBulletForMonster::OnMove(int & i, Map * map, int type)
	{
		const int STEP_SIZE = 8;
		if (!is_alive)
		{
			return;
		}
		else
		{
			if (isFaceToRight) //当人右且弹右时，子弹坚持往右走
			{
				if (map->IsEmpty(GetX2() + STEP_SIZE, y) && map->IsEmpty(GetX2() + STEP_SIZE, GetY2()))
				{
					//int i = enemy->GetX2();

					if (x <= (i + 500))
					{
						if (type == 0) {
							y -= 6;
						}
						if (type == 2) {
							y += 6;
						}
						x += STEP_SIZE;
					}
					else
					{
						SetIsAlive(false);

					}
				}
				else
				{
					SetIsAlive(false);
				}
			}

			if (!isFaceToRight)//当人左且弹左时，子弹坚持往左走
			{
				if (map->IsEmpty(GetX1() - STEP_SIZE, y) && map->IsEmpty(GetX1() - STEP_SIZE, GetY2()))
				{
					//int i = enemy->GetX1();

					if (x >= (i - 500))
					{
						if (type == 0) {
							y -= 6;
						}
						if (type == 2) {
							y += 6;
						}
						x -= STEP_SIZE;
					}
					else
					{
						SetIsAlive(false);
					}
				}
				else
				{
					SetIsAlive(false);
				}

			}
		}
	}

	void CBulletForMonster::OnShow(Map * map)
	{
		if (!IsAlive())
			return;

		if (IsAlive())
		{
			if (isFaceToRight)
			{
				bulletForMonsterBmp.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
				bulletForMonsterBmp.ShowBitmap();
			}
			else
			{
				bulletForMonsterBmp2.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
				bulletForMonsterBmp2.ShowBitmap();
			}

		}
	}

	void CBulletForMonster::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CBulletForMonster::SetXY(int nx, int ny)
	{
		this->x = nx;
		this->y = ny;
	}

	int CBulletForMonster::GetX1()
	{
		return x;
	}

	int CBulletForMonster::GetY1()
	{
		return y;
	}

	int CBulletForMonster::GetX2()
	{
		return x+bulletForMonsterBmp.Width();
	}

	int CBulletForMonster::GetY2()
	{
		return y + bulletForMonsterBmp.Height();
	}

	int CBulletForMonster::GetPictureWidth()
	{
		return bulletForMonsterBmp.Width();
	}

	void CBulletForMonster::SetFaceRight(bool flag)
	{
		isFaceToRight = flag;
	}

	bool CBulletForMonster::GetIsFaceToRight()
	{
		return isFaceToRight;
	}

	bool CBulletForMonster::hurtHero(CEraser * hero)
	{
		if(hero->IsAlive()) {
			return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
		}
		else {
			return false;
		}
	}

	bool CBulletForMonster::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;			// hero的左上角x座標

		int y1 = y;			// hero的左上角y座標

		int x2 = GetX2();	// hero的右下角x座標

		int y2 = GetY2();	// hero的右下角y座標

		//
		// 檢敌人的矩形與參數矩形是否有交集
		//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);//当子弹四个角和四个边，有一个碰到了敌人就算击中敌人

	}

}