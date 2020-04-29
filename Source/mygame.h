﻿/*
 * mygame.h: 本檔案儲游戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/
#include <vector>
#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "Lava_Rock_1.h"
#include "Lava_Rock_2.h"
#include "CBullet.h"
#include "Enemy.h"
#include "Item.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為游戲的游戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 游戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的游戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
	};

	///////////////////////////////////////////////////////////////////////////////
	//Practise
	//////////////////////////////////////////////////////////////////////////////
	/*
	
	class CPractice {
	public: 
		CPractice();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int x, y;
	};
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitMap();
		void OnShow();
	protected:
		CMovingBitmap green, blue;
		int map[4][5];
		const int X, Y;
		const int MH, MW; //地图的宽和高

	};


	
	
	*/
	














	/////////////////////////////////////////////////////////////////////////////
	// 這個class為游戲的游戲執行物件，主要的游戲程式都在這里
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////
	
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 游戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動游戲元素
		void OnShow();									// 顯示這個狀態的游戲畫面
	private:
		const int		NUMBALLS;	// 球的總數
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明
		int				countDownTime = 0;
		//CBall			*ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		CEraser			eraser;		// 拍子
		CInteger		hits_left;	// 剩下的撞擊數
		CInteger		points;
		//CBouncingBall   bball;		// 反覆彈跳的球
		int				mapLevel;
		int				invicibleCounter = 0;
		int				delayCounter = 0;
		int				point = 0;
		CBullet			*bullet;
		vector<Map *> maps;
		vector<AbstractEnemy*> enemies;
		vector<AbstractItem*>	items;
		CMovingBitmap	oneHeart;
		CMovingBitmap	twoHeart;
		CMovingBitmap	threeHeart;
		//Hero			hero;
		//Character		*character;

		///////////////////////////////////////////////////////
		//practise
		///////////////////////////////////////////////////////
		/*
		CMovingBitmap practice;
		CMovingBitmap practice_2;
		CMovingBitmap borader;
		int picX, picY;
		CPractice c_practice;
		CGameMap gamemap;
		*/
		

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為游戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動游戲元素
		void OnShow();									// 顯示這個狀態的游戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}