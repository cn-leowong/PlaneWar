// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"
#include<windows.h>
#include<MMSystem.h>  
#pragma   comment(lib,   "winmm.lib")  

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bomb.h"
#include "Ball.h"
#include"Prop.h"
#include"Boss.h"
#include "Explosion.h"
#include <atlimage.h>
#include "resource.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
	//��������
	 sndPlaySoundW(L"bgm.wav", SND_ASYNC);

}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);
	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CEnemy2::LoadImage();
	CEnemy3::LoadImage();
	CExplosion::LoadImage();
	CProp::LoadImage();
	CBoss::LoadImage();
	//��������(ս��)
	m_pMe = new CMyPlane;

	//������Ϸ
   SetTimer(1,25,NULL);

	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�ֹؿ����Ʊ���
	CRect rect;
	GetClientRect(&rect);
	CDC memdc;
	memdc.CreateCompatibleDC(pMemDC);
	CBitmap bitmap;
	BITMAP bitmap1;
	
	if(round%3==1)
	{
	bitmap.LoadBitmapW(IDB_BG);
	bitmap.GetBitmap(&bitmap1);
	memdc.SelectObject(&bitmap);
	pMemDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, bitmap1.bmWidth, bitmap1.bmHeight, SRCCOPY);
	
	 

	}
	if(round%3==2)
	{
		
    bitmap.LoadBitmapW(IDB_BG2);
	bitmap.GetBitmap(&bitmap1);
	memdc.SelectObject(&bitmap);
	pMemDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, bitmap1.bmWidth, bitmap1.bmHeight, SRCCOPY);
	 
	}
	if(round%3==0)
	{
		
    bitmap.LoadBitmapW(IDB_BG3);
	bitmap.GetBitmap(&bitmap1);
	memdc.SelectObject(&bitmap);
	pMemDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, bitmap1.bmWidth, bitmap1.bmHeight, SRCCOPY);
	 
	}
	
	
	//��ʱ��
	i++;
	j=i/40;
	
	pMemDC->TextOutW(30,20,_T("��ʱ��"));
	CString s;
	s.Format(_T("%d"),j);
	pMemDC->TextOutW(30,40,s);
	//���ֹ���
	CString r;
	r.Format(_T("���֣�%d"),rank*10);
	pMemDC->TextOutW(30,530,r);
	//���ùؿ�
	if(rank*10<200&&rank*10>=0)
	{round=1;}
	else if(rank*10>200&&rank*10<=400)
	{round=2;}
	else if(rank*10>400&&rank*10<=600)
	{round=3;}
	else if(rank*10>600&&rank*10<=800)
	{round=4;}
	else if(rank*10>800&&rank*10<=1000)
	{round=5;}
	else if(rank*10>1000&&rank*10<=1200)
	{round=6;}
	else if(rank*10>1200&&rank*10<=1400)
	{round=7;}
	else if(rank*10>1400&&rank*10<=1600)
	{round=8;}
	else if(rank*10>1600&&rank*10<=1800)
	{round=9;}
	else if(rank*10>1800)
	{round=10;}



	//��ʾ�ؿ���tips
	CString g;
	g.Format(_T("�ؿ���%d/10"),round);
	pMemDC->TextOutW(700,20, g);
	if(round==1)
	{
	pMemDC->TextOutW(450,500, _T("tips����shift����ͣ ���س��������޵�ģʽ"));
	
	}
	else if(round==2)
	{
	pMemDC->TextOutW(450,460, _T("tips�������2�� ս����һ���ӵ�"));
	pMemDC->TextOutW(450,480, _T("tips�������2�� ���ֻ�ɫ�л�~"));
	
	}
	else if(round==3)
	{
	pMemDC->TextOutW(450,460, _T("tips:�����3�� �ټ�һ���ӵ� ������ɫ�л�"));
	pMemDC->TextOutW(450,480, _T("tips:�����ɫս������ֵ+1��"));
	
	}
	else 
	{
	pMemDC->TextOutW(450,460, _T("tips:��ʼ������ɫ���ߣ�"));
	pMemDC->TextOutW(450,480, _T("tips:�����������50���ִ����ɫս������ֵ+1��"));
	
	}
	//��ʾѪ��������ֵ
	CString xue;
	xue.Format(_T("����ֵ��%d"),x);
	pMemDC->TextOutW(30,550, xue);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,0,0));
	pMemDC->SelectObject(&brush);
	pMemDC->Rectangle(30,570,(x+1)*30,590);
	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	}
	else
	{   
		
	pMemDC->TextOutW(400,300,_T("��Ϸ���� ��TAB������"));
			
	}
	
	//���� ��������ը���л�123���ӵ�,boss
	for(int i=0;i<8;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	// 
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
		UpdateFrame(m_pMemDC);
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
		static int nCreator = rand() %5+10,nCreator2,nCreator3,nCreator4;

//��������л��͵���
		if(i==4000)
		m_ObjList[boss].AddTail(new CBoss);
	if (nCreator <= 0)
	{
		nCreator = rand() % 5 + 10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
		if(round>=4)
			m_ObjList[enEnemy].AddTail(new CEnemy);
		if(round>=5)
		{
			m_ObjList[enEnemy].AddTail(new CEnemy);
		}
		if(round==10)
		{
		m_ObjList[enEnemy].AddTail(new CEnemy);
		m_ObjList[enEnemy].AddTail(new CEnemy);
		m_ObjList[enEnemy].AddTail(new CEnemy);
	
		}
	}
	nCreator--;
	nCreator2 = rand() % 200 + 5;
	if (round>=2)
	{

		if (nCreator2 == 15)
		{
			m_ObjList[enEnemy2].AddTail(new CEnemy2);
		}
	}
	nCreator3 = rand() % 200 + 5;
	if (round>=3)
	{

		if (nCreator3 == 15)
		{
			m_ObjList[enEnemy3].AddTail(new CEnemy3);
			m_ObjList[prop].AddTail(new CProp);
		}
	}
	nCreator4 = rand() % 200 + 5;
	if (round>=4)
	{

		if (nCreator4 == 15)
		{
			m_ObjList[prop].AddTail(new CProp);
		}
	}
		
	if(m_pMe==NULL)
		return;

	//����ĸ���������ƶ�ս��
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);
	}
	
	//����ս������
	if(GetKey(VK_SPACE)==1)//�����˿ո��
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+10,pt.y+10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+30,pt.y+10));
			if(round==2)
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+20,pt.y+10));
			if(round>=3)
			{
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 50, pt.y - 30));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x - 10, pt.y - 30));
            }
			

		}
	}


	//�л�1�����ӵ�

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	
	//�л�2�����ӵ�
	CPoint PlanePt2 = m_pMe->GetPoint();
	for(POSITION ePos2=m_ObjList[enEnemy2].GetHeadPosition();ePos2!=NULL;)
	{
          CEnemy2* pEnemy2 = (CEnemy2*)m_ObjList[enEnemy2].GetNext(ePos2);
		 
		  CPoint  ePt2 = pEnemy2->GetPoint();

		  BOOL by2=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy2->GetMontion()==1 && ePt2.y<PlanePt2.y)
		         by2=  TRUE;
		  //�л���ս������
		  if(pEnemy2->GetMontion()==-1 && ePt2.y>PlanePt2.y)
				 by2=  TRUE;	

		  if(by2 && ePt2.x >= PlanePt2.x && ePt2.x<PlanePt2.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt2.x+100,ePt2.y+10,pEnemy2->GetMontion()));
			   m_ObjList[enBall].AddTail(new CBall(ePt2.x+300,ePt2.y+10,pEnemy2->GetMontion()));
		  }
	}
	//�л�3�����ӵ�
	CPoint PlanePt3 = m_pMe->GetPoint();
	for(POSITION ePos3=m_ObjList[enEnemy3].GetHeadPosition();ePos3!=NULL;)
	{
          CEnemy3* pEnemy3 = (CEnemy3*)m_ObjList[enEnemy3].GetNext(ePos3);
		 
		  CPoint  ePt3 = pEnemy3->GetPoint();

		  BOOL by2=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy3->GetMontion()==1 && ePt3.y<PlanePt3.y)
		         by2=  TRUE;
		  //�л���ս������
		  if(pEnemy3->GetMontion()==-1 && ePt3.y>PlanePt3.y)
				 by2=  TRUE;	

		  if(by2 && ePt3.x >= PlanePt3.x && ePt3.x<PlanePt3.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt3.x+100,ePt3.y+10,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x+300,ePt3.y+30,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x+500,ePt3.y+10,pEnemy3->GetMontion()));
		  }
	}
	//boss�����ӵ�
	CPoint PlanePt4 = m_pMe->GetPoint();
	for(POSITION ePos3=m_ObjList[boss].GetHeadPosition();ePos3!=NULL;)
	{
          CBoss* pEnemy3 = (CBoss*)m_ObjList[boss].GetNext(ePos3);
		 
		  CPoint  ePt3 = pEnemy3->GetPoint();
		  if( ePt3.x >= PlanePt4.x && ePt3.x<PlanePt4.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt3.x+200,ePt3.y+155,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x+250,ePt3.y+200,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x+300,ePt3.y+250,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x,ePt3.y+155,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x-50,ePt3.y+200,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x-100,ePt3.y+250,pEnemy3->GetMontion()));
		  }
	}
	//�л��ӵ�ը��ս��
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			x--;
			
			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);
			if(x==0)

			{
			//ɾ��ս��
			delete m_pMe;
			m_pMe=NULL;
			break;}

			
		}

	}

	//ս������ը���л�1
	POSITION mPos1=NULL,mPos2=NULL;
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				rank++;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				break;

			}
		}
	}
     //ս������ը���л�2
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy2].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy2* pEnemy = (CEnemy2*)m_ObjList[enEnemy2].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				
				rank++;
				dj++;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				if(dj>=10)
				//ɾ���л� //��һ����
				{
				x++;
				m_ObjList[enEnemy2].RemoveAt(ePos2);
				delete pEnemy;
				dj=0;
				break;}

			}
		}
	}
	 //ս������ը���л�3
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy3].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy3* pEnemy = (CEnemy3*)m_ObjList[enEnemy3].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				
				rank++;
				dj1++;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				if(dj1>=30)
				//ɾ���л�
				{m_ObjList[enEnemy3].RemoveAt(ePos2);
				delete pEnemy;
				dj1=0;
				break;}

			}
		}
	}
	//ս������ը������
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[prop].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CProp* pEnemy = (CProp*)m_ObjList[prop].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				
				rank=rank+5;//���߼�50����
			
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				//ɾ���л�
				m_ObjList[prop].RemoveAt(ePos2);
				delete pEnemy;
				break;

			}
		}
	}

	 //ս������ը��boss
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[boss].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CBoss* pEnemy = (CBoss*)m_ObjList[boss].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				dj2++;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
 				delete pBomb;
				//ɾ���л�
				if(dj2>=20)
				{
				m_ObjList[boss].RemoveAt(ePos2);
				delete pEnemy;
				break;
				}

			}
		}
	}
	
	CView::OnTimer(nIDEvent);
}




int CPlaneGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

    i=1;//��ʱ
	rank=0;//����
	round=1;//�ؿ�
	x=10;//Ѫ��
	dj=0;//�л�2�Ŀ���������
	dj1=0;//�л�3�Ŀ���������
	dj2=0;//boss�Ŀ���������
	return 0;
}


void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	//��ͣ����
	if (nChar==VK_SHIFT)
		KillTimer(1);
	//�޵�ģʽ
	if(nChar==VK_RETURN)
		x=99999;
	//�����
		if(nChar==VK_TAB)
		{
		m_pMe = new CMyPlane;
		x=10;
		}
 
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
