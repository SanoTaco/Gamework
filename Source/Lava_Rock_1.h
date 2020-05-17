#pragma once

#include "CEraser.h"
#include "Enemy.h"
#include "Item.h"
#include "CBullet.h"
namespace game_framework {

	class Map {

	public :
		void OnMove();
		virtual void LoadBitmap() = 0;
		virtual void OnShow(Map* map) = 0;
		virtual void initialize() = 0;
		virtual int ScreenX(int &x) = 0;
		virtual int ScreenY(int &y) = 0;
		virtual void interact(Map* map, int &mapLevel, CEraser* hero, CBullet* bullet) = 0;
		virtual bool IsEmpty(int x, int y) = 0;
		bool IsEnterTheDoor(CEraser *hero);                      //与主角的碰撞
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);

	};

	class Lava_Rock_1	:public Map
	{
	public:
		Lava_Rock_1();
		void initialize();
		void LoadBitmap();
		void interact(Map* map,int &mapLevel, CEraser* hero , CBullet* bullet);
		void OnShow(Map* map);
		bool IsEmpty(int x, int y);
		int ScreenX(int &x);
		int ScreenY(int &y);
		void GetRandomItem(AbstractItem* item);
		//bool IsEnterTheDoor(CEraser *hero);                      //与主角的碰撞
		//bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	private:
		const int X, Y;
		const int MW, MH;
		int lavaMap[10][10];
		CMovingBitmap lava, rock,blackground;
		vector<AbstractEnemy*> enemies;
		vector<AbstractItem*> items;

		vector<AbstractEnemy*> ::const_iterator iter;
		vector<AbstractItem *>::const_iterator item_iter;
		int delayCounter=0;
		int invicibleCounter;
		int randX = 0;
		int randY = 0;
		
	};




}