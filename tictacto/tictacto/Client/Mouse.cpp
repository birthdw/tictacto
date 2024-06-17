#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	m_tInfo.fcx = 30.f; 
	m_tInfo.fcy = 30.f; 
}

int CMouse::Update()
{
	POINT pt = {};

	GetCursorPos(&pt);// 마우스의 좌표를 얻어오는 함수. 애는 스크린 기준 좌표를 얻어온다. 
	
	//스크린 좌표에서 클라이언트 좌표로 변환 시켜준다. 
	ScreenToClient(g_hWND, &pt);

	m_tInfo.fx = float(pt.x);
	m_tInfo.fy = float(pt.y);
	return 0;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{

}

void CMouse::Release()
{
}

INFO CMouse::GetPos()
{
	return m_tInfo;
}
