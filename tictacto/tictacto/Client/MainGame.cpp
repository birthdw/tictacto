#include "stdafx.h"
#include "MainGame.h"
#include "Mouse.h"
#include "Canvas.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{

	m_hDC = GetDC(g_hWND);

	pMouse = new CMouse;
	pMouse->Initialize();

	pCanvas = new Canvas;
	pCanvas->Initialize();

	PlayerTurn = true;
	eType = NONE;


	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			PlayerPos[i][k].fx = -1;
			AiPos[i][k].fx = -1;
			MarkCheck[i][k] = pair<bool, TYPE>(false, NONE);
		}
	}


}

void CMainGame::Update()
{
	pMouse->Update();
	pCanvas->Update();

	if (eType == TYPEEND || eType == PLAYER || eType == AI)
	{
		Sleep(3000);
		DestroyWindow(g_hWND);
	}

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000 && PlayerTurn == true)
	{
		if (MouseCol() == true)
		{
			PlayerTurn = false;
		}

	}

	if (PlayerTurn == false && CheckFull()==false)
	{
		INFO(*ptr)[3] = pCanvas->GetPos();
		pair<int, int> PosCom = FindBestMark(0, PlayerTurn);
		AiPos[PosCom.first][PosCom.second] = ptr[PosCom.first][PosCom.second];
		MarkCheck[PosCom.first][PosCom.second] = pair<bool, TYPE>(true, AI);
		PlayerTurn = true;
	}

	eType = TYPE::NONE;
}

void CMainGame::LateUpdate()
{
	pMouse->LateUpdate();
	pCanvas->LateUpdate();

	if (eType == TYPE::NONE)
		CheckWin();


}

void CMainGame::Render()
{

	Rectangle(m_hDC, 0, 0, WINCX, WINCY);


	if (eType == TYPE::NONE)
	{
		if (PlayerTurn == true)
		{
			TCHAR szBuf[128] = L"Click Where You Want";
			TextOut(m_hDC, 420, 250, szBuf, lstrlen(szBuf));
		}
	}
	else if (eType == TYPE::PLAYER)
	{
		TCHAR szBuf[128] = L"Player WIN";
		TextOut(m_hDC, 450, 250, szBuf, lstrlen(szBuf));
	}
	else if (eType == TYPE::AI)
	{
		TCHAR szBuf[128] = L"AI WIN";
		TextOut(m_hDC, 450, 250, szBuf, lstrlen(szBuf));
	}

	
	if (CheckFull()==true)
	{
		TCHAR szBuf[128] = L"DRAW GAME";
		TextOut(m_hDC, 450, 250, szBuf, lstrlen(szBuf));
		eType = TYPE::TYPEEND;
	}


	pCanvas->Render(m_hDC);


	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			if (PlayerPos[i][k].fx < 0)
				continue;

			Ellipse(m_hDC, PlayerPos[i][k].fx - 50, PlayerPos[i][k].fy - 50, PlayerPos[i][k].fx + 50, PlayerPos[i][k].fy + 50);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			if (AiPos[i][k].fx < 0)
				continue;
			MoveToEx(m_hDC, AiPos[i][k].fx - 50, AiPos[i][k].fy - 50, NULL);
			LineTo(m_hDC, AiPos[i][k].fx + 50, AiPos[i][k].fy + 50);
			MoveToEx(m_hDC, AiPos[i][k].fx + 50, AiPos[i][k].fy - 50, NULL);
			LineTo(m_hDC, AiPos[i][k].fx - 50, AiPos[i][k].fy + 50);
		}
	}

	

}

void CMainGame::Release()
{
	ReleaseDC(g_hWND, m_hDC);
	delete pMouse;
	delete pCanvas;

}

bool CMainGame::MouseCol()
{

	INFO(*ptr)[3] = pCanvas->GetPos();
	INFO pt = pMouse->GetPos();

	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			if (ptr[i][k].fx - 50 < pt.fx && ptr[i][k].fx + 50 > pt.fx &&
				ptr[i][k].fy - 50 < pt.fy && ptr[i][k].fy + 50 > pt.fy)
			{
				if (MarkCheck[i][k].first == true)
					continue;
				PlayerPos[i][k] = ptr[i][k];
				MarkCheck[i][k] = pair<bool, TYPE>(true, PLAYER);
				return true;
			}
		}
	}

	return false;
}

