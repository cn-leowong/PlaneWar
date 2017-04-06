#pragma once
#include "gameobject.h"

class CProp :public CGameObject
{
public:
	CProp(void);
	~CProp(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+PROP_HEIGHT,m_ptPos.y+PROP_HEIGHT));//�����εл�ͼƬ
	}

	int GetMontion() const
	{
		return m_nMotion;
	}

private:
	static const int PROP_HEIGHT = 50;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
};
