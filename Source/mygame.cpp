/*
 * mygame.cpp: 本檔案儲游戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為游戲的游戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩游戲的人
	//     等的不耐煩，游戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(IDB_INITIALBACKGROUND);
	tips.LoadBitmap(IDB_INITTIPS);
	Sleep(300);				// 放慢，以便看清楚進度，實際游戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉游戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉游戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	logo.SetTopLeft(0, 0);
	logo.ShowBitmap();
	tips.SetTopLeft(0, 400);
	tips.ShowBitmap();
	
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為游戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
	GotoGameState(ENABLE_GAME_PAUSE);
}

void CGameStateOver::OnBeginState()
{
	counter = 300 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩游戲的人
	//     等的不耐煩，游戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際游戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);

}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為游戲的游戲執行物件，主要的游戲程式都在這里
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28)
{
	maps.push_back(new Lava_Rock_1());
	maps.push_back(new Lava_Rock_2());
	maps.push_back(new ScrollMap());
	bullet = new CBullet();
	boomerangItem = new Boomerang();
	
}

CGameStateRun::~CGameStateRun()
{
	
	delete bullet;
	delete boomerangItem;
	for (int i = 0; i < 3; i++) {
		maps[i]->~Map();
	}
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 3;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 0;
	const int ANIMATION_SPEED = 15;
	mapLevel = 0;
	eraser.Initialize();
	background.SetTopLeft(0,0);				// 設定背景的起始座標
	help.SetTopLeft(0, 300);			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	//hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	points.SetInteger(point);
	points.SetTopLeft(590,0);
	CAudio::Instance()->Play(AUDIO_GANMEBACKGROUND, true);			// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
	vector<Map*>::iterator mapit;

	
	for (mapit = maps.begin(); mapit != maps.end();mapit++) {
		(*mapit)->initialize();
	}
		
	
	
	
	
	
}
void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const int KEY_SPACE = 0x20;  //keyboard空格键
	const int KEY_X = 0x58;
	CEraser* hero = &eraser;
	Map* map = maps[mapLevel];

	if (nChar == KEY_LEFT) {
		eraser.SetMovingLeft(true);
		eraser.SetFacingRight(false);
	}
		
	if (nChar == KEY_RIGHT) {
		eraser.SetMovingRight(true);
		eraser.SetFacingRight(true);
	}
		
	if (nChar == KEY_UP) {
		eraser.SetMovingUp(true);
		eraser.SetFacingUp(true);
	}
		
	if (nChar == KEY_DOWN) {
		eraser.SetMovingDown(true);
		eraser.SetFacingUp(false);
	}
	
	if (!(bullet->IsAlive())) {
		if (nChar == KEY_SPACE) {
			CAudio::Instance()->Play(AUDIO_HEROBULLETEXPLOSION, false);
			bullet->OnKeyDown(nChar, &eraser, map);
				
			
		}
		
		
	}
	
	
	if (!boomerangItem->IsAlive()&&hero->IsGetUseableItem()) {
		if (nChar == KEY_X) {
			CAudio::Instance()->Play(AUDIO_BOOMERANG, false);
			boomerangItem->OnKeyDown(nChar, &eraser, map);
		}
	}
	
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	if (nChar == KEY_LEFT) {
		eraser.SetMovingLeft(false);
		eraser.SetFacingRight(false);
	}
		
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingLeft(true);
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這里
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingRight(false);
}







void CGameStateRun::OnInit()  								// 游戲的初值及圖形設定
{
	
	vector<Map*>::const_iterator mapit;
	vector<AbstractItem*>::const_iterator it;
	for (it = items.begin(); it != items.end(); it++) {
		(*it)->LoadBitmap();
	}
	for (mapit = maps.begin(); mapit != maps.end(); mapit++) {
		(*mapit)->LoadBitmap();
	}
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩游戲的人
	//     等的不耐煩，游戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
								// 載入第i個球的圖形
	
	background.LoadBitmap(IDB_INITIALBACKGROUND);					// 載入背景的圖形
	
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	help.LoadBitmap(IDB_INITTIPS);
	Sleep(300); // 放慢，以便看清楚進度，實際游戲請刪除此Sleep

	points.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid

	CAudio::Instance()->Load(AUDIO_CHEERS, "sounds\\Cheers.mp3");
	CAudio::Instance()->Load(AUDIO_GANMEBACKGROUND, "sounds\\GameBackground.mp3");
	CAudio::Instance()->Load(AUDIO_HEROBELIGHTENED, "sounds\\Belightning.mp3");
	CAudio::Instance()->Load(AUDIO_MONSTERDEATH, "sounds\\Death.mp3");
	CAudio::Instance()->Load(AUDIO_MONSTERLAUGHTER, "sounds\\MonsterLaughter.mp3");
	CAudio::Instance()->Load(AUDIO_HEROBULLETEXPLOSION, "sounds\\Herobulletexplosion.wav");
	CAudio::Instance()->Load(AUDIO_BOSSFIRE, "sounds\\BossFire.mp3");
	CAudio::Instance()->Load(AUDIO_ENCHANCEDENEMY, "sounds\\EnchancedEnemy.mp3");
	CAudio::Instance()->Load(AUDIO_BOOMERANG, "sounds\\Boomerang.mp3");
	CAudio::Instance()->Load(AUDIO_ENEMYDUCK, "sounds\\EnemyDuck.mp3");
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
	eraser.LoadBitmap();
	bullet->LoadBitmap();
	boomerangItem->LoadBitmap();
	oneHeart.LoadBitmap(IDB_ONEHEART, RGB(255, 255, 255));
	twoHeart.LoadBitmap(IDB_TWOHEART, RGB(255, 255, 255));
	threeHeart.LoadBitmap(IDB_THREEHEART, RGB(255, 255, 255));
	atk.LoadBitmap(IDB_ATK, RGB(255, 255, 255));
	shield.LoadBitmap(IDB_SHIELD, RGB(255, 255, 255));
	boomerang.LoadBitmap(IDB_BOOMERANG_1,RGB(0,0,0));
	victory.LoadBitmap(IDB_VICTORY, RGB(255, 255, 255));
}




void CGameStateRun::OnMove()							// 移動游戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	//
	
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	vector<AbstractEnemy*> ::const_iterator iter;
	vector<AbstractItem *>::const_iterator item_iter;
	CEraser* hero = &eraser;
	switch (mapLevel) {
	case 0:
		maps[mapLevel]->OnMove();
		if (hero->IsAlive()) {
			maps[mapLevel]->interact(maps[mapLevel], mapLevel, hero, bullet , boomerangItem);
		}
		else {
			GotoGameState(GAME_STATE_OVER);
			CAudio::Instance()->Stop(AUDIO_GANMEBACKGROUND);

		}
		break;
	case 1:
		maps[mapLevel]->OnMove();
		//hero in the second map
		if (hero->IsAlive()) {
			maps[mapLevel]->interact(maps[mapLevel], mapLevel, hero, bullet, boomerangItem);

		}
		else {
			GotoGameState(GAME_STATE_OVER);
			CAudio::Instance()->Stop(AUDIO_GANMEBACKGROUND);
		}
		break;
	case 2:
		//hero in  the third map
		if (hero->IsAlive()) {
			maps[mapLevel]->interact(maps[mapLevel], mapLevel, hero, bullet, boomerangItem);

		}
		else {
			// if boss or hero died , game over
			GotoGameState(GAME_STATE_OVER);
			CAudio::Instance()->Stop(AUDIO_GANMEBACKGROUND);

		}
		
		break;
	default:
		break;
	}
	
	
	
	
}



void CGameStateRun::OnShow()
{
	//
	//  注意：Show里面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	//background.ShowBitmap();			// 貼上背景圖
	help.ShowBitmap();					// 貼上說明圖
	
	CEraser* hero = &eraser;
	
	switch (mapLevel) {
	case 0 :
		
		//useableItems[0]->OnShow(maps[mapLevel]);
		maps[mapLevel]->OnShow(maps[mapLevel]);
		eraser.OnShow(maps[mapLevel]);
		bullet->OnShow(maps[mapLevel]);
		boomerangItem->OnShow(maps[mapLevel]);
		break;


	case 1:
		
		maps[mapLevel]->OnShow(maps[mapLevel]);
		eraser.OnShow(maps[mapLevel]);
		bullet->OnShow(maps[mapLevel]);
		boomerangItem->OnShow(maps[mapLevel]);
		break;


	case 2:
		
		maps[mapLevel]->OnShow(maps[mapLevel]);
		eraser.OnShow(maps[mapLevel]);
		bullet->OnShow(maps[mapLevel]);
		boomerangItem->OnShow(maps[mapLevel]);
		break;

	default:
		break;
	}
	if (hero->GetHP() == 3) {
		threeHeart.SetTopLeft(0, 450);
		threeHeart.ShowBitmap();
	}
	if (hero->GetHP() == 2) {
		twoHeart.SetTopLeft(0, 450);
		twoHeart.ShowBitmap();
	}
	if (hero->GetHP() == 1) {
		oneHeart.SetTopLeft(0, 450);
		oneHeart.ShowBitmap();
	}
	if (hero->IsATKUp() == true) {
		atk.SetTopLeft(200, 430);
		atk.ShowBitmap();
	}
	if (hero->IsGetShiedl() == true) {
		shield.SetTopLeft(250, 430);
		shield.ShowBitmap();
	}
	if (hero->IsGetUseableItem()) {
		boomerang.SetTopLeft(400, 430);
		boomerang.ShowBitmap();
	}
	if (!maps[2]->GetBossAlive()) {
		victory.SetTopLeft(195,145);
		victory.ShowBitmap();
		//CAudio::Instance()->Play(AUDIO_CHEERS, false);
	}
	points.SetInteger(hero->GetPoint());
	points.ShowBitmap();
	
}

}

