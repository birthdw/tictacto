#pragma once

class CMouse 
{
public:
	CMouse();
	~CMouse();
public:
	void Initialize() ;
	int Update() ;
	void LateUpdate() ;
	void Render(HDC hDC) ;
	void Release() ;

	INFO GetPos();



	INFO m_tInfo;
};

