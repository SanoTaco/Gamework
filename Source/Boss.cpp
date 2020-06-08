#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "EnenyBullet.h"
#include "Boss.h"
#include "Lava_Rock_1.h"
#include "CEraser.h"



namespace game_framework {

	BigBoss_1::BigBoss_1()
	{
		hp = 20;
		x = y = 0;
		atk = 2;
		is_alive = true;
		ebullet.push_back(new EnemyBullet());
		ebullet.push_back(new EnemyBullet());
		ebullet.push_back(new EnemyBullet());
	}

	void BigBoss_1::LoadBitmap()
	{
		boss.AddBitmap(IDB_BOSS_1, RGB(255, 255, 255));
	}

	void BigBoss_1::OnShow(Map* map)
	{
		
		if (IsAlive()) {
			boss.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
			boss.OnShow();
		}
	}

	void BigBoss_1::OnMove(Map * map, CEraser* hero)
	{
		if (GetX2() >= 1850) {
			x += 0;
			SetXY(GetX1() - 600, GetY1());
		}
		else if (GetX1() <= 70) {
			x -= 0;
			SetXY(GetX1() + 600, GetY1());
		}
		else {
			if (abs(GetX1() - hero->GetX2()) < 200) {
				//hero has been deceted 
				if ((hero->GetX1()) < GetX1()) {
					// hero is on the left side
					SetFaceLeft(true);
					if (IsFaceLeft() && ((GetX1() - hero->GetX2()) < 130)) {
						x += 7;
					}
					else if (IsFaceLeft() && ((GetX1() - hero->GetX2()) > 200)) {
						x -= 7;
					}

				}
				else if ((hero->GetX1()) > GetX1()) {
					SetFaceLeft(false);
					if (!IsFaceLeft() && ((GetX1() - hero->GetX2()) < 130)) {
						x += 7;
					}
					else if (!IsFaceLeft() && ((GetX1() - hero->GetX2()) > 200)) {
						x -= 7;
					}
				}
			}
			else {

			}
		}
		
		

	}

	void BigBoss_1::Shoot()
	{
		
	}

	bool BigBoss_1::beShot(CBullet * bullet)
	{
		if (!IsAlive())//����������˾Ͳ�ִ����ײ
		{
			return false;
		}
		else    //������ţ��ӵ�����
		{
			if (!(bullet->IsAlive()))//������ţ��ӵ�����
			{
				return false;
			}
			else                     //������ţ��ӵ�����
			{

				return HitRectangle(bullet->GetX1(), bullet->GetY1(), bullet->GetX2(), bullet->GetY2());
			}

		}
	}

	void BigBoss_1::SetXY(int nx, int ny)
	{
		x = nx; 
		y = ny;
	}

	int BigBoss_1::GetX1()
	{
		return x;
	}

	int BigBoss_1::GetY1()
	{
		return y;
	}

	int BigBoss_1::GetX2()
	{
		return x + boss.Width();
	}

	int BigBoss_1::GetY2()
	{
		return y + boss.Height();
	}

	void BigBoss_1::ChangeHP(int flag)
	{
		hp += flag;
	}

	void BigBoss_1::SetHP(int flag)
	{
		hp = flag;
	}

	void BigBoss_1::SetATK(int flag)
	{
		atk = flag;
	}

	int BigBoss_1::GetATK()
	{
		return atk;
	}

	int BigBoss_1::GetHP()
	{
		return hp;
	}

	void BigBoss_1::Halt()
	{
		x += 0;
		y += 0;
	}

	bool BigBoss_1::IsAlive()
	{
		return is_alive;
	}

	bool BigBoss_1::touchHero(CEraser * hero)
	{
		if (!IsAlive())      //����������˾Ͳ�ִ����ײ
		{
			return false;
		}
		else                 //�������û��
		{
			if (hero->GetIsInvincible())//���Ӣ�۴����޵�״̬�ʹ���Ӣ��
			{
				return false;
			}
			else                        //Ӣ�۲������޵�״̬ʱ�����Ա�����
			{
				return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
			}

		}
	}








	void AbstractBoss::SetIsAlive(bool flag)
	{
		is_alive = flag;
	}

	bool AbstractBoss::IsFaceLeft()
	{
		return face_left;
	}

	void AbstractBoss::SetFaceLeft(bool flag)
	{
		face_left = flag;
	}

	bool AbstractBoss::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// ��������Ͻ�x����

		int y1 = y;				//��������Ͻ�y����

		int x2 = x1 + boss.Width();	// ��������½�x����

		int y2 = y1 + boss.Height();	// ��������½�y����

									//
									// �z���˵ľ����c���������Ƿ��н���
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);//���ӵ��ĸ��Ǻ��ĸ��ߣ���һ�������˵��˾�����е���
	}

}