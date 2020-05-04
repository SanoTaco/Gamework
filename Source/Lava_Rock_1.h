#pragma once

#include "CEraser.h"
namespace game_framework {

	class Map {

	public :
		void OnMove();
		virtual void LoadBitmap() = 0;
		virtual void OnShow() = 0;
		virtual int ScreenX(int &x) = 0;
		virtual int ScreenY(int &y) = 0;
		
		virtual bool IsEmpty(int x, int y) = 0;
		bool IsEnterTheDoor(CEraser *hero);                      //与主角的碰撞
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);

	};

	class Lava_Rock_1	:public Map
	{
	public:
		Lava_Rock_1();
		void LoadBitmap();
		void OnShow();
		bool IsEmpty(int x, int y);
		int ScreenX(int &x);
		int ScreenY(int &y);
		//bool IsEnterTheDoor(CEraser *hero);                      //与主角的碰撞
		//bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	private:
		const int X, Y;
		const int MW, MH;
		int lavaMap[10][10];
		CMovingBitmap lava, rock,blackground;
		
	};




}