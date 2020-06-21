#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Lava_Rock_2.h"

game_framework::Lava_Rock_2::Lava_Rock_2() :X(0), Y(0), MW(64), MH(48)
{
	int map_init[10][10] = {		 {1,1,1,1,1,1,1,1,1,1} ,    //row 1
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 2
									 {1,0,1,1,0,0,1,1,0,1} ,	//row 3
									 {1,0,1,0,0,0,0,1,0,1} ,	//row 4
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 5
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 6
									 {0,0,1,0,0,0,0,1,0,0} ,	//row 7
									 {0,0,1,1,0,0,1,1,0,0} ,	//row 8
									 {1,1,1,1,1,1,1,1,1,1} ,	//row 9
									 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} };	//row 10

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			lavaMap[i][j] = map_init[j][i];

		}
	}
}

game_framework::Lava_Rock_2::~Lava_Rock_2()
{

	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		delete (*iter);
	}
	for (item_iter = items.begin(); item_iter != items.end(); item_iter++) {
		delete (*item_iter);
	}
	for (item_iter = itemlist.begin(); item_iter != itemlist.end(); item_iter++) {
		delete (*item_iter);
	}
}


void game_framework::Lava_Rock_2::OnShow(Map* map)
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (lavaMap[i][j]) {
			case -1:
				blackground.SetTopLeft(X + MW * i, Y + MH * j);
				blackground.ShowBitmap();
				break;
			case 0:
				rock.SetTopLeft(X + MW * i, Y + MH * j);
				rock.ShowBitmap();
				break;
			case 1:
				lava.SetTopLeft(X + MW * i, Y + MH * j);
				lava.ShowBitmap();
				break;
			default:
				ASSERT(-1);



			}
		}
	}
	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		(*iter)->OnShow(map);
	}
	for (item_iter = items.begin(); item_iter != items.end(); item_iter++) {
		(*item_iter)->OnShow(map);
	}
	for (item_iter = itemlist.begin(); item_iter != itemlist.end(); item_iter++) {
		if ((*item_iter)->GetIsAlive()) {
			(*item_iter)->OnShow(map);
		}
		
	}

}

void game_framework::Lava_Rock_2::LoadBitmap()
{
	rock.LoadBitmap(IDB_ROCK);
	lava.LoadBitmap(IDB_LAVA_1);
	blackground.LoadBitmap(IDB_BLACKGROUND);
}

bool game_framework::Lava_Rock_2::IsEmpty(int x, int y)
{
	int gx = x / 64; // 轉換為格座標(整數除法)
	int gy = y / 48; // 轉換為格座標(整數除法)
	return lavaMap[gx][gy] == 0; // 假設 0 代表空的
}

void game_framework::Lava_Rock_2::interact(Map * map, int &mapLevel, CEraser * hero, CBullet * bullet, Boomerang* boomerangItem)
{
	hero->OnMove(map);
	//hero in the  map


	
	
	enemies[0]->ChaseHero(map, hero);

	boomerangItem->OnMove(hero);
	bullet->OnMove(hero);

	if (map->IsEnterTheDoor(hero)) {
		mapLevel++;
		hero->SetXY(hero->GetX1() - 300, hero->GetY1());
	}



	for (item_iter = items.begin(); item_iter != items.end(); item_iter++) {
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
			if ((*item_iter)->Usage() == 5) {
				hero->SetGetUseableItem(true);
			}
			(*item_iter)->SetIsAlive(false);
		}

	}

	// get droped items
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



	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		if ((*iter)->IsAlive() && (*iter)->beShot(bullet)) {
			
			(*iter)->ChangeHP(-(hero->GetATK()));
			bullet->SetIsAlive(false);//子弹死了
			if ((*iter)->GetHP() <= 0) {
				(*iter)->SetIsAlive(false);//敌人死了
				CAudio::Instance()->Play(AUDIO_ENCHANCEDENEMY, false);
				//points.Add(1);
				hero->addPoint(1);
				CAudio::Instance()->Play(AUDIO_DING, false);
				map->dropItem((*iter), itemlist);
				CAudio::Instance()->Play(AUDIO_MONSTERDEATH, false);
			}

		}
		if ((*iter)->IsAlive() && (*iter)->beShotByItem(boomerangItem)) {
			(*iter)->ChangeHP(-10);
			boomerangItem->SetIsAlive(false);
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
				CAudio::Instance()->Play(AUDIO_HEROBELIGHTENED, false);
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

void game_framework::Lava_Rock_2::dropItem(AbstractEnemy * enemy, vector<AbstractItem*> itemlist)
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

void game_framework::Lava_Rock_2::initialize()
{
	enemies.push_back(new EnchancedEnemy());
	items.push_back(new Potion());
	items.push_back(new Shield());


	itemlist.push_back(new Item());
	itemlist.push_back(new Potion());
	itemlist.push_back(new Shield());



	for (iter = enemies.begin(); iter != enemies.end(); iter++) {
		(*iter)->LoadBitmap();
		(*iter)->SetXY(384, 288);
		(*iter)->SetIsAlive(true);
	}
	for (item_iter = items.begin(); item_iter != items.end(); item_iter++) {

		GetRandomItem(*item_iter);

	}
	for (item_iter = itemlist.begin(); item_iter != itemlist.end(); item_iter++) {
		(*item_iter)->LoadBitmap();
		(*item_iter)->SetIsAlive(false);
	}
}

int game_framework::Lava_Rock_2::ScreenX(int & x)
{
	return x;
}

int game_framework::Lava_Rock_2::ScreenY(int & y)
{
	return y;
}

int game_framework::Lava_Rock_2::GetX1()
{
	return X;
}

int game_framework::Lava_Rock_2::GetY1()
{
	return Y;
}

void game_framework::Lava_Rock_2::SetX1Y1ToLeft(int x)
{
}

void game_framework::Lava_Rock_2::SetX1Y1ToRight(int x)
{
}

void game_framework::Lava_Rock_2::GetRandomItem(AbstractItem * item)
{
	randX = (rand() % 9);
	randY = (rand() % 9);
	if (lavaMap[randX][randY] == 0) {
		(*item_iter)->LoadBitmap();
		(*item_iter)->SetIsAlive(true);
		(*item_iter)->SetXY(randX * 64, randY * 48);
	}
	else {
		GetRandomItem(*item_iter);
	}
}

bool game_framework::Lava_Rock_2::isScrol()
{
	return false;
}

bool game_framework::Lava_Rock_2::GetBossAlive()
{
	return false;
}
