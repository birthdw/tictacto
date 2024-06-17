#pragma once
class Canvas
{
public:
	Canvas();
	~Canvas();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC dc);

public:

	INFO(*GetPos())[3];


public:
	int width;
	int height;
	int half;
	INFO PannelPos[3][3];
};



