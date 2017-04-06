#include "StdAfx.h"
#include "Enemy2.h"
#include "resource.h"

CImageList CEnemy2::m_Images;

CEnemy2::CEnemy2(void)
{
	//随机确定X位置
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT2);//产生的敌机均在  游戏屏幕  上完整显示

	//随机确定图像索引，控制敌机飞行方向
	m_nImgIndex = rand()%2;

	//根据图像索引确定方向
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT2;//初始时刻隐藏敌机
	if (m_nImgIndex%2!=0)//如果是图像索引是偶数
	{
		m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT2;
	}
	//随机确定速度
	m_V = rand()%2+1;

	m_nWait=0;
}

CEnemy2::~CEnemy2(void)
{
}
BOOL CEnemy2::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_ENEMY2,RGB(0,0,0),115,75,2);
}
BOOL CEnemy2::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>5)//5帧之后 开始发子弹
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if(m_ptPos.y > GAME_HEIGHT+ENEMY_HEIGHT2 )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT2)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy2::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}