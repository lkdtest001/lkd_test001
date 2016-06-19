// MainView.cpp : 实现文件
//

#include "stdafx.h"
#include "NoName001.h"
#include "MainView.h"
#include "afxdialogex.h"


// CMainView 对话框

IMPLEMENT_DYNAMIC(CMainView, CDialogEx)

CMainView::CMainView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainView::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainView, CDialogEx)
END_MESSAGE_MAP()


// CMainView 消息处理程序
