#pragma once
#include "Lava_Rock_1.h"
#include "Boss.h"
namespace game_framework {
	
	class ScrollMap :public Map {
	public:
		ScrollMap();
		~ScrollMap();
		void LoadBitmap();
		void OnShow(Map* map);        //显示地图
		int  GetX1();          //得到荧幕左上角在地图上的X坐标
		int  GetY1();            //得到荧幕左上角在地图上的Y坐标
		void SetX1(int &x);
		void SetY1(int &y);
		void initialize();
		void interact(Map* map, int &mapLevel, CEraser* hero, CBullet* bullet, Boomerang* boomerangItem);
		bool GetBossAlive();
		void dropItem(AbstractEnemy* enemy, vector<AbstractItem*> itemlist);
		bool isScrol();

		void SetX1Y1ToLeft(int x);
		void SetX1Y1ToRight(int x);
		void SetX1Y1ToUp(int x);
		void SetX1Y1ToDown(int x);
		bool IsEmpty(int x, int y);
		//void SetPosition(int x, int y);
		int ScreenX(int& x);                //返回人物在荧幕里的坐标X
		int ScreenY(int& y);              //返回人物在荧幕里的坐标Y
	private:
		CMovingBitmap rock,lava,blackground;        //障碍物
		vector<AbstractItem*> itemlist;
		vector<AbstractEnemy*> enemies;
		vector<AbstractEnemy*> ::const_iterator iter;
		vector<AbstractItem *>::const_iterator item_iter;
		AbstractBoss* boss;
		int map_matrix[20][60];              //建立一个地图矩阵的index
		int X1, Y1;                  //大地图的左上角x,y坐标(荧幕在地图上的位置)
		int MW, MH;         //每张小地图的宽和高
		int invicibleCounter;
		int delayCounter = 0;// normal enemies delay counter
		

	};















}
