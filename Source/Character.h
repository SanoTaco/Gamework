#include "Lava_Rock_1.h"
namespace game_framework {

	class Lava_Rock_1;

	class Hero 
	{
	public:
		Hero();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove(Lava_Rock_1 *m);
		void OnShow();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetXY(int nx, int ny); 
		

	private:
		CAnimation character;
		
		int x, y;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
	};
	class Character 
	{
	public :
		Character() { Initialize(); };
		virtual int  GetX1() = 0;					// 擦子左上角 x 座標
		virtual int  GetY1()=0;					// 擦子左上角 y 座標
		virtual int  GetX2()=0;					// 擦子右下角 x 座標
		virtual int  GetY2()=0;					// 擦子右下角 y 座標
		virtual void Initialize()=0;				// 設定擦子為初始值
		virtual void LoadBitmap()=0;				// 載入圖形
		virtual void OnMove()=0;					// 移動擦子
		virtual void OnShow()=0;					// 將擦子圖形貼到畫面
		virtual void SetMovingDown(bool flag)=0;	// 設定是否正在往下移動
		virtual void SetMovingLeft(bool flag)=0;	// 設定是否正在往左移動
		virtual void SetMovingRight(bool flag)=0; // 設定是否正在往右移動
		virtual void SetMovingUp(bool flag)=0;	// 設定是否正在往上移動
		virtual void SetXY(int nx, int ny)=0;		// 設定擦子左上角座標
	private :
		
	};

	
















}