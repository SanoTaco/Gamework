#pragma once
namespace game_framework {

	class Map;
	class CEraser;
	class CBullet
	{
	public:
		CBullet();
		virtual ~CBullet();
		bool IsAlive();											// 是否活著
		virtual void LoadBitmap();                                      // 載入圖形
		virtual void OnShow(Map *m);											// 將圖形貼到畫面
		virtual void OnKeyDown(UINT nChar, CEraser* hero, Map* map);        //按下回车的时候发射子弹
		void SetIsAlive(bool alive);							// 設定是否活著
		void OnMove(CEraser* hero);						   // 移動
		void SetXY(int nx, int ny);                            //设置子弹的起始位置，应为人物的右边
		int  GetX1();					                    // 子弹左上角 x 座標
		int  GetY1();					                   // 子弹左上角 y 座標
		int  GetX2();					                   // 子弹右下角 x 座標
		int  GetY2();					                   // 子弹右下角 y 座標
		void SetTopLeft(int x, int y);
		void SetFaceRight(bool flag);                   //设置子弹向左还是右
		void SetFaceUp(bool flag);
		bool GetIsFaceToRight();                       //得到当前子弹向左向右的状态
		bool GetIsFaceToUp();

	protected:
		CMovingBitmap bullet_1;
		CMovingBitmap bullet_0;
		bool is_alive;				                                  // 是否活著
		int x, y;                                           //子弹图左上角的坐标
		bool isFaceToRight;                                 //子弹是否向右移动
		bool isFaceToLeft;
		bool isFaceToUp;
		bool isFaceToDown;
	};

	class Boomerang  {

	public :
		Boomerang();
		~Boomerang();
		void LoadBitmap();
		void OnKeyDown(UINT nChar, CEraser* hero, Map* map);
		void OnShow(Map *m);
		void SetIsAlive(bool alive);							// 設定是否活著
		void OnMove(CEraser* hero);						   // 移動
		void SetXY(int nx, int ny);                            //设置子弹的起始位置，应为人物的右边
		int  GetX1();					                    // 子弹左上角 x 座標
		int  GetY1();					                   // 子弹左上角 y 座標
		int  GetX2();					                   // 子弹右下角 x 座標
		int  GetY2();					                   // 子弹右下角 y 座標
		void SetTopLeft(int x, int y);
		bool IsAlive();

		void SetFaceRight(bool flag);                   //设置子弹向左还是右
		void SetFaceUp(bool flag);
		bool GetIsFaceToRight();                       //得到当前子弹向左向右的状态
		
	private:
		CAnimation boomerang;
		bool is_alive;				                                  // 是否活著
		int x, y;                                           //子弹图左上角的坐标
		bool isFaceToRight;                                 //子弹是否向右移动
		bool isFaceToLeft;
		bool isFaceToUp;
		bool isFaceToDown;
	};


	class CBulletForMonster
	{
	public:
		CBulletForMonster();

		bool touchHero(CEraser *hero);						// 是否碰到擦子

		bool IsAlive();											// 是否活著
		virtual void LoadBitmap();                                      // 載入圖形
		virtual void OnMove(int &i, Map* map,int type);						   // 移動
		virtual void OnShow(Map* map);											// 將圖形貼到畫面
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetXY(int nx, int ny);                            //设置子弹的起始位置，应为人物的右边
		int  GetX1();					                    // 子弹左上角 x 座標
		int  GetY1();					                   // 子弹左上角 y 座標
		int  GetX2();					                   // 子弹右下角 x 座標
		int  GetY2();					                   // 子弹右下角 y 座標
		int GetPictureWidth();
		void SetFaceRight(bool flag);                   //设置子弹向左还是右
		bool GetIsFaceToRight();                       //得到当前子弹向左向右的状态
		bool hurtHero(CEraser* hero);
		//void Shooting(AbstractEnemy* enemy);
	protected:
		CMovingBitmap bulletForMonsterBmp;
		CMovingBitmap bulletForMonsterBmp2;
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
		bool is_alive;				                                  // 是否活著
		int x, y;                                           //子弹图左上角的坐标
		bool isFaceToRight;                                 //子弹是否向右移动

	};
}