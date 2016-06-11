#pragma once
#include "stdafx.h"
#include "Point_3D.h"
#include "Face.h"
#include "Transform_3D.h"
// CTransform_3D_Dlg 对话框

#define DX 300
#define DY 300

class CTransform_3D_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTransform_3D_Dlg)

public:
	CTransform_3D_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTransform_3D_Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	CPoint_3D P[8];//点表
	CFace F[6];//面表
	CPoint_2D ScreenP;//屏幕坐标系的二维坐标点
	CTransform_3D trans;
public:
	void ReadPoint();
	void ReadFace();
	void ObliqueProject(CPoint_3D);//斜等侧变换
	void DrawPolygon(CDC *);//绘制多边形
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	afx_msg void OnBnClickedFront();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedBigger();
	afx_msg void OnBnClickedSmall();
	afx_msg void OnBnClickedYoz();
	afx_msg void OnBnClickedXoz();
	afx_msg void OnBnClickedXoy();
	afx_msg void OnBnClickedXaxis();
	afx_msg void OnBnClickedYaxis();
	afx_msg void OnBnClickedZaxis();
	afx_msg void OnBnClickedXdirectionplus();
	afx_msg void OnBnClickedYdirectionplus();
	afx_msg void OnBnClickedZdirectionplus();
	afx_msg void OnBnClickedReset();
};
