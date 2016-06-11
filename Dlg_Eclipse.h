#pragma once


// CDlg_Eclipse 对话框

class CDlg_Eclipse : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Eclipse)

public:
	CDlg_Eclipse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Eclipse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int x;
	int y;
	float a;
	float b;
	int r;
};
