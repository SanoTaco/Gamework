#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Lava_Rock_Map.h"

namespace game_framework {

	











	Lava_Rock_Map::Lava_Rock_Map():X(0),Y(0),MW(64),MH(48)
	{
		int map_init[10][10] = { {1,1,1,1,1,1,1,1,1,1} ,    //row 1
								 {1,0,0,0,0,0,1,1,1,1} ,	//row 2
								 {1,0,0,0,0,0,0,0,0,1} ,	//row 3
								 {1,0,0,0,0,0,0,0,0,1} ,	//row 4
								 {1,0,0,0,1,1,0,0,0,1} ,	//row 5
								 {1,0,0,0,1,1,0,0,0,1} ,	//row 6
								 {1,0,0,0,0,0,0,0,0,0} ,	//row 7
								 {1,0,0,0,0,0,0,0,0,0} ,	//row 8
								 {1,1,1,1,0,0,0,0,0,0} ,	//row 9
								 {1,1,1,1,1,1,1,1,1,1} };	//row 10
								
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				map[i][j] = map_init[i][j];
			}
		}
		
		
		
		
		
		
		
	}

	void Lava_Rock_Map::LoadBitmap()
	{
		lava.LoadBitmap(IDB_LAVA_1);
		rock.LoadBitmap(IDB_ROCK);
	}

	void Lava_Rock_Map::OnShow()
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				switch (map[j][i]) {
				case -1:
					break;
				case 0:
					rock.SetTopLeft(X + MW * i, Y + MH * j);
					rock.ShowBitmap();
					break;
				case 1:
					lava.SetTopLeft(X + MW * i, Y + MH * j);
					lava.ShowBitmap();
					break;
				default:
					ASSERT(-1);



				}
			}
		}
	}

}