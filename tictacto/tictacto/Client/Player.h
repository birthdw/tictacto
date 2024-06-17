#pragma once
class CPlayer 
{
public:
	CPlayer();
	~CPlayer();
public:
	void Initialize() ;
	int Update() ;
	void LateUpdate() ;
	void Render(HDC hDC) ;
	void Release() ;

public:

private:
};

