#pragma once

namespace game_framework {
	class Map;
	class CBullet;
	class Boomerang;
	class AbstractEnemy {

	public:
		AbstractEnemy();
		virtual ~AbstractEnemy();
		bool IsAlive();											// �Ƿ����
		void SetIsAlive(bool alive);							// �O���Ƿ����
		//void SetBulletIsAlive(bool alive);
		void OnMove(Map* m);											// �Ƅ�
		void ChaseHero(Map* map, CEraser* hero);
		void OnShow(Map* m);											// ���D���N������
		bool beShot(CBullet *bullet);						    // �Ƿ��䵽
		bool beShotByItem(Boomerang* boomerang);
		void SetXY(int nx, int ny);								// �O���������Ͻǵ�����		
		int  GetX1();					                    // �������Ͻ� x ����
		int  GetY1();					                   // �������Ͻ� y ����
		int  GetX2();					                   // �������½� x ����
		int  GetY2();					                   // �������½� y ����
		int GetMaxDelay();
		void ChangeHP(int flag);
		void SetHP(int initialHP);
		int GetATK();
		void SetATK(int flag);
		int GetHP();
		void pause();
		bool Halt();
		void SetHalt(bool flag);
		bool touchHero(CEraser *hero);                      //�����ǵ���ײ
		virtual void LoadBitmap();						// �d��D��
	protected:
		CAnimation    enemy_left;          // ��������
		CAnimation    enemy_right;          // ��������		
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		bool is_alive;				// �Ƿ����
		int x, y;					// ��������
		int x1, y1;                 //��¼��������
		int hp;
		int atk;
		bool is_Down;               
		bool is_right;             
		bool is_halt;
	};

	class EnemyDuck :public AbstractEnemy{
	public:
		
		EnemyDuck();
		 ~EnemyDuck();
		void LoadBitmap();
	};

	class EnchancedEnemy : public AbstractEnemy {
	public:
		EnchancedEnemy();
		~EnchancedEnemy();
		void LoadBitmap();
		
	};

}

