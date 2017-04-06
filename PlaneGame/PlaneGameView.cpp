// PlaneGameView.cpp : CPlaneGameView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
	//背景音乐
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
	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
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
	//产生主角(战机)
	m_pMe = new CMyPlane;

	//启动游戏
   SetTimer(1,25,NULL);

	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//分关卡绘制背景
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
	
	
	//计时器
	i++;
	j=i/40;
	
	pMemDC->TextOutW(30,20,_T("定时器"));
	CString s;
	s.Format(_T("%d"),j);
	pMemDC->TextOutW(30,40,s);
	//积分功能
	CString r;
	r.Format(_T("积分：%d"),rank*10);
	pMemDC->TextOutW(30,530,r);
	//设置关卡
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



	//显示关卡和tips
	CString g;
	g.Format(_T("关卡：%d/10"),round);
	pMemDC->TextOutW(700,20, g);
	if(round==1)
	{
	pMemDC->TextOutW(450,500, _T("tips：按shift键暂停 按回车键开启无敌模式"));
	
	}
	else if(round==2)
	{
	pMemDC->TextOutW(450,460, _T("tips：进入第2关 战机加一排子弹"));
	pMemDC->TextOutW(450,480, _T("tips：进入第2关 出现黄色敌机~"));
	
	}
	else if(round==3)
	{
	pMemDC->TextOutW(450,460, _T("tips:进入第3关 再加一排子弹 出现蓝色敌机"));
	pMemDC->TextOutW(450,480, _T("tips:打掉蓝色战机生命值+1！"));
	
	}
	else 
	{
	pMemDC->TextOutW(450,460, _T("tips:开始出现蓝色道具！"));
	pMemDC->TextOutW(450,480, _T("tips:打掉道具增加50积分打掉蓝色战机生命值+1！"));
	
	}
	//显示血条和生命值
	CString xue;
	xue.Format(_T("生命值：%d"),x);
	pMemDC->TextOutW(30,550, xue);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,0,0));
	pMemDC->SelectObject(&brush);
	pMemDC->Rectangle(30,570,(x+1)*30,590);
	//绘制我方战机
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	}
	else
	{   
		
	pMemDC->TextOutW(400,300,_T("游戏结束 按TAB键复活"));
			
	}
	
	//绘制 导弹、爆炸、敌机123、子弹,boss
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
	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
		UpdateFrame(m_pMemDC);
	//刷新游戏帧画面: 在内存DC上绘图
		static int nCreator = rand() %5+10,nCreator2,nCreator3,nCreator4;

//随机产生敌机和道具
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

	//检测四个方向键，移动战机
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
	
	//产生战机导弹
	if(GetKey(VK_SPACE)==1)//按下了空格键
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


	//敌机1发射子弹

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //敌机在战机前面
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //敌机在战机后面
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	
	//敌机2发射子弹
	CPoint PlanePt2 = m_pMe->GetPoint();
	for(POSITION ePos2=m_ObjList[enEnemy2].GetHeadPosition();ePos2!=NULL;)
	{
          CEnemy2* pEnemy2 = (CEnemy2*)m_ObjList[enEnemy2].GetNext(ePos2);
		 
		  CPoint  ePt2 = pEnemy2->GetPoint();

		  BOOL by2=FALSE;

		  //敌机在战机前面
		  if(pEnemy2->GetMontion()==1 && ePt2.y<PlanePt2.y)
		         by2=  TRUE;
		  //敌机在战机后面
		  if(pEnemy2->GetMontion()==-1 && ePt2.y>PlanePt2.y)
				 by2=  TRUE;	

		  if(by2 && ePt2.x >= PlanePt2.x && ePt2.x<PlanePt2.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt2.x+100,ePt2.y+10,pEnemy2->GetMontion()));
			   m_ObjList[enBall].AddTail(new CBall(ePt2.x+300,ePt2.y+10,pEnemy2->GetMontion()));
		  }
	}
	//敌机3发射子弹
	CPoint PlanePt3 = m_pMe->GetPoint();
	for(POSITION ePos3=m_ObjList[enEnemy3].GetHeadPosition();ePos3!=NULL;)
	{
          CEnemy3* pEnemy3 = (CEnemy3*)m_ObjList[enEnemy3].GetNext(ePos3);
		 
		  CPoint  ePt3 = pEnemy3->GetPoint();

		  BOOL by2=FALSE;

		  //敌机在战机前面
		  if(pEnemy3->GetMontion()==1 && ePt3.y<PlanePt3.y)
		         by2=  TRUE;
		  //敌机在战机后面
		  if(pEnemy3->GetMontion()==-1 && ePt3.y>PlanePt3.y)
				 by2=  TRUE;	

		  if(by2 && ePt3.x >= PlanePt3.x && ePt3.x<PlanePt3.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt3.x+100,ePt3.y+10,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x+300,ePt3.y+30,pEnemy3->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt3.x+500,ePt3.y+10,pEnemy3->GetMontion()));
		  }
	}
	//boss发射子弹
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
	//敌机子弹炸掉战机
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
			
			//删除子弹
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);
			if(x==0)

			{
			//删除战机
			delete m_pMe;
			m_pMe=NULL;
			break;}

			
		}

	}

	//战机导弹炸掉敌机1
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
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				break;

			}
		}
	}
     //战机导弹炸掉敌机2
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

				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				if(dj>=10)
				//删除敌机 //加一条命
				{
				x++;
				m_ObjList[enEnemy2].RemoveAt(ePos2);
				delete pEnemy;
				dj=0;
				break;}

			}
		}
	}
	 //战机导弹炸掉敌机3
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
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				if(dj1>=30)
				//删除敌机
				{m_ObjList[enEnemy3].RemoveAt(ePos2);
				delete pEnemy;
				dj1=0;
				break;}

			}
		}
	}
	//战机导弹炸掉道具
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
				
				rank=rank+5;//道具加50积分
			
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				//删除敌机
				m_ObjList[prop].RemoveAt(ePos2);
				delete pEnemy;
				break;

			}
		}
	}

	 //战机导弹炸掉boss
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
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
 				delete pBomb;
				//删除敌机
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

	// TODO:  在此添加您专用的创建代码

    i=1;//计时
	rank=0;//积分
	round=1;//关卡
	x=10;//血量
	dj=0;//敌机2的抗击打能力
	dj1=0;//敌机3的抗击打能力
	dj2=0;//boss的抗击打能力
	return 0;
}


void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//暂停功能
	if (nChar==VK_SHIFT)
		KillTimer(1);
	//无敌模式
	if(nChar==VK_RETURN)
		x=99999;
	//复活功能
		if(nChar==VK_TAB)
		{
		m_pMe = new CMyPlane;
		x=10;
		}
 
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
