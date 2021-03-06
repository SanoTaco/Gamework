﻿#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class Map;
	class AbstractItem;
	class UseableItem;
	class CEraser
	{
	public:
		CEraser();
		
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove(Map *m);					// 移動擦子
		void OnShow(Map* map);					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void SetFacingRight(bool flag);
		void SetFacingUp(bool flag);
		bool IsAlive();
		void SetIsAlive(bool flag);
		bool GetIsFaceToRight();
		bool GetIsFaceToUp();
		bool IsMovingRight();
		void SetIsInvincible(bool flag);
		void addHP(int num);
		int GetHP();
		int GetPoint();
		void addPoint(int number);
		void InvicibleCountDown();
		bool GetIsInvincible();
		bool IsMovingUp() { return isMovingUp; };
		bool GetItem(AbstractItem* item);
		bool GetUseableItem(UseableItem* useable);
		int GetATK();
		bool IsATKUp();
		void SetIsATKUp(bool flag);
		void SetATK(int num);
		bool IsGetShiedl();
		void SetShield(bool flag);
		bool IsGetUseableItem();
		void SetGetUseableItem(bool flag);

	protected:
		CAnimation animation;		// 擦子的動畫	
		CAnimation	invicible;
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		int hp;
		int atk;
		int x, y;					// 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isFaceToRight;
		bool isFaceToUp;
		bool isInvicible;
		bool isAlive;
		bool getATK;
		bool getShield;
		bool getUseableItem;
		int point;
		int invicibleCounter;

	};

}