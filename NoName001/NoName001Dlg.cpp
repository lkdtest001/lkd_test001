
// NoName001Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NoName001.h"
#include "NoName001Dlg.h"
#include "afxdialogex.h"
#include "CRadarCommonPara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNoName001Dlg 对话框


CNoName001Dlg::CNoName001Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoName001Dlg::IDD, pParent)
	,m_nIndexLvl(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CNoName001Dlg::~CNoName001Dlg()
{
	for (int i = 0; i < XLINEPICNUM; i++)
	{
		for(int j = 0; j < YLINEPICNUM; j++)
		{
			if (m_pImgBk[i][j]!=NULL)
			{
				delete m_pImgBk[i][j];
				m_pImgBk[i][j] = NULL;
			}
		}
	}
}

void CNoName001Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNoName001Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
//	ON_STN_CLICKED(IDC_STATIC_RADAR, &CNoName001Dlg::OnStnClickedStaticRadar)
//	ON_STN_DBLCLK(IDC_STATIC_RADAR, &CNoName001Dlg::OnStnDblclickStaticRadar)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()


// CNoName001Dlg 消息处理程序

BOOL CNoName001Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOW);

	// TODO: 在此添加额外的初始化代码
	((CStatic *)GetDlgItem(IDC_STATIC_RADAR))->MoveWindow(405, 0, 600, 450);
	((CStatic *)GetDlgItem(IDC_STATIC_VIDEO))->MoveWindow(0, 0, 400, 300);
	((CButton *)GetDlgItem(IDC_BUTTON_DRAW))->MoveWindow(1007, 20, 40, 30);
	for (int i = 0; i < XLINEPICNUM; i++)
	{
		for(int j = 0; j < YLINEPICNUM; j++)
		{
			m_pImgBk[i][j] = NULL;
		}
	}
	m_nYTiles[14] = 8;
	m_nYTiles[15] = 18;
	m_nYTiles[16] = 35;
	m_nYTiles[17] = 71;
	m_nYTiles[18] = 142;
	m_nYTiles[19] = 284;
	m_nYTiles[20] = 568;
	m_nYTiles[21] = 1136;

	for(int i = 0; i < 22; i++)
	{
		m_dResolutions[i] = 20037508.3427892f * 2 / 256 / (double)pow(2.f,i);
	}
	m_nIndexLvl = 14;

	
	m_GPSCentre.dLatitude = 30.50608;
	m_GPSCentre.dLongitude = 114.43673;
	m_GPSCentre.dHeight = 0.f;
	m_GPSCentre.CalculatePos();

	for (int i = 0; i < XLINEPICNUM; i++)
	{
		for(int j = 0; j < YLINEPICNUM; j++)
		{
			m_pImgBk[i][j] = new CImage;
		}
	}
// 	m_pImgBk[0]->Load(_T("res\\53984.png"));
// 	if ( m_pImgBk[0]->IsNull() ) // 图片加载失败
// 	{
// 		delete m_pImgBk[0];
// 		m_pImgBk[0] = NULL;
// 	} 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNoName001Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
	DrawBkg(m_GPSCentre, m_nIndexLvl);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNoName001Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNoName001Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}

