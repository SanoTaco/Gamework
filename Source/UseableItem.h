#pragma once
namespace game_framework {
	class CEraser;
	class Map;

	class UseableItem {
	public:
		UseableItem();
		void LoadBitmap();
		void OnMove(Map* map, CEraser* hero);
		void Retrive(Map* map, CEraser* hero);
		void OnShow(Map* map);
		int Usage();
		int Effect();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void SetXY(int nx, int ny);
		bool GetIsUsed();
		void SetIsUsed(bool flag);
		bool IsFaceToRight();
		void SetFaceToRight(bool flag);
		
		bool IsAlive();
		void SetIsAlive(bool flag);
		void OnKeyDown(UINT nChar, CEraser* hero, Map* map);

	protected:
		CAnimation useable;
		int x, y;
		bool is_used;
		bool isAlive;
		int usage;
		int effect;
		bool isFaceToRight;
		


	};












}