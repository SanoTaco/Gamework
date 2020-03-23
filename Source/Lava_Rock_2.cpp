#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Lava_Rock_2.h"

game_framework::Lava_Rock_2::Lava_Rock_2() :X(0), Y(0), MW(64), MH(48)
{
	int map_init[10][10] = { {1,1,1,1,1,1,1,1,1,1} ,    //row 1
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 2
									 {1,0,1,1,0,0,1,1,0,1} ,	//row 3
									 {1,0,1,0,0,0,0,1,0,1} ,	//row 4
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 5
									 {1,0,0,0,0,0,0,0,0,1} ,	//row 6
									 {0,0,1,0,0,0,0,1,0,1} ,	//row 7
									 {0,0,1,1,0,0,1,1,0,1} ,	//row 8
									 {0,0,0,0,0,0,0,0,0,1} ,	//row 9
									 {1,1,1,1,1,1,1,1,1,1} };	//row 10

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			lavaMap[i][j] = map_init[i][j];

		}
	}
}
