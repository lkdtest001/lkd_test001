#pragma once

#include "stdafx.h"

// CDrawRadarView ������ͼ

class CDrawRadarView : public CFormView
{
	DECLARE_DYNCREATE(CDrawRadarView)

public:
	CDrawRadarView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDrawRadarView();

public:
	enum { IDD = IDD_NONAME001_DIALOG };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
//	virtual void OnDraw(CDC* /*pDC*/);

public:
	void drawLines(CPoint *pt, int nNum);

	afx_msg void OnBnClickedButtonDraw();
	bool m_bStartSel;
	CPoint m_pt[255];
	int m_nNum;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


