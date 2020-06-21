#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "EnenyBullet.h"
#include "Boss.h"
#include "Lava_Rock_1.h"
#include "CEraser.h"
#include "CBullet.h"


namespace game_framework {

	BigBoss_1::BigBoss_1()
	{
		hp = 20;
		x = y = 0;
		atk = 2;
		is_alive = true;
		is_Shot = false;
		ebullet.push_back(new CBulletForMonster());
		ebullet.push_back(new CBulletForMonster());
		ebullet.push_back(new CBulletForMonster());
		vector<CBulletForMonster*>::iterator it;
		for (it = ebullet.begin(); it != ebullet.end(); it++) {
			(*it)->LoadBitmap();
		}
	}

	void BigBoss_1::LoadBitmap()
	{
		boss.AddBitmap(IDB_BOSS_1, RGB(255, 255, 255));
		boss2.AddBitmap(IDB_BOSS_2, RGB(255, 255, 255));
	}

	void BigBoss_1::OnShow(Map* map)
	{
		
		if (IsAlive()) {
			if (IsFaceLeft()) {
				boss.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
				boss.OnShow();

			}
			else {
				boss2.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
				boss2.OnShow();
			}
			
		}
		for (iter = ebullet.begin(); iter != ebullet.end(); iter++) {
			(*iter)->OnShow(map);
		}
	}

	void BigBoss_1::OnMove(Map * map, CEraser* hero)
	{
		int distance_1 = abs(GetX2() - hero->GetX1());// boss is on the left side of hero
		int distance_2 = abs(GetX1() - hero->GetX2());// boss is on the right side of hero
		if (IsAlive()) {
			if (GetX2() >= 1850) {
				x += 0;
				SetXY(GetX1() - 600, GetY1());
			}
			else if (GetX1() <= 70) {
				x -= 0;
				SetXY(GetX1() + 600, GetY1());
			}
			else {

				if ((hero->GetX1()) < GetX1()) {
					// hero is on the left side
					SetFaceLeft(true);
					if (distance_1 < 300) {
						//hero has been deceted 
						if (IsFaceLeft() && ((GetX1() - hero->GetX2()) < 130)) {
							x += 7;
						}


					}

				}
				//hero is on the right of boss
				if ((hero->GetX1()) > GetX2()) {
					SetFaceLeft(false);
					if (distance_2 < 200) {
						//hero has been deceted 
						if (!IsFaceLeft() && ((hero->GetX1() - GetX2()) > 200)) {
							x -= 7;
						}

					}
				}



			}

			Shoot();
			if (IsFaceLeft()) {
				int i = GetX1();
				ebullet[0]->OnMove(i, map, 0);
				ebullet[1]->OnMove(i, map, 1);
				ebullet[2]->OnMove(i, map, 2);
			}
			else {
				int i = GetX2();
				ebullet[0]->OnMove(i, map, 0);
				ebullet[1]->OnMove(i, map, 1);
				ebullet[2]->OnMove(i, map, 2);
			}
			for (int i = 0; i < 2; i++) {
				if (hero->IsAlive() && ebullet[i]->hurtHero(hero)) {
					if (hero->IsGetShiedl()) {
						hero->SetShield(false);
					}
					else {
						hero->addHP(-1);
						hero->SetIsInvincible(true);
						CAudio::Instance()->Play(AUDIO_HEROBELIGHTENED, false);
					}

					if (hero->GetHP() <= 0) {
						hero->SetIsAlive(false);
						hero->SetIsInvincible(true);
					}
					ebullet[i]->SetIsAlive(false);
					//hero->SetIsInvincible(true);
				}
			}
		}
		
		
		
		

	}

	void BigBoss_1::Shoot()
	{
		SetIsShot(true);
		vector< CBulletForMonster*>::iterator it;
		if (IsFaceLeft()) {
			//boss is facing left
			for (it = ebullet.begin(); it != ebullet.end(); it++) {
				if (!(*it)->IsAlive()) {
					//bullet goes to left
					(*it)->SetFaceRight(false);
					int i = GetX1();
					int j = GetY1();
					(*it)->SetIsAlive(true);
					(*it)->SetXY(i - (*it)->GetPictureWidth(), j + 20);
				}
				
			}
		}
		else {
			//boss facing right
			for (it = ebullet.begin(); it != ebullet.end(); it++) {
				if (!(*it)->IsAlive()) {
					//bullet goes to left
					(*it)->SetFaceRight(true);
					int i = GetX2();
					int j = GetY1();
					(*it)->SetIsAlive(true);
					(*it)->SetXY(i , j + 20);
				}

			}
		}
	}

