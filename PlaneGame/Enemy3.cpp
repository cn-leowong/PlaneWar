#include "StdAfx.h"
#include "Enemy3.h"
#include "resource.h"

CImageList CEnemy3::m_Images;

CEnemy3::CEnemy3(void)
{
	//随机确定X位置
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT3);//产生的敌机均在  游戏屏幕  上完整显示

	//随机确定图像索引，控制敌机飞行方向
	m_nImgIndex = rand()%2;

	//根据图像索引确定方向
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT3;//初始时刻隐藏敌机
	if (m_nImgIndex%2!=0)//如果是图像索引是偶数
	{
		m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT3;
	}
	//随机确定速度
	m_V = rand()%2+1;

	m_nWait=0;
}

CEnemy3::~CEnemy3(void)
{
}
BOOL CEnemy3::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_ENEMY3,RGB(0,0,0),150,100,2);
}
BOOL CEnemy3::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>2)//2帧之后 开始发子弹
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if(m_ptPos.y > GAME_HEIGHT+ENEMY_HEIGHT3 )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT3)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy3::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}