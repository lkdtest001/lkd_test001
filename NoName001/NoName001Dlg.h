
// NoName001Dlg.h : 头文件
//

#pragma once
#include "CRadarCommonPara.h"
#include "DrawRadarView.h"

#define XLINEPICNUM 4
#define YLINEPICNUM 3
#define NOMAPPATH _T("res\\nomap.png")
// CNoName001Dlg 对话框
class CNoName001Dlg : public CDialogEx
{
// 构造
public:
	CNoName001Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CNoName001Dlg();
// 对话框数据
	enum { IDD = IDD_NONAME001_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CImage *m_pImgBk[XLINEPICNUM][YLINEPICNUM];
	GPSPOSITION m_GPSCentre;

	void DrawBkg(GPSPOSITION gPos, int nLvl = 14); // 传入中心GPS与缩放等级
	void Lonlat2Mercator(GPSPOSITION gpsPos, double &dx, double &dy); // 经纬度转墨卡托

	double m_dResolutions[22]; // 分辨率数组，与级别相对应，即一个级别对应一个分辨率，分辨率表示当前级别下单个像素代表的地理长度
	int m_nIndexLvl; // 缩放级别 0~21

	int m_nYTiles[22]; // Y坐标修正

	CDrawRadarView m_RadarDraw;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
