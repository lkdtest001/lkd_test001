#pragma once


// CMainView �Ի���

class CMainView : public CDialogEx
{
	DECLARE_DYNAMIC(CMainView)

public:
	CMainView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainView();

// �Ի�������
	enum { IDD = IDD_NONAME001_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
