#pragma once
namespace game_framework {

	class Map;
	class CEraser;
	class CBullet
	{
	public:
		CBullet();
		virtual ~CBullet();
		bool IsAlive();											// �Ƿ����
		virtual void LoadBitmap();                                      // �d��D��
		virtual void OnShow(Map *m);											// ���D���N������
		virtual void OnKeyDown(UINT nChar, CEraser* hero, Map* map);        //���»س���ʱ�����ӵ�
		void SetIsAlive(bool alive);							// �O���Ƿ����
		void OnMove(CEraser* hero);						   // �Ƅ�
		void SetXY(int nx, int ny);                            //�����ӵ�����ʼλ�ã�ӦΪ������ұ�
		int  GetX1();					                    // �ӵ����Ͻ� x ����
		int  GetY1();					                   // �ӵ����Ͻ� y ����
		int  GetX2();					                   // �ӵ����½� x ����
		int  GetY2();					                   // �ӵ����½� y ����
		void SetTopLeft(int x, int y);
		void SetFaceRight(bool flag);                   //�����ӵ���������
		void SetFaceUp(bool flag);
		bool GetIsFaceToRight();                       //�õ���ǰ�ӵ��������ҵ�״̬
		bool GetIsFaceToUp();

	protected:
		CMovingBitmap bullet_1;
		CMovingBitmap bullet_0;
		bool is_alive;				                                  // �Ƿ����
		int x, y;                                           //�ӵ�ͼ���Ͻǵ�����
		bool isFaceToRight;                                 //�ӵ��Ƿ������ƶ�
		bool isFaceToLeft;
		bool isFaceToUp;
		bool isFaceToDown;
	};

	class Boomerang  {

	public :
		Boomerang();
		~Boomerang();
		void LoadBitmap();
		void OnKeyDown(UINT nChar, CEraser* hero, Map* map);
		void OnShow(Map *m);
		void SetIsAlive(bool alive);							// �O���Ƿ����
		void OnMove(CEraser* hero);						   // �Ƅ�
		void SetXY(int nx, int ny);                            //�����ӵ�����ʼλ�ã�ӦΪ������ұ�
		int  GetX1();					                    // �ӵ����Ͻ� x ����
		int  GetY1();					                   // �ӵ����Ͻ� y ����
		int  GetX2();					                   // �ӵ����½� x ����
		int  GetY2();					                   // �ӵ����½� y ����
		void SetTopLeft(int x, int y);
		bool IsAlive();

		void SetFaceRight(bool flag);                   //�����ӵ���������
		void SetFaceUp(bool flag);
		bool GetIsFaceToRight();                       //�õ���ǰ�ӵ��������ҵ�״̬
		
	private:
		CAnimation boomerang;
		bool is_alive;				                                  // �Ƿ����
		int x, y;                                           //�ӵ�ͼ���Ͻǵ�����
		bool isFaceToRight;                                 //�ӵ��Ƿ������ƶ�
		bool isFaceToLeft;
		bool isFaceToUp;
		bool isFaceToDown;
	};


	class CBulletForMonster
	{
	public:
		CBulletForMonster();

		bool touchHero(CEraser *hero);						// �Ƿ��������Ӥl

		bool IsAlive();											// �Ƿ����
		virtual void LoadBitmap();                                      // �d��D��
		virtual void OnMove(int &i, Map* map,int type);						   // �Ƅ�
		virtual void OnShow(Map* map);											// ���D���N������
		void SetIsAlive(bool alive);							// �O���Ƿ����
		void SetXY(int nx, int ny);                            //�����ӵ�����ʼλ�ã�ӦΪ������ұ�
		int  GetX1();					                    // �ӵ����Ͻ� x ����
		int  GetY1();					                   // �ӵ����Ͻ� y ����
		int  GetX2();					                   // �ӵ����½� x ����
		int  GetY2();					                   // �ӵ����½� y ����
		int GetPictureWidth();
		void SetFaceRight(bool flag);                   //�����ӵ���������
		bool GetIsFaceToRight();                       //�õ���ǰ�ӵ��������ҵ�״̬
		bool hurtHero(CEraser* hero);
		//void Shooting(AbstractEnemy* enemy);
	protected:
		CMovingBitmap bulletForMonsterBmp;
		CMovingBitmap bulletForMonsterBmp2;
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �Ƿ��������������ľ���
		bool is_alive;				                                  // �Ƿ����
		int x, y;                                           //�ӵ�ͼ���Ͻǵ�����
		bool isFaceToRight;                                 //�ӵ��Ƿ������ƶ�

	};
}