#pragma once


// CDlg_Line 对话框

class CDlg_Line : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Line)

public:
	CDlg_Line(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Line();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int a;
	int b;
	int c;
	int d;
};
