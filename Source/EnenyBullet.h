#pragma once
namespace game_framework {
	class Map;
	class AbstractBoss;
	class EnemyBullet {
	public:

		EnemyBullet();

		bool IsAlive();											// 是否活著
		void LoadBitmap();                                      // 載入圖形
		void OnMove(AbstractBoss* boss,int  ymove);						   // 移動
		void OnShow(Map *m);											// 將圖形貼到畫面
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetXY(int nx, int ny);                            //设置子弹的起始位置，应为人物的右边
		int  GetX1();					                    // 子弹左上角 x 座標
		int  GetY1();					                   // 子弹左上角 y 座標
		int  GetX2();					                   // 子弹右下角 x 座標
		int  GetY2();					                   // 子弹右下角 y 座標
		void SetTopLeft(int x, int y);
		void SetIsFaceToLeft(bool flag);
		bool GetIsFaceToLeft();

	private:
		CMovingBitmap leftbullet;
		CMovingBitmap rightbullet;

		bool is_alive;
		int x, y;
		bool isFaceToLeft;














	};
















}