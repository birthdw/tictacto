#include "stdafx.h"
#include "Canvas.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::Initialize()
{
	width = 100;
	height = 100;
	half = 50;

	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			PannelPos[i][k].fx = 150+ (k*100);
			PannelPos[i][k].fy = 150 +(i *100);
		}
	}
}

void Canvas::Update()
{

}

void Canvas::LateUpdate()
{
}

void Canvas::Render(HDC dc)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			Rectangle(dc, PannelPos[i][k].fx - half, PannelPos[i][k].fy - half, PannelPos[i][k].fx + half, PannelPos[i][k].fy + half);
		}
	}
}

INFO(*Canvas::GetPos())[3]
{
	return PannelPos;
}

