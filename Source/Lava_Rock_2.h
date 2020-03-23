#pragma once
#include "Lava_Rock_1.h"
namespace game_framework {


	class Lava_Rock_2 : public Lava_Rock_1
	{
	public:
		Lava_Rock_2();
		
	private:
		const int X, Y;
		const int MW, MH;
		int lavaMap[10][10];
		CMovingBitmap lava, rock;
	};




}