#pragma once

namespace game_framework {
	// it has the same usage as gold for exchange
	class Map;
	class AbstractItem {
	public:
		void OnMove();
		virtual void LoadBitmap()=0;
		virtual void OnShow(Map* map) = 0;
		virtual void SetXY(int nx, int ny)=0;
		virtual int Usage() = 0;
		virtual int Effect() = 0;
		virtual void SetIsAlive(bool flag)=0;
		virtual bool GetIsAlive() = 0;
		virtual int GetX1() = 0;
		virtual int GetY1() = 0;
		virtual int GetX2() = 0;
		virtual int GetY2() = 0;

	};
	class Item :public AbstractItem{
	public:
		Item();
		 ~Item();
		 void OnShow(Map* map);
		void OnMove();
		 void LoadBitmap();
		 int Usage();
		 int Effect();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void SetXY(int nx, int ny);
		bool GetIsAlive();
		void SetIsAlive(bool flag);

	protected:
		CMovingBitmap point;
		int usage;
		int effect;
		int x, y;
		bool isalive;

	};



	// for now it can only heal hero
	class Potion : public AbstractItem{
	public:
		Potion()  { usage = 1; effect = 1; x = y = 0; };
		void OnShow(Map* map);
		void SetXY(int nx, int ny);
		void LoadBitmap();
		int Usage();
		int Effect();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		bool GetIsAlive();
		void SetIsAlive(bool flag);
	private:
		CMovingBitmap potion;
		int usage;
		int effect;
		int x ;
		int y ;
		bool isalive = false;
	};



	//item for enchance hero ability
	class  Star :public AbstractItem {
	public:
		Star() { usage = 2; effect = 1; x = y = 0; };
		void OnShow(Map* map);
		void SetXY(int nx, int ny);
		void LoadBitmap();
		int Usage();
		int Effect();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		bool GetIsAlive();
		void SetIsAlive(bool flag);
	private:
		CMovingBitmap star;
		int effect, usage;
		int x ;
		int y ;
		bool isalive = false;



	};
	class AttackUp : public AbstractItem {
	public:
		AttackUp();
		void OnShow(Map* map);
		void SetXY(int nx, int ny);
		void LoadBitmap();
		int Usage();
		int Effect();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		bool GetIsAlive();
		void SetIsAlive(bool flag);
	private:
		CMovingBitmap atk;
		int effect, usage;
		int x;
		int y;
		bool isalive = false;
	};

	class Shield :public AbstractItem {
	public:
		Shield();
		void OnShow(Map* map);
		void SetXY(int nx, int ny);
		void LoadBitmap();
		int Usage();
		int Effect();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		bool GetIsAlive();
		void SetIsAlive(bool flag);
	private:
		CMovingBitmap shield;
		int effect, usage;
		int x;
		int y;
		bool isalive = false;
	};



}
















