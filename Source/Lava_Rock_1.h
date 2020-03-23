#pragma once

#include "CEraser.h"
namespace game_framework {


	class Lava_Rock_1
	{
	public:
		Lava_Rock_1();
		void LoadBitmap();
		void OnShow();
		bool IsEmpty(int x, int y);
		bool isEnterDoor(CEraser * hero);
	private:
		const int X, Y;
		const int MW, MH;
		int lavaMap[10][10];
		CMovingBitmap lava, rock;
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};




}