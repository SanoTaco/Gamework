#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "ScrollMap.h"
#include "Boss.h"

game_framework::ScrollMap::ScrollMap() : X1(0), Y1(0), MW(64), MH(48)
{
	int matrix[10][30] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
	};
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			map_matrix[i][j] = matrix[i][j];

		}
	}








}

void game_framework::ScrollMap::LoadBitmap()
{
	lava.LoadBitmap(IDB_LAVA_1);
	rock.LoadBitmap(IDB_ROCK);
	blackground.LoadBitmapA(IDB_BLACKGROUND);
}

void game_framework::ScrollMap::OnShow(Map* map)
{
	int tempX = 0;
	int tempY = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 30; j++) {
			switch (map_matrix[i][j]) {
			case -1:
				tempX = MW * j;
				tempY = MH * i;
				blackground.SetTopLeft(ScreenX(tempX), ScreenY(tempY));
				blackground.ShowBitmap();
				break;
			case 0:
				tempX = MW * j;
				tempY = MH * i;
				rock.SetTopLeft(ScreenX(tempX), ScreenY(tempY));
				rock.ShowBitmap();
				break;
			case 1:
				tempX = MW * j;
				tempY = MH * i;
				lava.SetTopLeft(ScreenX(tempX), ScreenY(tempY));
				lava.ShowBitmap();
				break;
			default:
				ASSERT(-1);



			}
		}
	}
	if (boss->IsAlive()) {
		boss->OnShow(map);
	}
	for (item_iter = itemlist.begin(); item_iter != itemlist.end(); item_iter++) {
		if ((*item_iter)->GetIsAlive()) {
			(*item_iter)->OnShow(map);
		}
	}
	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		(*iter)->OnShow(map);
	}
	
}

int game_framework::ScrollMap::GetX1()
{
	return X1;
}

int game_framework::ScrollMap::GetY1()
{
	return Y1;
}

void game_framework::ScrollMap::SetX1(int & x)
{
	X1 = x;
}

void game_framework::ScrollMap::SetY1(int & y)
{
	Y1 = y;
}

void game_framework::ScrollMap::initialize()
{
	enemies.push_back(new EnemyDuck());
	enemies.push_back(new EnemyDuck());
	enemies.push_back(new EnchancedEnemy());
	boss = new BigBoss_1();
	boss->LoadBitmap();
	boss->SetXY(700, 240);
	boss->SetIsAlive(true);
	boss->SetHP(20);

	itemlist.push_back(new Item());
	itemlist.push_back(new Potion());
	itemlist.push_back(new Shield());
	int i = 1;
	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		(*iter)->LoadBitmap();
		(*iter)->SetXY(384 * i, 288);
		(*iter)->SetIsAlive(true);
		i++;
	}
	for (item_iter = itemlist.begin(); item_iter != itemlist.end(); item_iter++) {
		(*item_iter)->LoadBitmap();
		(*item_iter)->SetIsAlive(false);
	}
}

