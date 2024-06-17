#pragma once

class Canvas;
class CMouse;

enum TYPE { NONE, PLAYER, AI,  TYPEEND };

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(); 
	void Update(); 
	void LateUpdate();
	void Render();
	void Release(); 


public:
	bool MouseCol();

public:
	TYPE CheckWin();
	bool CheckFull();
	int MinMax(int depth, bool p);
	pair<int, int> FindBestMark(int depth, bool p);

private:

	bool PlayerTurn = true;
	TYPE eType;

	HDC m_hDC;
	CMouse* pMouse;
	Canvas* pCanvas;
	INFO PlayerPos[3][3];
	INFO AiPos[3][3];
	pair<bool,TYPE> MarkCheck[3][3];
	vector<pair<int, int>> vecPair;



};

