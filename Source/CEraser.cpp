#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Lava_Rock_1.h"
#include "CBullet.h"
#include "Item.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 380;
		isAlive = true;
		isInvicible = false;
		hp = 3;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		animation.AddBitmap(IDB_HERO, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));

		invicible.AddBitmap(IDB_INVICIBLE, RGB(255, 255,255));
		invicible.AddBitmap(IDB_HERO, RGB(0, 0, 0));
		invicible.AddBitmap(IDB_INVICIBLE, RGB(255, 255, 255));
	}

	void CEraser::OnMove(Map *m)
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		if (isMovingLeft) {
			if (m->IsEmpty(x - 1, y) == true) {
				x -= STEP_SIZE;
			}
			
		}
			
		if (isMovingRight) {
			if (m->IsEmpty(x + 1 + animation.Width(), y) == true) {
				x += STEP_SIZE;
			}
			
		}
			
		if (isMovingUp) {
			if (m->IsEmpty(x, y - 1) == true) {
				y -= STEP_SIZE;
			}
			
		}
			
		if (isMovingDown) {
			if (m->IsEmpty(x, y + 1 + animation.Height()) == true) {
				y += STEP_SIZE;
			}
			
		}
			
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::SetFacingRight(bool flag)
	{
		isFaceToRight = flag;
	}

	void CEraser::SetFacingUp(bool flag)
	{
		isFaceToUp = flag;
	}

	bool CEraser::IsAlive()
	{
		return isAlive;
	}

	void CEraser::SetIsAlive(bool flag)
	{
		isAlive = flag;
	}

	

	bool CEraser::GetIsFaceToRight()
	{
		return isFaceToRight;
	}

	bool CEraser::GetIsFaceToUp()
	{
		return isFaceToUp;
	}

	bool CEraser::IsMovingRight()
	{
		return isMovingRight;
	}

	void CEraser::SetIsInvincible(bool flag)
	{
		isInvicible = flag;
	}

	void CEraser::addHP(int num)
	{
		hp += num;
	}

	int CEraser::GetHP()
	{
		return hp;
	}

	bool CEraser::GetIsInvincible()
	{
		return isInvicible;
	}

	bool CEraser::GetItem(AbstractItem * item)
	{
		if (!item->GetIsAlive()) {
			return false;
		}
		else {
			return HitRectangle(item->GetX1(), item->GetY1(), item->GetX2(), item->GetY2());
		}
	}

	bool CEraser::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// 怪物的左上角x座標

		int y1 = y;				//怪物的左上角y座標

		int x2 = x1 + animation.Width();	// 怪物的右下角x座標

		int y2 = y1 + animation.Height();	// 怪物的右下角y座標

									//
									// 檢敌人的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);//当子弹四个角和四个边，有一个碰到了敌人就算击中敌人
	}

	void CEraser::OnShow(Map* map)
	{
		if (!IsAlive()) {
			return;
		}
		else {
			if (isInvicible) {
				invicible.SetTopLeft(x, y);
				invicible.OnShow();
			}
			else {
				animation.SetTopLeft(x, y);
				animation.OnShow();
			}
		}
		

		
	}







	
}