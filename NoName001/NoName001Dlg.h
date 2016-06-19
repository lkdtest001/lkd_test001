
// NoName001Dlg.h : ͷ�ļ�
//

#pragma once
#include "CRadarCommonPara.h"
#include "DrawRadarView.h"

#define XLINEPICNUM 4
#define YLINEPICNUM 3
#define NOMAPPATH _T("res\\nomap.png")
// CNoName001Dlg �Ի���
class CNoName001Dlg : public CDialogEx
{
// ����
public:
	CNoName001Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CNoName001Dlg();
// �Ի�������
	enum { IDD = IDD_NONAME001_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CImage *m_pImgBk[XLINEPICNUM][YLINEPICNUM];
	GPSPOSITION m_GPSCentre;

	void DrawBkg(GPSPOSITION gPos, int nLvl = 14); // ��������GPS�����ŵȼ�
	void Lonlat2Mercator(GPSPOSITION gpsPos, double &dx, double &dy); // ��γ��תī����

	double m_dResolutions[22]; // �ֱ������飬�뼶�����Ӧ����һ�������Ӧһ���ֱ��ʣ��ֱ��ʱ�ʾ��ǰ�����µ������ش���ĵ�����
	int m_nIndexLvl; // ���ż��� 0~21

	int m_nYTiles[22]; // Y��������

	CDrawRadarView m_RadarDraw;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnStnClickedStaticRadar();
//	afx_msg void OnStnDblclickStaticRadar();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
};
