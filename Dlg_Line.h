#pragma once


// CDlg_Line �Ի���

class CDlg_Line : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Line)

public:
	CDlg_Line(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_Line();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int a;
	int b;
	int c;
	int d;
};
