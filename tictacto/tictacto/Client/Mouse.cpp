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

	GetCursorPos(&pt);// ���콺�� ��ǥ�� ������ �Լ�. �ִ� ��ũ�� ���� ��ǥ�� ���´�. 
	
	//��ũ�� ��ǥ���� Ŭ���̾�Ʈ ��ǥ�� ��ȯ �����ش�. 
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
