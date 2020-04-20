#pragma once
namespace game_framework {

	class Lava_Rock_1;
	class CEraser;
	class CBullet
	{
	public:
		CBullet();

		bool IsAlive();											// 是否活著
		void LoadBitmap();                                      // 載入圖形
		void OnMove(CEraser* hero);						   // 移動
		void OnShow(Lava_Rock_1 *m);											// 將圖形貼到畫面
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetXY(int nx, int ny);                            //设置子弹的起始位置，应为人物的右边
		int  GetX1();					                    // 子弹左上角 x 座標
		int  GetY1();					                   // 子弹左上角 y 座標
		int  GetX2();					                   // 子弹右下角 x 座標
		int  GetY2();					                   // 子弹右下角 y 座標
		void SetTopLeft(int x, int y);
		void OnKeyDown(UINT nChar, CEraser* hero, Lava_Rock_1* map);        //按下回车的时候发射子弹

		void SetFaceRight(bool flag);                   //设置子弹向左还是右
		void SetFaceUp(bool flag);
		bool GetIsFaceToRight();                       //得到当前子弹向左向右的状态
		bool GetIsFaceToUp();

	protected:
		
		//CMovingBitmap explosion;


	private:
		CMovingBitmap bullet_1;
		CMovingBitmap bullet_0;
		bool is_alive;				                                  // 是否活著
		int x, y;                                           //子弹图左上角的坐标
		bool isFaceToRight;                                 //子弹是否向右移动
		bool isFaceToLeft;
		bool isFaceToUp;
		bool isFaceToDown;
	};

}