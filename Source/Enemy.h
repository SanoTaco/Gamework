#pragma once

namespace game_framework {
	class Map;
	class AbstractEnemy {

	public:
		AbstractEnemy();
		virtual ~AbstractEnemy();
		bool IsAlive();											// �Ƿ����
		void SetIsAlive(bool alive);							// �O���Ƿ����
		//void SetBulletIsAlive(bool alive);
		void OnMove(Map* m);											// �Ƅ�
		void OnShow(Map* m);											// ���D���N������
		bool beShot(CBullet *bullet);						    // �Ƿ��䵽
		void SetXY(int nx, int ny);								// �O���������Ͻǵ�����		
		int  GetX1();					                    // �������Ͻ� x ����
		int  GetY1();					                   // �������Ͻ� y ����
		int  GetX2();					                   // �������½� x ����
		int  GetY2();					                   // �������½� y ����
		bool GetIs_right();
		int GetMaxDelay();
		void pause();
		bool Halt();
		void SetHalt(bool flag);
		bool touchHero(CEraser *hero);                      //�����ǵ���ײ
		//bool shotHero(CEraser *hero);                       //�����ӵ��������
		//void shooting();                                 //�����ӵ���ʼ��
		virtual void LoadBitmap();						// �d��D��
	protected:
		CAnimation    enemy_left;          // ��������
		CAnimation    enemy_right;          // ��������		
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		bool is_alive;				// �Ƿ����
		int x, y;					// ��������
		int x1, y1;                 //��¼��������
		bool is_Down;               
		bool is_right;             
		
		bool is_halt;


	};

	class EnemyDuck :public AbstractEnemy{
	public:
		
		EnemyDuck();
		virtual ~EnemyDuck();
		void LoadBitmap();
	};











}

