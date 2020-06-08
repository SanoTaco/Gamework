#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Lava_Rock_1.h"


game_framework::Lava_Rock_1::Lava_Rock_1():X(0), Y(0), MW(64), MH(48)
{
	
	int map_init[10][10] = { {1,1,1,1,1,1,1,1,1,1} ,    //row 1
							 {1,0,0,0,0,0,1,1,1,1} ,	//row 2
							 {1,0,0,0,0,0,0,0,0,1} ,	//row 3
							 {1,0,0,0,0,0,0,0,0,1} ,	//row 4
						     {1,0,0,0,1,1,0,0,0,1} ,	//row 5
							 {1,0,0,0,1,1,0,0,0,1} ,	//row 6
							 {1,0,0,0,0,0,0,0,0,0} ,	//row 7
							 {1,0,0,0,0,0,0,0,0,0} ,	//row 8
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

void game_framework::Lava_Rock_1::initialize()
{
	enemies.push_back(new EnemyDuck());

	items.push_back(new Item());
	items.push_back(new Potion());
	items.push_back(new Star());
	items.push_back(new AttackUp());
	items.push_back(new Shield());


	itemlist.push_back(new Item());
	itemlist.push_back(new Potion());
	itemlist.push_back(new Shield());
	
	useableItems.push_back(new UseableItem());
	useableItems[0]->LoadBitmap();
	useableItems[0]->SetXY(130, 130);
	
	useableItems[0]->SetIsAlive(true);
	int i = 1;

	for (iter = enemies.begin(); iter != enemies.end();iter++) {
		(*iter)->LoadBitmap();
		(*iter)->SetXY(384, 288);
		(*iter)->SetIsAlive(true);
	}
	/*
	for (item_iter = items.begin(); item_iter != items.end(); item_iter++) {
		(*item_iter)->LoadBitmap();
		(*item_iter)->SetIsAlive(true);
		(*item_iter)->SetXY(70, 50 * (i));
		i++;
	}*/
	

	for (item_iter = items.begin(); item_iter != items.end(); item_iter++) {
		
		GetRandomItem(*item_iter);
		
	}
	for (item_iter = itemlist.begin(); item_iter != itemlist.end(); item_iter++) {
		(*item_iter)->LoadBitmap();
		(*item_iter)->SetIsAlive(false);
	}
	
}


void game_framework::Lava_Rock_1::LoadBitmap()
{
	lava.LoadBitmap(IDB_LAVA_1);
	rock.LoadBitmap(IDB_ROCK);
	blackground.LoadBitmapA(IDB_BLACKGROUND);
	
}

void game_framework::Lava_Rock_1::interact(Map* map,int &mapLevel, CEraser* hero, CBullet* bullet)
{
	
	hero->OnMove(map);
	//hero in the  map



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
	
	if (useableItems[0]->GetIsUsed() == false) {
		if (hero->GetUseableItem(useableItems[0])) {
			useableItems[0]->SetIsAlive(false);
			hero->SetGetUseableItem(true);
		}
	}
	
	useableItems[0]->OnMove(map, hero);
	bullet->OnMove(hero);

	if (map->IsEnterTheDoor(hero)) {
		mapLevel++;
		hero->SetXY(hero->GetX1() - 300, hero->GetY1());
	}


	// items already showed on map
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
			(*item_iter)->SetIsAlive(false);
		}

	}

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

void game_framework::Lava_Rock_1::OnShow(Map* map)
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
	useableItems[0]->OnShow(map);



}

void game_framework::Lava_Rock_1::dropItem(AbstractEnemy * enemy, vector<AbstractItem*> itemlist)
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

bool game_framework::Lava_Rock_1::IsEmpty(int x, int y)
{
	int gx = x / 64; // 轉換為格座標(整數除法)
	int gy = y / 48; // 轉換為格座標(整數除法)
	return lavaMap[gx][gy] == 0; // 假設 0 代表空的
}



int game_framework::Lava_Rock_1::ScreenX(int & x)
{
	return x;
}

int game_framework::Lava_Rock_1::ScreenY(int & y)
{
	return y;
}
void game_framework::Lava_Rock_1::GetRandomItem(AbstractItem* item)
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
int game_framework::Lava_Rock_1::GetX1()
{
	return X;
}
int game_framework::Lava_Rock_1::GetY1()
{
	return Y;
}
void game_framework::Lava_Rock_1::SetX1Y1ToLeft(int x)
{
}
void game_framework::Lava_Rock_1::SetX1Y1ToRight(int x)
{
}
bool game_framework::Lava_Rock_1::isScrol()
{
	return true;
}
/*
bool game_framework::Lava_Rock_1::IsEnterTheDoor(CEraser * hero)
{
	return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
}

bool game_framework::Lava_Rock_1::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	//int x1 = 1855;				//门的左上角x坐标
	int x1 = 576;				//门的左上角x坐标
	//int y1 = 359;				//门的左上角y坐标
	int y1 = 288;				//门的左上角y坐标
	//int x2 = 1919;	// 门的右下角x坐标
	int x2 = 640;	// 门的右下角x坐标
	//int y2 = 433;	// 门的右下角y坐标
	int y2 = 432;	// 门的右下角y坐标
								//
								// 檢主角的矩形與參數矩形是否有交集
								//
	return (tx1 >= x1 && tx2 <= x2 && ty1 >= y1 && ty2 <= y2);//当主角图形的四个角，完全进入门框时，才算是进门了。
}*/



void game_framework::Map::OnMove()
{
}

bool game_framework::Map::IsEnterTheDoor(CEraser * hero)
{
	return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
}

bool game_framework::Map::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	//int x1 = 1855;				//门的左上角x坐标
	int x1 = 576;				//门的左上角x坐标
	//int y1 = 359;				//门的左上角y坐标
	int y1 = 288;				//门的左上角y坐标
	//int x2 = 1919;	// 门的右下角x坐标
	int x2 = 640;	// 门的右下角x坐标
	//int y2 = 433;	// 门的右下角y坐标
	int y2 = 432;	// 门的右下角y坐标
								//
								// 檢主角的矩形與參數矩形是否有交集
								//
	return (tx1 >= x1 && tx2 <= x2 && ty1 >= y1 && ty2 <= y2);//当主角图形的四个角，完全进入门框时，才算是进门了。
}




