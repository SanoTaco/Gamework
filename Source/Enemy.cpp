#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "Lava_Rock_1.h"
#include "CEraser.h"
#include "Enemy.h"


game_framework::AbstractEnemy::AbstractEnemy()
{
	is_alive = true;
	is_right = true;
	is_Down = true;
	x = 0;
	y = 0;
	x1 = 0;
	y1 = 0;
	is_halt = false;
	hp = 2;
}

game_framework::AbstractEnemy::~AbstractEnemy()
{

}

bool game_framework::AbstractEnemy::IsAlive()
{
	return is_alive;
}

void game_framework::AbstractEnemy::SetIsAlive(bool alive)
{
	is_alive = alive;
}

void game_framework::AbstractEnemy::OnMove(Map * m)
{
	if (!IsAlive()) {
		return;
	}
	const int STEP_SIZE = 50;
	if(IsAlive()) {
		
		if (Halt() == true) {
			x += 0;
			y += 0;
		}
		if (Halt() == false) {
			int direction = (rand() % 4);
			int currentX = GetX1();
			int currentY = GetY1();
			switch (direction)
			{
			case 0:
				//direction goes up
				if (m->IsEmpty(x, y - STEP_SIZE) == true) {
					
						for (int i = 0; i < STEP_SIZE; i++)
						{
							y -= 1;
						}
						
					
				}
				SetHalt(true);
				break;
			case 1:
				//direction goes right
				if (m->IsEmpty(x + enemy_left.Width() + STEP_SIZE, y) == true) {
					
						for (int i = 0; i < STEP_SIZE; i++) {
							x += 1;
						}
						
				}
				SetHalt(true);
				break;
			case 2:
				//direction goes down
				if (m->IsEmpty(x, y + enemy_left.Height() + STEP_SIZE) == true) {
					
						for (int i = 0; i < STEP_SIZE; i++)
						{
							y += 1;
						}
						
				}
				SetHalt(true);
				break;
			case 3:
				//direction goes left
				if (m->IsEmpty(x - STEP_SIZE, y) == true) {
					
						for (int i = 0; i < STEP_SIZE; i++) {
							x -= 1;
						}
						
					


				}
				SetHalt(true);
				break;

			default:
				SetHalt(true);
				break;
			}
		
		}
		
		



	}
}

void game_framework::AbstractEnemy::ChaseHero(Map * map, CEraser * hero)
{
	if (!IsAlive()) {
		return;
	}
	
	if (IsAlive() == true) {
		//enemy goes left
		if (hero->GetX1() < this->GetX1()) {
			if (map->IsEmpty((x - 1), y) == true) {
				x -= 1;
			}

		}
		else
		{
			if (map->IsEmpty((x + 1), y) == true) {
				x += 1;
			}


		}

		// enemy goes up
		if (hero->GetY1() < this->GetY1()) {
			if (map->IsEmpty(x, (y - 1)) == true) {
				y -= 1;
			}

		}
		else {
			if (map->IsEmpty(x, (y + 1)) == true) {
				y += 1;
			}

		}
		
	}
}

void game_framework::AbstractEnemy::OnShow(Map * m)
{
	if (!IsAlive()) {
		return;
	}
	if (IsAlive()) {
		enemy_left.SetTopLeft(x, y);
		enemy_left.OnShow();
	}
}

bool game_framework::AbstractEnemy::beShot(CBullet * bullet)
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

void game_framework::AbstractEnemy::LoadBitmap()
{
	enemy_left.AddBitmap(IDB_Duck, RGB(255, 255, 255));
}

bool game_framework::AbstractEnemy::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	int x1 = x;				// 怪物的左上角x座標

	int y1 = y;				//怪物的左上角y座標

	int x2 = x1 + enemy_left.Width();	// 怪物的右下角x座標

	int y2 = y1 + enemy_left.Height();	// 怪物的右下角y座標

								//
								// 檢敌人的矩形與參數矩形是否有交集
								//
	return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);//当子弹四个角和四个边，有一个碰到了敌人就算击中敌人
}

void game_framework::AbstractEnemy::SetXY(int nx, int ny)
{
	x = nx; y = ny;
	x1 = nx; y1 = ny;
}



int game_framework::AbstractEnemy::GetX1()
{
	return x;
}

int game_framework::AbstractEnemy::GetY1()
{
	return y;
}

int game_framework::AbstractEnemy::GetX2()
{
	return x + enemy_left.Width();
}

int game_framework::AbstractEnemy::GetY2()
{
	return y + enemy_left.Height();
}
int game_framework::AbstractEnemy::GetMaxDelay()
{
	return 150;
}
void game_framework::AbstractEnemy::ChangeHP(int flag)
{
	hp += flag;
}
void game_framework::AbstractEnemy::SetHP(int initialHP)
{
	hp = initialHP;
}
int game_framework::AbstractEnemy::GetHP()
{
	return hp;
}
void game_framework::AbstractEnemy::pause()
{
		this->x += 0;
		this->y += 0;
	
}
bool game_framework::AbstractEnemy::Halt()
{
	return is_halt;
}
void game_framework::AbstractEnemy::SetHalt(bool flag)
{
	is_halt = flag;
}
bool game_framework::AbstractEnemy::touchHero(CEraser * hero)
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
/////////////////////////
//
////////////////////////
game_framework::EnemyDuck::EnemyDuck()
{
	is_alive = true;
	is_right = true;
	is_Down = true;
	x = y = x1 = y1 = 0;
}

game_framework::EnemyDuck::~EnemyDuck()
{
}

void game_framework::EnemyDuck::LoadBitmap()
{
	enemy_left.AddBitmap(IDB_Duck,RGB(0,0,0));
}

game_framework::EnchancedEnemy::EnchancedEnemy()
{
	is_alive = true;
	is_right = true;
	is_Down = true;
	x = y = x1 = y1 = 0;
	SetHP(5);
}

game_framework::EnchancedEnemy::~EnchancedEnemy()
{
}

void game_framework::EnchancedEnemy::LoadBitmap()
{
	enemy_left.AddBitmap(IDB_ENCHANCEDMONSTER1, RGB(255, 255, 255));
}

