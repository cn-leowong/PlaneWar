#include "StdAfx.h"
#include "Prop.h"
#include "resource.h"

CImageList CProp::m_Images;

CProp::CProp(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-PROP_HEIGHT);//�����ĵл�����  ��Ϸ��Ļ  ��������ʾ

	//���ȷ��ͼ�����������Ƶл����з���
	m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion=1;
	m_ptPos.y=-PROP_HEIGHT;//��ʼʱ�����صл�
	if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	{
		m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+PROP_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand()%4+2;//v��2��5��

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

