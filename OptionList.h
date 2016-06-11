#pragma once
#include "afxcmn.h"


// COptionList 对话框

class COptionList : public CDialogEx
{
	DECLARE_DYNAMIC(COptionList)

public:
	COptionList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionList();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Control_BALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	bool m_Display;

public:
	CSliderCtrl m_cRadius;
	CSliderCtrl m_cFaceCount;
	int m_rPattern;
	int m_rLighting;
	CSliderCtrl m_cTranslateX;
	CSliderCtrl m_cTranslateY;
	CSliderCtrl m_cTranslateZ;
	CSliderCtrl m_cRotateX;
	CSliderCtrl m_cRotateY;
	CSliderCtrl m_cRotateZ;
	afx_msg void OnBnClickedRadioPattern();
	afx_msg void OnBnClickedRadioPattern2();
	afx_msg void OnBnClickedRadioLighting();
	afx_msg void OnBnClickedRadioLighting2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDisplay();
	afx_msg void OnBnClickedHide();
};
