#include "Map.h"
namespace game_framework
{
	class Lava_Rock_Map:public Map
	{
	public:
		Lava_Rock_Map();
		void LoadBitmap();
		void OnShow();
	private:
		const int X, Y;
		const int MW, MH;
		int map[10][10];
		CMovingBitmap lava, rock;
	};






}