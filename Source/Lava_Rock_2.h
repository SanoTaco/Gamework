#pragma once
#include "Lava_Rock_1.h"
namespace game_framework {


	class Lava_Rock_2 :public Map
	{
	public:
		Lava_Rock_2();
		~Lava_Rock_2();
		void OnShow(Map* map);
		void LoadBitmap();
		bool IsEmpty(int x, int y);
		void interact(Map* map, int &mapLevel, CEraser* hero, CBullet* bullet, Boomerang* boomerangItem);
		void dropItem(AbstractEnemy* enemy, vector<AbstractItem*> itemlist);
		void initialize();
		int ScreenX(int &x);
		int ScreenY(int &y);
		int GetX1();
		int GetY1();
		void SetX1Y1ToLeft(int x);
		void SetX1Y1ToRight(int x);
		void GetRandomItem(AbstractItem* item);
		bool isScrol();
		bool GetBossAlive();
	private:
		const int X, Y;
		const int MW, MH;
		int lavaMap[10][10];
		CMovingBitmap lava, rock,blackground;
		vector<AbstractEnemy*> enemies;
		vector<AbstractItem*> items;
		vector<AbstractItem*> itemlist;	//drop items
		vector<AbstractEnemy*> ::const_iterator iter;
		vector<AbstractItem *>::const_iterator item_iter;
		int delayCounter = 0;
		int invicibleCounter;
		int randX = 0;
		int randY = 0;
	};




}