	bool BigBoss_1::beShot(CBullet * bullet)
	{
		if (!IsAlive())//如果怪物死了就不执行碰撞
		{
			return false;
		}
		else    //怪物活着，子弹活着
		{
			if (!(bullet->IsAlive()))//怪物活着，子弹活着
			{
				return false;
			}
			else                     //怪物活着，子弹活着
			{

				return HitRectangle(bullet->GetX1(), bullet->GetY1(), bullet->GetX2(), bullet->GetY2());
			}

		}
	}

	bool BigBoss_1::beShotByItem(Boomerang * boomerang)
	{
		if (!IsAlive())//如果怪物死了就不执行碰撞
		{
			return false;
		}
		else    //怪物活着，子弹活着
		{
			if (!(boomerang->IsAlive()))//怪物活着，子弹活着
			{
				return false;
			}
			else                     //怪物活着，子弹活着
			{

				return HitRectangle(boomerang->GetX1(), boomerang->GetY1(), boomerang->GetX2(), boomerang->GetY2());
			}

		}
	}

	void BigBoss_1::SetXY(int nx, int ny)
	{
		x = nx; 
		y = ny;
	}

	int BigBoss_1::GetX1()
	{
		return x;
	}

	int BigBoss_1::GetY1()
	{
		return y;
	}

	int BigBoss_1::GetX2()
	{
		return x + boss.Width();
	}

	int BigBoss_1::GetY2()
	{
		return y + boss.Height();
	}

	void BigBoss_1::ChangeHP(int flag)
	{
		hp += flag;
	}

	void BigBoss_1::SetHP(int flag)
	{
		hp = flag;
	}

	void BigBoss_1::SetATK(int flag)
	{
		atk = flag;
	}

	int BigBoss_1::GetATK()
	{
		return atk;
	}

	int BigBoss_1::GetHP()
	{
		return hp;
	}

	void BigBoss_1::Halt()
	{
		x += 0;
		y += 0;
	}

	bool BigBoss_1::IsAlive()
	{
		return is_alive;
	}

	bool BigBoss_1::touchHero(CEraser * hero)
	{
		if (!IsAlive())      //如果怪物死了就不执行碰撞
		{
			return false;
		}
		else                 //如果怪物没死
		{
			if (hero->GetIsInvincible())//如果英雄处于无敌状态就打不中英雄
			{
				return false;
			}
			else                        //英雄不处于无敌状态时，可以被打中
			{
				return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
			}

		}
	}

	void BigBoss_1::floating()
	{
		const int DISTANCE = 180;
		const int STEP_SIZE =7;
		for (int i = 0; i < DISTANCE; i++) {
			y += STEP_SIZE;
		}
		for (int i = 0; i < DISTANCE; i++) {
			y -= STEP_SIZE;
		}
	}

	void BigBoss_1::AimingHero(CEraser * hero)
	{
		if ((GetY1()+56) == (hero->GetY1()+15 )) {

		}
		if ((GetY1()+56) < (hero->GetY1() + 15)) {
			y += 7;
		}
		if ((GetY1()+56) > (hero->GetY1() + 15)) {
			y -= 7;
		}
	}








	void AbstractBoss::SetIsAlive(bool flag)
	{
		is_alive = flag;
	}

	bool AbstractBoss::IsFaceLeft()
	{
		return face_left;
	}

	void AbstractBoss::SetFaceLeft(bool flag)
	{
		face_left = flag;
	}

	bool AbstractBoss::isShot()
	{
		return is_Shot;
	}

	void AbstractBoss::SetIsShot(bool flag)
	{
		is_Shot = flag;
	}

	bool AbstractBoss::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// 怪物的左上角x座標

		int y1 = y;				//怪物的左上角y座標

		int x2 = x1 + boss.Width();	// 怪物的右下角x座標

		int y2 = y1 + boss.Height();	// 怪物的右下角y座標

									//
									// 檢敌人的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);//当子弹四个角和四个边，有一个碰到了敌人就算击中敌人
	}

}