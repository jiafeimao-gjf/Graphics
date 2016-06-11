
// Graphics_SoftwareView.h : CGraphics_SoftwareView 类的接口
//

#pragma once
#include "Graphics_SoftwareDoc.h"
#include "Dlg_Eclipse.h"
#include "Point_2D.h"
#include "Transform_2D.h"
#include "Transform_3D_Dlg.h"
#include "Ball_Display_Dlg.h"

#define width 8
#define NUM 10
#define DX 650
#define DY 350
#define SIDE_COLOR RGB(0,125,225)
#define INSIDE_COLOR RGB(100,50,100)
#define POINT_COLOR RGB(166,166,166)
#define LINE_COLOR RGB(75,10,35)



class CGraphics_SoftwareView : public CView
{
protected: // 仅从序列化创建
	CGraphics_SoftwareView();
	DECLARE_DYNCREATE(CGraphics_SoftwareView)
// 特性
public:
	CGraphics_SoftwareDoc* GetDocument() const;
// 操作
public:
	void DDA_Alg(CDC* pDC,CPoint point1, CPoint point2,COLORREF clr);
	void Rect(CDC* pDC,int x, int y, COLORREF clr);
	void Middle_Alg(CDC* pDC, CPoint point1, CPoint point2, COLORREF clr);
	void MidPoint_Circle(CDC* pDC,long r,COLORREF clr);
	void Bresenham_Circle_alg(CDC* pDC, long r,COLORREF clr);
	void Bresenham_Alg(CDC* pDC, CPoint point1, CPoint point2, COLORREF clr);
	void MidPoint_Eclipse_Alg(CDC* pDC, int a, int b, COLORREF clr);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphics_SoftwareView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	//变量
	//直线扫描转换
	bool m_chooseAlg;
	CPoint p1[3],p2[3];
	//绘制圆、椭圆
	int R[2], A, B;
	bool m_bDraw;

	bool m_axis;
	bool m_rect;
	//多边形
	CPoint m_point[NUM*width];

	CPoint O[3];

	CPoint_2D P[NUM];//矩形的顶点
	CTransform_2D trans;

	CPoint Point[NUM];
	CPoint Seed;
	int number;
	int number_n;
	bool m_polygon;
	bool m_polygon_n;
	int m_Angle;
	int m_showWeb;
	int m_num;
	//辅助函数
	int destence(CPoint a, CPoint b);
	void selectSort(CPoint a[], int num);

	void BoundaryFill_4(HDC hdc,CDC *pDC,int x, int y);

	void Draw_polygon();
	void DrawPolygon();

	void GetSeed();
	bool Isinside(CPoint point);

private:
	void Draw_Polygon_edge(int num);
public:
	afx_msg void DDA_alg();
	afx_msg void Middle_alg();
	afx_msg void Bresenham_alg();
	afx_msg void _Clear();
	afx_msg void Compare_Line_Alg();
	afx_msg void Middle_Circle_Alg();
	afx_msg void Clear_Circle();
	afx_msg void Bresenham_Circle();
	afx_msg void Compare_Circle_Alg();
	afx_msg void MidPoint_Eclipse();
	afx_msg void OnPantagon_filling();
	afx_msg void OnSix_Side();
	afx_msg void Onseven_side();
	afx_msg void OnEight_Side();
	afx_msg void OnNine_Side();
	afx_msg void OnTen_Side();
	afx_msg void OnPolygon_clear();
	afx_msg void On_N_Side();
	afx_msg void OnFill_Alg_1();
	afx_msg void OnEageMark_Fill();
	afx_msg void OnSeed_Fill();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On_Scanline_seed_fill();
	afx_msg void On_FanceFill();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void On_Web();
	afx_msg void On_Webclear();
	afx_msg void showCoordinateAxis();
	afx_msg void On_closeCoordinate();
	afx_msg void On_Rectangle();
	afx_msg void On_left();
	afx_msg void OnTright();
	afx_msg void OnTdown();
	afx_msg void OnTup();
	afx_msg void OnTincrease();
	afx_msg void OnTdecrease();
	afx_msg void On_Angle_30();
	afx_msg void On_Angle_60();
	afx_msg void On_Angle_90();
	afx_msg void On_Angle_180();
	afx_msg void OnRclockwise();
	afx_msg void OnRcunterclockwise();
	afx_msg void OnRxaxis();
	afx_msg void OnRyaxis();
	afx_msg void OnRorg();
	afx_msg void OnSxdorectionneg();
	afx_msg void OnSxdirectionplus();
	afx_msg void OnSydirectionneg();
	afx_msg void OnSydirectionplus();
	afx_msg void Onhexagon();
	afx_msg void Onoctagon();
	afx_msg void OnTransform_3D();
	afx_msg void OnBall_Display();
};

#ifndef _DEBUG  // Graphics_SoftwareView.cpp 中的调试版本
inline CGraphics_SoftwareDoc* CGraphics_SoftwareView::GetDocument() const
   { return reinterpret_cast<CGraphics_SoftwareDoc*>(m_pDocument); }
#endif

