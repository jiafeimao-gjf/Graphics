#pragma once


// CDlg_Eclipse �Ի���

class CDlg_Eclipse : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Eclipse)

public:
	CDlg_Eclipse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_Eclipse();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int x;
	int y;
	float a;
	float b;
	int r;
};
