#include "StdAfx.h"
#include "Enemy3.h"
#include "resource.h"

CImageList CEnemy3::m_Images;

CEnemy3::CEnemy3(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT3);//�����ĵл�����  ��Ϸ��Ļ  ��������ʾ

	//���ȷ��ͼ�����������Ƶл����з���
	m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT3;//��ʼʱ�����صл�
	if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	{
		m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT3;
	}
	//���ȷ���ٶ�
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
	if(m_nWait>2)//2֮֡�� ��ʼ���ӵ�
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