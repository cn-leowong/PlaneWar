#include "StdAfx.h"
#include "Boss.h"
#include "resource.h"

CImageList CBoss::m_Images;

CBoss::CBoss(void)
{
	//随机确定X位置
	m_ptPos.x = rand()%(GAME_WIDTH-BOSS_HEIGHT)+1;//产生的敌机均在  游戏屏幕  上完整显示



	//根据图像索引确定方向
	m_nMotion=1;
	m_ptPos.y=-BOSS_HEIGHT;//初始时刻隐藏敌机
	



	m_nWait=0;
}

CBoss::~CBoss(void)
{
}
BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BOSS,RGB(0,0,0),200,150,1);
}
BOOL CBoss::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>2)//2帧之后 开始发子弹
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.y =m_ptPos.y  +1;
		if(m_ptPos.y>=200)
		{
		m_ptPos.y=200;
		}
		if(m_ptPos.y==200)
		{
		m_ptPos.x=m_ptPos.x+1;
		if(m_ptPos.x>=700)
			m_ptPos.x=-200;
		
		}
		
	}

	if(m_ptPos.y > 400 )
		return FALSE;
	if(m_ptPos.y < -BOSS_HEIGHT)
		return FALSE;
	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBoss::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}