TYPE CMainGame::CheckWin()
{
	eType = NONE;

	for (int i = 0; i < 3; ++i)
	{
		if (MarkCheck[i][0].second == PLAYER && MarkCheck[i][1].second == PLAYER && MarkCheck[i][2].second == PLAYER)
			eType = TYPE::PLAYER;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (MarkCheck[0][i].second == PLAYER && MarkCheck[1][i].second == PLAYER && MarkCheck[2][i].second == PLAYER)
			eType = TYPE::PLAYER;
	}

	if (MarkCheck[0][0].second == PLAYER && MarkCheck[1][1].second == PLAYER && MarkCheck[2][2].second == PLAYER)
		eType = TYPE::PLAYER;
	if (MarkCheck[0][2].second == PLAYER && MarkCheck[1][1].second == PLAYER && MarkCheck[2][0].second == PLAYER)
		eType = TYPE::PLAYER;

	///////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 3; ++i)
	{
		if (MarkCheck[i][0].second == AI && MarkCheck[i][1].second == AI && MarkCheck[i][2].second == AI)
			eType = TYPE::AI;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (MarkCheck[0][i].second == AI && MarkCheck[1][i].second == AI && MarkCheck[2][i].second == AI)
			eType = TYPE::AI;
	}

	if (MarkCheck[0][0].second == AI && MarkCheck[1][1].second == AI && MarkCheck[2][2].second == AI)
		eType = TYPE::AI;
	if (MarkCheck[0][2].second == AI && MarkCheck[1][1].second == AI && MarkCheck[2][0].second == AI)
		eType = TYPE::AI;


	return eType;


}

bool CMainGame::CheckFull()
{
	int cnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			if (MarkCheck[i][k].first == true)
				++cnt;
		}
	}
	if (cnt == 9)
	{
		return true;
	}
	else
		return false;
}


int CMainGame::MinMax(int depth, bool p)
{
	if (CheckWin() == PLAYER)
		return -100 + depth;
	else if (CheckWin() == AI)
		return 100 - depth;
	if (CheckFull()==true)
		return 0;
	if (p == false)//ai턴
	{
		int bestscore = -10000;
		for (int i = 0; i < 3; ++i)
		{
			for (int k = 0; k < 3; ++k)
			{
				if (MarkCheck[i][k].first == false)
				{
					MarkCheck[i][k].first = true;
					MarkCheck[i][k].second = AI;
					bestscore = max(bestscore, MinMax(depth + 1, !p));
					MarkCheck[i][k].first = false;
					MarkCheck[i][k].second = NONE;
				}
			}
		}
		return bestscore;
	}
	else //플레이어 턴
	{
		int bestscore = 10000;
		for (int i = 0; i < 3; ++i)
		{
			for (int k = 0; k < 3; ++k)
			{
				if (MarkCheck[i][k].first == false)
				{
					MarkCheck[i][k].first = true;
					MarkCheck[i][k].second = PLAYER;
					bestscore = min(bestscore, MinMax(depth + 1, !p));
					MarkCheck[i][k].first = false;
					MarkCheck[i][k].second = NONE;
				}
			}
		}
		return bestscore;
	}
}


pair<int, int> CMainGame::FindBestMark(int depth, bool p)
{
	pair<int, int> res;
	int BestScore = -10000;

	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			if (MarkCheck[i][k].first == false)
			{
				MarkCheck[i][k].first = true;
				MarkCheck[i][k].second = AI;
				int markvalue = MinMax(0, true);
				if (BestScore < markvalue)
				{
					BestScore = markvalue;
					res = pair<int, int>(i, k);
				}
				MarkCheck[i][k].first = false;
				MarkCheck[i][k].second = NONE;
			}
		}
	}



	return res;
}

