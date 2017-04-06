#include "StdAfx.h"
#include "Enemy2.h"
#include "resource.h"

CImageList CEnemy2::m_Images;

CEnemy2::CEnemy2(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT2);//�����ĵл�����  ��Ϸ��Ļ  ��������ʾ

	//���ȷ��ͼ�����������Ƶл����з���
	m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT2;//��ʼʱ�����صл�
	if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	{
		m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT2;
	}
	//���ȷ���ٶ�
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
	if(m_nWait>5)//5֮֡�� ��ʼ���ӵ�
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