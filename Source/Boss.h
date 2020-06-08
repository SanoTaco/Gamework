#pragma once
namespace game_framework {
	class Map;
	class CBullet;
	class CEraser;
	class EnemyBullet;

	class AbstractBoss {
	public:

		virtual void LoadBitmap() = 0;
		virtual void OnShow(Map* map) = 0;
		virtual void OnMove(Map* map , CEraser* hero) = 0;
		virtual void Shoot() = 0;
		virtual bool beShot(CBullet* bullet) = 0;
		virtual void SetXY(int x, int y) = 0;
		virtual int	GetX1() = 0;
		virtual int	GetY1() = 0;
		virtual int	GetX2() = 0;
		virtual int	GetY2() = 0;
		virtual void ChangeHP(int flag) = 0;
		virtual void SetHP(int flag) = 0;
		virtual void SetATK(int flag) = 0;
		virtual int GetATK() = 0;
		virtual int GetHP() = 0;
		virtual bool touchHero(CEraser* hero) = 0;
		virtual bool IsAlive() = 0;
		virtual void SetIsAlive(bool flag);
		virtual bool IsFaceLeft();
		virtual void SetFaceLeft(bool flag);
		virtual void Halt() = 0;
	protected:
		CAnimation boss;
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		int hp;
		int x, y;
		//int x1, y1;
		int atk;
		bool is_alive;
		bool face_left;
	};


	class BigBoss_1 :public AbstractBoss {
	public:
		BigBoss_1();
		void LoadBitmap();
		void OnShow(Map* map);
		void OnMove(Map* map, CEraser* hero);
		void Shoot();
		bool beShot(CBullet* bullet);
		void SetXY(int nx, int ny);
		int	GetX1();
		int	GetY1();
		int	GetX2();
		int	GetY2();
		void ChangeHP(int flag);
		void SetHP(int flag);
		void SetATK(int flag);
		int GetATK();
		int GetHP();
		void Halt();
		bool IsAlive();
		bool touchHero(CEraser* hero);



	private:
		vector<EnemyBullet*> ebullet;

	};




















}