void CNoName001Dlg::DrawBkg(GPSPOSITION gPos, int nLvl /* = 14 */)
{

	for (int i = 0; i < XLINEPICNUM; i++)
	{
		for(int j = 0; j < YLINEPICNUM; j++)
		{
			if (m_pImgBk[i][j]!=NULL)
			{
				delete m_pImgBk[i][j];
				m_pImgBk[i][j] = NULL;
			}

			m_pImgBk[i][j] = new CImage;
		}
	}

	RECT rct;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_RADAR);
	pWnd->GetWindowRect(&rct);
	ScreenToClient(&rct);

	double dx, dy;
	Lonlat2Mercator(gPos, dx, dy);

	VIEWBOUNDS vb;
	vb.dleft = dx-(m_dResolutions[m_nIndexLvl]*(rct.right - rct.left)/2);
	vb.dright = dx+(m_dResolutions[m_nIndexLvl]*(rct.right - rct.left)/2);
	vb.dtop = dy+(m_dResolutions[m_nIndexLvl]*(rct.bottom - rct.top)/2);
	vb.dbottom = dy-(m_dResolutions[m_nIndexLvl]*(rct.bottom - rct.top)/2);

	int nStartX = floor(((vb.dleft - MAP_BOUNDS_LEFT) / m_dResolutions[m_nIndexLvl]) / PNGSIZE);
	int nStartY = floor(((MAP_BOUNDS_TOP - vb.dtop) / m_dResolutions[m_nIndexLvl]) / PNGSIZE) - m_nYTiles[m_nIndexLvl];
	int nEndX = floor(((vb.dright - MAP_BOUNDS_LEFT) / m_dResolutions[m_nIndexLvl]) / PNGSIZE);
	int nEndY = floor(((MAP_BOUNDS_TOP - vb.dbottom) / m_dResolutions[m_nIndexLvl]) / PNGSIZE) - m_nYTiles[m_nIndexLvl];

	CString str1;
	str1.Format(_T("res\\googlemaps\\roadmap\\%d\\"), m_nIndexLvl);
	CString str2;
	CString str3;
	CString str;
	for (int i = nStartX; i <= nEndX; i++)
	{
		str2.Format(_T("%d\\"), i);
		for (int j = nStartY; j <= nEndY; j++)
		{
			str3.Format(_T("%d.png"), j);
			str = str1+str2+str3;
			if (m_pImgBk[i-nStartX][j-nStartY]->IsNull())
			{
				if (!SUCCEEDED(m_pImgBk[i-nStartX][j-nStartY]->Load(str)))
				{
					m_pImgBk[i-nStartX][j-nStartY]->Load(NOMAPPATH);
				}
// 				m_pImgBk[i-nStartX][j-nStartY]->Load(str);
			}
// 			if ( m_pImgBk[i-nStartX][j-nStartY]->IsNull() ) // 图片加载失败
// 			{
// 			 	delete m_pImgBk[i-nStartX][j-nStartY];
// 			 	m_pImgBk[i-nStartX][j-nStartY] = NULL;
// 			} 
		}
	}

	nStartY += m_nYTiles[m_nIndexLvl];
	nEndY += m_nYTiles[m_nIndexLvl];
	int nStartTileX = MAP_BOUNDS_LEFT + (nStartX*PNGSIZE*m_dResolutions[m_nIndexLvl]);
	int nStartTileY = MAP_BOUNDS_TOP - (nStartY*PNGSIZE*m_dResolutions[m_nIndexLvl]);
	int ndistanceX = (vb.dleft - nStartTileX)/m_dResolutions[m_nIndexLvl];
	int ndistanceY = (nStartTileY - vb.dtop)/m_dResolutions[m_nIndexLvl];

	int nWidth = rct.right-rct.left;
	int nHeight = rct.bottom-rct.top;

	CWindowDC dc(this);
	for (int i = 0; i < XLINEPICNUM; i++)
	{
		if ((i*PNGSIZE+4-ndistanceX)>nWidth)
		{
			break;
		}
		for(int j = 0; j < YLINEPICNUM; j++)
		{
			if ((j*PNGSIZE+30-ndistanceY)>nHeight)
			{
				break;
			}
			if ((((i+1)*PNGSIZE+4-ndistanceX) > nWidth) && ((((j+1)*PNGSIZE)+30-ndistanceY)>nHeight))
			{
				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+i*PNGSIZE+4-ndistanceX, rct.top+j*PNGSIZE+30-ndistanceY, nWidth-i*PNGSIZE-4+ndistanceX, nHeight-j*PNGSIZE-5+ndistanceY, 0, 0, nWidth-i*PNGSIZE-4+ndistanceX, nHeight-j*PNGSIZE-5+ndistanceY);
				continue;
			}
			if (((i+1)*PNGSIZE+4-ndistanceX) > nWidth)
			{
				if ((j*PNGSIZE+30-ndistanceY)<0)
				{
					m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+i*PNGSIZE+4-ndistanceX, rct.top+30, nWidth-i*PNGSIZE-4+ndistanceX, m_pImgBk[i][j]->GetHeight()-ndistanceY, 0, ndistanceY,nWidth-i*PNGSIZE-4+ndistanceX, PNGSIZE-ndistanceY);
					continue;
				}
				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+i*PNGSIZE+4-ndistanceX, rct.top+j*PNGSIZE+30-ndistanceY, nWidth-i*PNGSIZE-4+ndistanceX, m_pImgBk[i][j]->GetHeight(), 0, 0, nWidth-i*PNGSIZE-4+ndistanceX, PNGSIZE);
				continue;
			}
			if ((((j+1)*PNGSIZE)+30-ndistanceY)>nHeight)
			{
				if ((i*PNGSIZE+4-ndistanceX)<0)
				{
					m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+4, rct.top+j*PNGSIZE+30-ndistanceY, m_pImgBk[i][j]->GetWidth()-ndistanceX, nHeight-j*PNGSIZE-5+ndistanceY, ndistanceX, 0, PNGSIZE-ndistanceX, nHeight-j*PNGSIZE-5+ndistanceY);
					continue;
				}
				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+i*PNGSIZE+4-ndistanceX, rct.top+j*PNGSIZE+30-ndistanceY, m_pImgBk[i][j]->GetWidth(), nHeight-j*PNGSIZE-5+ndistanceY, 0, 0, PNGSIZE, nHeight-j*PNGSIZE-5+ndistanceY);
				continue;
			}
			if (((i*PNGSIZE+4-ndistanceX)<0) && ((j*PNGSIZE+30-ndistanceY)<0))
			{
				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+4, rct.top+j*PNGSIZE+30, m_pImgBk[i][j]->GetWidth()-ndistanceX, m_pImgBk[i][j]->GetHeight()-ndistanceY, ndistanceX, ndistanceY, PNGSIZE-ndistanceX, PNGSIZE-ndistanceY);
				continue;
			}
			if ((i*PNGSIZE+4-ndistanceX)<0)
			{
				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+4, rct.top+j*PNGSIZE+30-ndistanceY, m_pImgBk[i][j]->GetWidth()-ndistanceX, m_pImgBk[i][j]->GetHeight(), ndistanceX, 0, PNGSIZE-ndistanceX, PNGSIZE);
				continue;
			}
			if ((j*PNGSIZE+30-ndistanceY)<0)
			{
				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+i*PNGSIZE+4-ndistanceX, rct.top+30, m_pImgBk[i][j]->GetWidth(), m_pImgBk[i][j]->GetHeight()-ndistanceY, 0, ndistanceY, PNGSIZE, PNGSIZE-ndistanceY);
				continue;
			}
			m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+i*PNGSIZE+4-ndistanceX, rct.top+j*PNGSIZE+30-ndistanceY, m_pImgBk[i][j]->GetWidth(), m_pImgBk[i][j]->GetHeight());
		}
