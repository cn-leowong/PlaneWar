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
		return CRect(m_ptPos,CPoint(m_ptPos.x+PROP_HEIGHT,m_ptPos.y+PROP_HEIGHT));//正方形敌机图片
	}

	int GetMontion() const
	{
		return m_nMotion;
	}

private:
	static const int PROP_HEIGHT = 50;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
};
