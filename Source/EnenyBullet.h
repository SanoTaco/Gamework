#pragma once
namespace game_framework {
	class Map;
	class AbstractBoss;
	class EnemyBullet {
	public:

		EnemyBullet();

		bool IsAlive();											// �Ƿ����
		void LoadBitmap();                                      // �d��D��
		void OnMove(AbstractBoss* boss,int  ymove);						   // �Ƅ�
		void OnShow(Map *m);											// ���D���N������
		void SetIsAlive(bool alive);							// �O���Ƿ����
		void SetXY(int nx, int ny);                            //�����ӵ�����ʼλ�ã�ӦΪ������ұ�
		int  GetX1();					                    // �ӵ����Ͻ� x ����
		int  GetY1();					                   // �ӵ����Ͻ� y ����
		int  GetX2();					                   // �ӵ����½� x ����
		int  GetY2();					                   // �ӵ����½� y ����
		void SetTopLeft(int x, int y);
		void SetIsFaceToLeft(bool flag);
		bool GetIsFaceToLeft();

	private:
		CMovingBitmap leftbullet;
		CMovingBitmap rightbullet;

		bool is_alive;
		int x, y;
		bool isFaceToLeft;














	};
















}