#pragma once
class CObj; 
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	void CollisionCheck(vector<RECT> vec, float x, float y);


};