void game_framework::ScrollMap::interact(Map * map, int & mapLevel, CEraser * hero, CBullet * bullet)
{
	hero->OnMove(map);
	bullet->OnMove(hero);
	boss->OnMove(map,hero);

	if (this->enemies[0]->Halt()) {
		delayCounter++;
		if (delayCounter > 30 && delayCounter < 60) {
			enemies[0]->SetHalt(false);
			delayCounter = 0;
		}
	}
	else
	{
		enemies[0]->OnMove(map);
	}
	
	if (this->enemies[1]->Halt()) {
		delayCounter++;
		if (delayCounter > 30 && delayCounter < 60) {
			enemies[1]->SetHalt(false);
			delayCounter = 0;
		}
	}
	else
	{
		enemies[1]->OnMove(map);
	}
		
	
	enemies[2]->ChaseHero(map, hero);

	// drop items
	for (item_iter = itemlist.begin(); item_iter != itemlist.end(); item_iter++) {
		if (hero->IsAlive() && hero->GetItem(*item_iter) && (*item_iter)->GetIsAlive()) {
			if ((*item_iter)->Usage() == 1) {
				// its a potion
				if (hero->GetHP() < 3) {

					hero->addHP((*item_iter)->Effect());
				}

			}
			if ((*item_iter)->Usage() == 2) {
				//it can enchance hero
				hero->SetIsInvincible(true);
				invicibleCounter++;
				if (invicibleCounter >= 60 && invicibleCounter <= 70)
				{
					hero->SetIsInvincible(false);
					invicibleCounter = 0;
				}
			}
			if ((*item_iter)->Usage() == 0) {
				//points

				hero->addPoint((*item_iter)->Effect());
			}
			// ATK Up
			if ((*item_iter)->Usage() == 3) {
				hero->SetATK(3);

				hero->SetIsATKUp(true);
			}

			if ((*item_iter)->Usage() == 4) {
				hero->SetShield(true);
			}
			(*item_iter)->SetIsAlive(false);
		}

	}
	if (boss->IsAlive() && boss->beShot(bullet)) {
		boss->ChangeHP(-(hero->GetATK()));
		bullet->SetIsAlive(false);
		if ((boss->GetHP())<=0) {
			hero->addPoint(10);
			boss->SetIsAlive(false);
		}
	}



	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		if ((*iter)->IsAlive() && (*iter)->beShot(bullet)) {
			(*iter)->ChangeHP(-(hero->GetATK()));
			bullet->SetIsAlive(false);//子弹死了
			if ((*iter)->GetHP() <= 0) {
				(*iter)->SetIsAlive(false);//敌人死了
				//points.Add(1);
				hero->addPoint(1);
				map->dropItem((*iter), itemlist);

			}

		}

		if (hero->IsAlive() && (*iter)->touchHero(hero)) {
			if (hero->IsGetShiedl() == true) {
				hero->SetShield(false);
				hero->SetIsInvincible(true);
			}
			else {
				hero->SetIsInvincible(true);
				hero->addHP(-(*iter)->GetATK());
			}


			if (hero->GetHP() <= 0) {
				hero->SetIsAlive(false);
				//GotoGameState(GAME_STATE_OVER);
			}
		}
		if (hero->GetIsInvincible())                                      //主角无敌的时间
		{
			hero->InvicibleCountDown();

		}


	}




}

void game_framework::ScrollMap::dropItem(AbstractEnemy * enemy, vector<AbstractItem*> itemlist)
{
	int randNumber = (rand() % 9);
	if (randNumber <= 7 && randNumber >= 4) {
		itemlist[0]->SetXY(enemy->GetX1(), enemy->GetY1());
		itemlist[0]->SetIsAlive(true);

	}
	/*
	if (randNumber == 0) {
		// No Item droped , bad luck~
	}*/
	if (randNumber > 0 && randNumber < 4) {
		itemlist[1]->SetXY(enemy->GetX1(), enemy->GetY1());
		itemlist[1]->SetIsAlive(true);

	}
	if (randNumber > 7 && randNumber <= 9) {
		itemlist[2]->SetXY(enemy->GetX1(), enemy->GetY1());
		itemlist[2]->SetIsAlive(true);

	}
}

bool game_framework::ScrollMap::isScrol()
{
	return true;
}

void game_framework::ScrollMap::SetX1Y1ToLeft(int x)
{
	X1 = X1 - x;
}

void game_framework::ScrollMap::SetX1Y1ToRight(int x)
{
	X1 = X1 + x;
}

void game_framework::ScrollMap::SetX1Y1ToUp(int x)
{
	Y1 = Y1 - x;
}

void game_framework::ScrollMap::SetX1Y1ToDown(int x)
{
	Y1 = Y1 + x;
}

bool game_framework::ScrollMap::IsEmpty(int x, int y)
{
	int gx = x / 64;          // 轉換為格座標(整數除法)
	int gy = y / 48;         // 轉換為格座標(整數除法)
	bool state;
	switch (map_matrix[gy][gx])
	{
	case 0:
		state = true;
		break;
	case 1:
		state = false;
		break;
	case 2:
		state = false;
		break;
	default:
		state = false;

	}
	return state;
}

int game_framework::ScrollMap::ScreenX(int & x)
{
	return x - X1;
}

int game_framework::ScrollMap::ScreenY(int & y)
{
	return y - Y1;
}
