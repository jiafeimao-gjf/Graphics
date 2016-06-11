#pragma once
#include "OptionList.h"
// CBall_Display_Dlg 对话框

class CBall_Display_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBall_Display_Dlg)

public:
	CBall_Display_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBall_Display_Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

public:
	HGLRC m_hglrc;	//add two variable
	CClientDC* m_pDC;


protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	COptionList Optiondlg;
	GLuint  m_nRadius;
	GLuint  m_nCount;
	GLuint  m_nPattern;
	GLuint  m_nLighting;
	GLfloat m_fTranslateX;
	GLfloat m_fTranslateY;
	GLfloat m_fTranslateZ;
	GLfloat m_fRotateX;
	GLfloat m_fRotateY;
	GLfloat m_fRotateZ;
	BOOL m_xTranBool;
	BOOL m_yTranBool;
	BOOL m_zTranBool;
protected:
	void DrawScene();
	void NormalTriangle(float *v1, float *v2, float *v3, float *vout);
	void Normalize(float *v, float radius);
	void DrawTriangle(float *v1, float *v2, float *v3);
	void SubDivide(float *v1, float *v2, float *v3, int count);
	void DrawGeometry();
public:
	virtual BOOL OnInitDialog();
};
