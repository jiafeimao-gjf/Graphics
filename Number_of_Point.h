#pragma once


// CNumber_of_Point �Ի���

class CNumber_of_Point : public CDialogEx
{
	DECLARE_DYNAMIC(CNumber_of_Point)

public:
	CNumber_of_Point(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNumber_of_Point();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_Num_point;
};
