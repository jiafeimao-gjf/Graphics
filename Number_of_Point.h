#pragma once


// CNumber_of_Point 对话框

class CNumber_of_Point : public CDialogEx
{
	DECLARE_DYNAMIC(CNumber_of_Point)

public:
	CNumber_of_Point(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNumber_of_Point();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Num_point;
};