// 		if ( m_pImgBk[i] != NULL )
// 		{
// 			if (4+256*(i+1) > (rct.right - rct.left))
// 			{
// 				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+4+256*i, rct.top, 852-256*(i+1), m_pImgBk[i][j]->GetHeight() );
// 				break;
// 			}
// 			else
// 			{
// 				m_pImgBk[i][j]->Draw(dc.GetSafeHdc(), rct.left+4+256*i, rct.top, m_pImgBk[i][j]->GetWidth(), m_pImgBk[i][j]->GetHeight() );
// 			}
// 		} 
	}

}

void CNoName001Dlg::Lonlat2Mercator(GPSPOSITION gpsPos, double &dx, double &dy)
{

// 	dx = gpsPos.dLatitude *MAP_BOUNDS_RIGHT/180.f;
// 	dy = log(tan((90.f+gpsPos.dLongitude)*PI/360.f))/(PI/180.f);
// 	dy = dy *MAP_BOUNDS_RIGHT/180.f;

	double CentralMeridian=0;
	double RefLat = 0;
	double N0 = 6378137.0 / sqrt( 1-pow(0.081819190843,2)*pow(sin(RefLat*PI/180),2) ); 
	double q1 = log( tan( (180.0/4.0+gpsPos.dLatitude/2.0)*PI/180.0 ) ); 
	double q2 = 0.081819190843/2 * log( (1+0.081819190843*sin(gpsPos.dLatitude*PI/180.0) ) / (1-0.081819190843*sin(gpsPos.dLatitude*PI/180.0) ) ); 
	double q = q1 - q2 ; 
	dx = N0 * cos(RefLat*PI/180.0) * ((gpsPos.dLongitude-CentralMeridian)/57.29577951) ; 
	dy = N0 * cos(RefLat*PI/180.0) * q ;

// 	dx=gpsPos.dLatitude/180*(20037508.3427892);  
// 	dy=gpsPos.dLongitude*(PI)/180;//转换到弧度  
// 
// 	dy=0.5 * log((1 + sin(dy)) / (1 -sin(dy)));//墨卡托转换  
// 	dy=dy*180/(2*85.05112877980659)/PI;  
// 	dy=(1-dy-0.5)/0.5*20037508.3427892;  
}

//void CNoName001Dlg::OnStnClickedStaticRadar()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_nIndexLvl++;
//	if (m_nIndexLvl > 21)
//	{
//		m_nIndexLvl = 0;
//	}
//	DrawBkg(m_GPSCentre);
//}


//void CNoName001Dlg::OnStnDblclickStaticRadar()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_nIndexLvl--;
//	if (m_nIndexLvl < 0)
//	{
//		m_nIndexLvl = 21;
//	}
//	DrawBkg(m_GPSCentre);
//}


void CNoName001Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RECT rct;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_RADAR);
	pWnd->GetWindowRect(&rct);
	ScreenToClient(&rct);

	if (PtInRect(&rct, point))
	{
		m_nIndexLvl++;
		if (m_nIndexLvl > 21)
		{
			m_nIndexLvl = 21;
		}
		DrawBkg(m_GPSCentre, m_nIndexLvl);
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CNoName001Dlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RECT rct;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_RADAR);
	pWnd->GetWindowRect(&rct);
	ScreenToClient(&rct);

	if (PtInRect(&rct, point))
	{
		m_nIndexLvl--;
		if (m_nIndexLvl < 0)
		{
			m_nIndexLvl = 0;
		}
		DrawBkg(m_GPSCentre, m_nIndexLvl);
	}

	CDialogEx::OnRButtonDblClk(nFlags, point);
}
