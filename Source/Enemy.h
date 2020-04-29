#pragma once

namespace game_framework {
	class Map;
	class AbstractEnemy {

	public:
		AbstractEnemy();
		virtual ~AbstractEnemy();
		bool IsAlive();											// 是否活著
		void SetIsAlive(bool alive);							// 設定是否活著
		//void SetBulletIsAlive(bool alive);
		void OnMove(Map* m);											// 移動
		void OnShow(Map* m);											// 將圖形貼到畫面
		bool beShot(CBullet *bullet);						    // 是否被射到
		void SetXY(int nx, int ny);								// 設定敌人左上角的座標		
		int  GetX1();					                    // 敌人左上角 x 座標
		int  GetY1();					                   // 敌人左上角 y 座標
		int  GetX2();					                   // 敌人右下角 x 座標
		int  GetY2();					                   // 敌人右下角 y 座標
		bool GetIs_right();
		int GetMaxDelay();
		void pause();
		bool Halt();
		void SetHalt(bool flag);
		bool touchHero(CEraser *hero);                      //与主角的碰撞
		//bool shotHero(CEraser *hero);                       //发射子弹射击主角
		//void shooting();                                 //发射子弹初始化
		virtual void LoadBitmap();						// 載入圖形
	protected:
		CAnimation    enemy_left;          // 敌人向左
		CAnimation    enemy_right;          // 敌人向右		
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		bool is_alive;				// 是否活著
		int x, y;					// 敌人坐标
		int x1, y1;                 //记录敌人坐标
		bool is_Down;               
		bool is_right;             
		
		bool is_halt;


	};

	class EnemyDuck :public AbstractEnemy{
	public:
		
		EnemyDuck();
		virtual ~EnemyDuck();
		void LoadBitmap();
	};











}

