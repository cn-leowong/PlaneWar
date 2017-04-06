#include "StdAfx.h"
#include "Prop.h"
#include "resource.h"

CImageList CProp::m_Images;

CProp::CProp(void)
{
	//随机确定X位置
	m_ptPos.x = rand()%(GAME_WIDTH-PROP_HEIGHT);//产生的敌机均在  游戏屏幕  上完整显示

	//随机确定图像索引，控制敌机飞行方向
	m_nImgIndex = rand()%2;

	//根据图像索引确定方向
	m_nMotion=1;
	m_ptPos.y=-PROP_HEIGHT;//初始时刻隐藏敌机
	if (m_nImgIndex%2!=0)//如果是图像索引是偶数
	{
		m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+PROP_HEIGHT;
	}
	//随机确定速度
	m_V = rand()%4+2;//v（2，5）

}

CProp::~CProp(void)
{
}
BOOL CProp::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_PROP,RGB(0,0,0),50,50,2);
}
BOOL CProp::Draw(CDC* pDC,BOOL bPause)
{

	
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if(m_ptPos.y > GAME_HEIGHT+PROP_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -PROP_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

