#pragma once

#include "CEraser.h"
#include "Enemy.h"
#include "Item.h"
#include "CBullet.h"
#include "UseableItem.h"
namespace game_framework {

	class Map {

	public :
		virtual ~Map() {};
		void OnMove();
		virtual void LoadBitmap() = 0;
		virtual void OnShow(Map* map) = 0;
		virtual void initialize() = 0;
		virtual int ScreenX(int &x) = 0;
		virtual int ScreenY(int &y) = 0;
		virtual void interact(Map* map, int &mapLevel, CEraser* hero, CBullet* bullet,Boomerang* boomerangItem) = 0;
		virtual bool IsEmpty(int x, int y) = 0;
		bool IsEnterTheDoor(CEraser *hero);                      //�����ǵ���ײ
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		virtual int GetX1() = 0;
		virtual int GetY1() = 0;
		virtual void SetX1Y1ToLeft(int x) = 0;
		virtual void SetX1Y1ToRight(int x) = 0;
		virtual void dropItem(AbstractEnemy* enemy, vector<AbstractItem*> itemlist) = 0;
		virtual bool isScrol() = 0;
		virtual bool GetBossAlive()=0;

	};

	class Lava_Rock_1	:public Map
	{
	public:
		Lava_Rock_1();
		~Lava_Rock_1();
		void initialize();
		void LoadBitmap();
		void interact(Map* map,int &mapLevel, CEraser* hero , CBullet* bullet, Boomerang* boomerangItem);
		void OnShow(Map* map);
		void dropItem(AbstractEnemy* enemy, vector< AbstractItem*> itemlist);
		bool IsEmpty(int x, int y);
		int ScreenX(int &x);
		int ScreenY(int &y);
		void GetRandomItem(AbstractItem* item);
		//bool IsEnterTheDoor(CEraser *hero);                      //�����ǵ���ײ
		//bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		int GetX1();
		int GetY1();
		void SetX1Y1ToLeft(int x);
		void SetX1Y1ToRight(int x);
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
		//vector<UseableItem*>	useableItems;
		int delayCounter=0;
		int invicibleCounter;
		int randX = 0;
		int randY = 0;
		
	};




}