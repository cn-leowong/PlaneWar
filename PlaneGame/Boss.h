#pragma once
#include "gameobject.h"

class CBoss :public CGameObject
{
public:
	CBoss(void);
	~CBoss(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BOSS_HEIGHT,m_ptPos.y+BOSS_HEIGHT));//�����εл�ͼƬ
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int BOSS_HEIGHT = 150;
	static CImageList m_Images;
	int    m_nMotion;
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int    m_nWait;//������ʱ
};
