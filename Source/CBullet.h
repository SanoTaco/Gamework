#pragma once
namespace game_framework {

	class Lava_Rock_1;
	class CEraser;
	class CBullet
	{
	public:
		CBullet();

		bool IsAlive();											// �Ƿ����
		void LoadBitmap();                                      // �d��D��
		void OnMove(CEraser* hero);						   // �Ƅ�
		void OnShow(Lava_Rock_1 *m);											// ���D���N������
		void SetIsAlive(bool alive);							// �O���Ƿ����
		void SetXY(int nx, int ny);                            //�����ӵ�����ʼλ�ã�ӦΪ������ұ�
		int  GetX1();					                    // �ӵ����Ͻ� x ����
		int  GetY1();					                   // �ӵ����Ͻ� y ����
		int  GetX2();					                   // �ӵ����½� x ����
		int  GetY2();					                   // �ӵ����½� y ����
		void SetTopLeft(int x, int y);
		void OnKeyDown(UINT nChar, CEraser* hero, Lava_Rock_1* map);        //���»س���ʱ�����ӵ�

		void SetFaceRight(bool flag);                   //�����ӵ���������
		void SetFaceUp(bool flag);
		bool GetIsFaceToRight();                       //�õ���ǰ�ӵ��������ҵ�״̬
		bool GetIsFaceToUp();

	protected:
		
		//CMovingBitmap explosion;


	private:
		CMovingBitmap bullet_1;
		CMovingBitmap bullet_0;
		bool is_alive;				                                  // �Ƿ����
		int x, y;                                           //�ӵ�ͼ���Ͻǵ�����
		bool isFaceToRight;                                 //�ӵ��Ƿ������ƶ�
		bool isFaceToLeft;
		bool isFaceToUp;
		bool isFaceToDown;
	};

}