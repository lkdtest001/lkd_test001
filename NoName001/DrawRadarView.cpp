// DrawRadarView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NoName001.h"
#include "DrawRadarView.h"


// CDrawRadarView

IMPLEMENT_DYNCREATE(CDrawRadarView, CFormView)

CDrawRadarView::CDrawRadarView()
	: CFormView(CDrawRadarView::IDD)
	,m_bStartSel(false)
	,m_nNum(0)
{

}

CDrawRadarView::~CDrawRadarView()
{
}

void CDrawRadarView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawRadarView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CDrawRadarView::OnBnClickedButtonDraw)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CDrawRadarView ���

#ifdef _DEBUG
void CDrawRadarView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDrawRadarView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDrawRadarView ��Ϣ�������
void CDrawRadarView::drawLines(CPoint *pt, int nNum)
{
	CDC *pdc = GetDC();
	CPen RedPen, *pOldPen;
	RedPen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
	pOldPen = pdc->SelectObject(&RedPen);
	if (nNum >= 2)
	{
		pdc->MoveTo(pt[0]);
		for (int i = 1; i < nNum; i++)
		{
			pdc->LineTo(pt[i]);
		}
	}

	pdc->SelectObject(pOldPen);
	RedPen.DeleteObject();
	delete pdc;
	pdc = NULL;
	

}

void CDrawRadarView::OnBnClickedButtonDraw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bStartSel == false)
	{
		m_bStartSel = true;
		m_nNum = 0;
	}
	else 
	{
		m_bStartSel = false;
		drawLines(m_pt, m_nNum);
	}
}


void CDrawRadarView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_pt[m_nNum++] = point;
	CFormView::OnLButtonUp(nFlags, point);
}
