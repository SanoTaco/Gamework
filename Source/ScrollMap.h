#pragma once
#include "Lava_Rock_1.h"
#include "Boss.h"
namespace game_framework {
	
	class ScrollMap :public Map {
	public:
		ScrollMap();
		~ScrollMap();
		void LoadBitmap();
		void OnShow(Map* map);        //��ʾ��ͼ
		int  GetX1();          //�õ�ӫĻ���Ͻ��ڵ�ͼ�ϵ�X����
		int  GetY1();            //�õ�ӫĻ���Ͻ��ڵ�ͼ�ϵ�Y����
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
		int ScreenX(int& x);                //����������ӫĻ�������X
		int ScreenY(int& y);              //����������ӫĻ�������Y
	private:
		CMovingBitmap rock,lava,blackground;        //�ϰ���
		vector<AbstractItem*> itemlist;
		vector<AbstractEnemy*> enemies;
		vector<AbstractEnemy*> ::const_iterator iter;
		vector<AbstractItem *>::const_iterator item_iter;
		AbstractBoss* boss;
		int map_matrix[20][60];              //����һ����ͼ�����index
		int X1, Y1;                  //���ͼ�����Ͻ�x,y����(ӫĻ�ڵ�ͼ�ϵ�λ��)
		int MW, MH;         //ÿ��С��ͼ�Ŀ�͸�
		int invicibleCounter;
		int delayCounter = 0;// normal enemies delay counter
		

	};















}
