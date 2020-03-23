#include "Lava_Rock_1.h"
namespace game_framework {

	class Lava_Rock_1;

	class Hero 
	{
	public:
		Hero();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove(Lava_Rock_1 *m);
		void OnShow();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetXY(int nx, int ny); 
		

	private:
		CAnimation character;
		
		int x, y;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
	};
	class Character 
	{
	public :
		Character() { Initialize(); };
		virtual int  GetX1() = 0;					// �������Ͻ� x ����
		virtual int  GetY1()=0;					// �������Ͻ� y ����
		virtual int  GetX2()=0;					// �������½� x ����
		virtual int  GetY2()=0;					// �������½� y ����
		virtual void Initialize()=0;				// �O�����Ӟ��ʼֵ
		virtual void LoadBitmap()=0;				// �d��D��
		virtual void OnMove()=0;					// �ƄӲ���
		virtual void OnShow()=0;					// �����ӈD���N������
		virtual void SetMovingDown(bool flag)=0;	// �O���Ƿ����������Ƅ�
		virtual void SetMovingLeft(bool flag)=0;	// �O���Ƿ����������Ƅ�
		virtual void SetMovingRight(bool flag)=0; // �O���Ƿ����������Ƅ�
		virtual void SetMovingUp(bool flag)=0;	// �O���Ƿ����������Ƅ�
		virtual void SetXY(int nx, int ny)=0;		// �O���������Ͻ�����
	private :
		
	};

	
















}