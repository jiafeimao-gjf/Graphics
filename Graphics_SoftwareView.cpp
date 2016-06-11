
// Graphics_SoftwareView.cpp : CGraphics_SoftwareView 类的实现
//

#include <time.h>
#include <cstdlib>
#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Graphics_Software.h"
#endif

#include "Graphics_SoftwareDoc.h"
#include "Graphics_SoftwareView.h"
#include "Dlg_Line.h"
#include "Dlg_polygon.h"
#include "Number_of_Point.h"
#include "Stack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphics_SoftwareView

IMPLEMENT_DYNCREATE(CGraphics_SoftwareView, CView)

BEGIN_MESSAGE_MAP(CGraphics_SoftwareView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CGraphics_SoftwareView::DDA_alg)
	ON_COMMAND(ID_32772, &CGraphics_SoftwareView::Middle_alg)
	ON_COMMAND(ID_32773, &CGraphics_SoftwareView::Bresenham_alg)
	ON_COMMAND(ID_32778, &CGraphics_SoftwareView::_Clear)
	ON_COMMAND(ID_32780, &CGraphics_SoftwareView::Compare_Line_Alg)
	ON_COMMAND(ID_32781, &CGraphics_SoftwareView::Middle_Circle_Alg)
	ON_COMMAND(ID_32785, &CGraphics_SoftwareView::Clear_Circle)
	ON_COMMAND(ID_32782, &CGraphics_SoftwareView::Bresenham_Circle)
	ON_COMMAND(ID_32783, &CGraphics_SoftwareView::Compare_Circle_Alg)
	ON_COMMAND(ID_32784, &CGraphics_SoftwareView::MidPoint_Eclipse)
	ON_COMMAND(ID_Menu, &CGraphics_SoftwareView::OnPantagon_filling)
	ON_COMMAND(ID_32789, &CGraphics_SoftwareView::OnSix_Side)
	ON_COMMAND(ID_32790, &CGraphics_SoftwareView::Onseven_side)
	ON_COMMAND(ID_32791, &CGraphics_SoftwareView::OnEight_Side)
	ON_COMMAND(ID_32792, &CGraphics_SoftwareView::OnNine_Side)
	ON_COMMAND(ID_32793, &CGraphics_SoftwareView::OnTen_Side)
	ON_COMMAND(ID_32794, &CGraphics_SoftwareView::OnPolygon_clear)
	ON_COMMAND(ID_32795, &CGraphics_SoftwareView::On_N_Side)
	ON_COMMAND(ID_32796, &CGraphics_SoftwareView::OnFill_Alg_1)
	ON_COMMAND(ID_32797, &CGraphics_SoftwareView::OnEageMark_Fill)
	ON_COMMAND(ID_32798, &CGraphics_SoftwareView::OnSeed_Fill)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32799, &CGraphics_SoftwareView::On_Scanline_seed_fill)
	ON_COMMAND(ID_32801, &CGraphics_SoftwareView::On_FanceFill)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_32803, &CGraphics_SoftwareView::On_Web)
	ON_COMMAND(ID_32804, &CGraphics_SoftwareView::On_Webclear)
	ON_COMMAND(ID_32814, &CGraphics_SoftwareView::showCoordinateAxis)
	ON_COMMAND(ID_32815, &CGraphics_SoftwareView::On_closeCoordinate)
	ON_COMMAND(ID_32817, &CGraphics_SoftwareView::On_Rectangle)
	ON_COMMAND(ID_32806, &CGraphics_SoftwareView::On_left)
	ON_COMMAND(ID_32807, &CGraphics_SoftwareView::OnTright)
	ON_COMMAND(ID_32808, &CGraphics_SoftwareView::OnTdown)
	ON_COMMAND(ID_32809, &CGraphics_SoftwareView::OnTup)
	ON_COMMAND(ID_32811, &CGraphics_SoftwareView::OnTincrease)
	ON_COMMAND(ID_32812, &CGraphics_SoftwareView::OnTdecrease)
	ON_COMMAND(ID_32836, &CGraphics_SoftwareView::On_Angle_30)
	ON_COMMAND(ID_32838, &CGraphics_SoftwareView::On_Angle_60)
	ON_COMMAND(ID_32840, &CGraphics_SoftwareView::On_Angle_90)
	ON_COMMAND(ID_32841, &CGraphics_SoftwareView::On_Angle_180)
	ON_COMMAND(ID_32827, &CGraphics_SoftwareView::OnRclockwise)
	ON_COMMAND(ID_32826, &CGraphics_SoftwareView::OnRcunterclockwise)
	ON_COMMAND(ID_32829, &CGraphics_SoftwareView::OnRxaxis)
	ON_COMMAND(ID_32830, &CGraphics_SoftwareView::OnRyaxis)
	ON_COMMAND(ID_32842, &CGraphics_SoftwareView::OnRorg)
	ON_COMMAND(ID_32834, &CGraphics_SoftwareView::OnSxdorectionneg)
	ON_COMMAND(ID_32835, &CGraphics_SoftwareView::OnSxdirectionplus)
	ON_COMMAND(ID_32833, &CGraphics_SoftwareView::OnSydirectionneg)
	ON_COMMAND(ID_32832, &CGraphics_SoftwareView::OnSydirectionplus)
	ON_COMMAND(ID_32818, &CGraphics_SoftwareView::Onhexagon)
	ON_COMMAND(ID_32819, &CGraphics_SoftwareView::Onoctagon)
	ON_COMMAND(ID_32843, &CGraphics_SoftwareView::OnTransform_3D)
	ON_COMMAND(ID_BALL, &CGraphics_SoftwareView::OnBall_Display)
END_MESSAGE_MAP()

// CGraphics_SoftwareView 构造/析构

CGraphics_SoftwareView::CGraphics_SoftwareView()
	: m_chooseAlg(false)
	, m_polygon(false)
	, m_polygon_n(false)
	, m_bDraw(false)
	, m_showWeb(0)
	, m_axis(false)
	, m_rect(false)
	, m_Angle(0)
	, m_num(0)
{
	R[0] = R[1] = A = B = 0;
	p1[0].x = p1[0].y = p1[1].x = p1[1].y = p1[2].x = p1[2].y = 0;
	p2[0].x = p2[0].y = p2[1].x = p2[1].y = p2[2].x = p2[2].y = 0;
	O[2].x = O[2].y = O[0].x = O[0].y = O[1].x = O[1].y = 0;
	Point[0].x = Point[0].y = -1;
	for (int i = 1; i < NUM; i++) {
		Point[i] = Point[i - 1];
	}
	Seed.x = -1; Seed.y = -1;
	for (int i = 0; i < NUM*width; i++) {
		m_point[i].x = -1;
		m_point[i].y = -1;
	}
	number = number_n = -1;
}

CGraphics_SoftwareView::~CGraphics_SoftwareView()
{
}

BOOL CGraphics_SoftwareView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.lpszName = _T("Graphics Software");
	return CView::PreCreateWindow(cs);
}

// CGraphics_SoftwareView 绘制

//绘制像素点函数
void CGraphics_SoftwareView::Rect(CDC* pDC, int x, int y, COLORREF clr)
{
	CPoint pp1, pp2;
	pp1.x = x * width + 1; pp1.y = y * width  + 1; pp2.x = x * width + width; pp2.y = y * width + width;

	//Sleep(5);
	CBrush Brush(clr);
	pDC->FillRect(CRect(pp1, pp2), &Brush);
}

//直线扫描算法
//DDA算法
void CGraphics_SoftwareView::DDA_Alg(CDC* pDC, CPoint point1, CPoint point2, COLORREF clr)
{
	float x, y, k, deltx, delty;
	CPoint p1 = point1, p2 = point2;
	if ((p1.x == p2.x) && (p1.y != p2.y)) {	//斜率无穷大
		y = p1.y < p2.y ? p1.y : p2.y;
		x = p1.y > p2.y ? p1.y : p2.y;
		for (int i = y; i <= x; i++) {
			Rect(pDC, p1.x, i, clr);
		}
	}
	if (p1.x > p2.x) {
		int temp = 0;
		temp = p1.x;
		p1.x = p2.x;
		p2.x = temp;
		temp = p1.y;
		p1.y = p2.y;
		p2.y = temp;
	}
	deltx = p1.x - p2.x;
	delty = p1.y - p2.y;
	k = delty / deltx;
	if (k <= 1 && k >= -1) {										//斜率小于等于1
		y = p1.y;
		for (int i = p1.x; i <= p2.x; i++) {
			Rect(pDC, i, int(y + 0.5), clr);
			y = y + k;
		}
	}
	else {											//斜率大于1
		if (p1.y > p2.y) {
			int temp = 0;
			temp = p1.x;
			p1.x = p2.x;
			p2.x = temp;
			temp = p1.y;
			p1.y = p2.y;
			p2.y = temp;
		}
		x = p1.x;
		for (int i = p1.y; i <= p2.y; i++) {
			Rect(pDC, int(x + 0.5), i, clr);
			x = x + 1 / k;
		}
	}
}
//中点画线法
void CGraphics_SoftwareView::Middle_Alg(CDC * pDC, CPoint point1, CPoint point2, COLORREF clr)
{
	int a, b, delta1, delta2, d, x, y;
	if ((point1.x == point2.x) && (point1.y != point2.y)) {	//斜率无穷大
		y = point1.y < point2.y ? point1.y : point2.y;
		x = point1.y > point2.y ? point1.y : point2.y;
		for (int i = y; i <= x; i++) {
			Rect(pDC, point1.x, i, clr);
		}
		return;
	}
	if (point1.x > point2.x && point1.y > point2.y) {
		int temp = 0;
		temp = point1.y;
		point1.x = point2.x;
		point2.x = temp;
		temp = point1.y;
		point1.y = point2.y;
		point2.y = temp;
	}
	a = point1.y - point2.y;
	b = point2.x - point1.x;
	if ((float)-a / b <= 1) {									//斜率小于等于1
		d = 2 * a + b;
		delta1 = 2 * a;
		delta2 = 2 * (a + b);
		x = point1.x;
		y = point1.y;
		Rect(pDC, x, y, clr);

		while (x < point2.x) {
			if (d < 0) {
				x++; y++;
				d += delta2;
			}
			else {
				x++; d += delta1;
			}
			Rect(pDC, x, y, clr);
		}
	}
	else {												//斜率大于1
		a = point1.x - point2.x;
		b = point2.y - point1.y;
		d = 2 * a + b;
		delta1 = 2 * a;
		delta2 = 2 * (a + b);
		if (point1.x != point1.y) {
			x = point1.y + (point1.x - point1.y);
			y = point1.x + (point1.y - point1.x);
		}
		else {
			x = point1.y;
			y = point1.x;
		}

		Rect(pDC, point1.x, point1.y, clr);

		while (y < point2.y) {
			if (d < 0) {
				x++; y++;
				d += delta2;
			}
			else {
				y++; d += delta1;
			}
			Rect(pDC, x, y, clr);
		}
	}
}
//Bresenham算法画直线
void CGraphics_SoftwareView::Bresenham_Alg(CDC * pDC, CPoint point1, CPoint point2, COLORREF clr)
{
	int x, y, dx, dy, e;
	if ((point1.x == point2.x) && (point1.y != point2.y)) {	//斜率无穷大
		y = point1.y < point2.y ? point1.y : point2.y;
		x = point1.y > point2.y ? point1.y : point2.y;
		for (int i = y; i <= x; i++) {
			Rect(pDC, point1.x, i, clr);
		}
		return;
	}
	if (point1.x >= point2.x && point1.y >= point2.y) {
		int temp = 0;
		temp = point1.y;
		point1.x = point2.x;
		point2.x = temp;
		temp = point1.y;
		point1.y = point2.y;
		point2.y = temp;
	}
	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	if ((float)dy / dx <= 1) {									//斜率小于等于1
		e = -dx;
		x = point1.x;
		y = point1.y;
		for (int i = 0; i <= dx; i++) {
			Rect(pDC, x, y, clr);
			x++;
			e = e + 2 * dy;
			if (e >= 0) {
				y++;
				e = e - 2 * dx;
			}
		}
	}
	else {												//斜率大于1
		e = -dy;
		if (point1.x != point1.y) {
			x = point1.y + (point1.x - point1.y);
			y = point1.x + (point1.y - point1.x);
		}
		else {
			x = point1.y;
			y = point1.x;
		}
		for (int i = 0; i <= dy; i++) {
			Rect(pDC, x, y, clr);
			y++;
			e = e + 2 * dx;
			if (e >= 0) {
				x++;
				e = e - 2 * dy;
			}
		}
	}
}

//画圆算法
//中点画圆法
void CGraphics_SoftwareView::MidPoint_Circle(CDC * pDC, long r, COLORREF clr)
{
	int x, y, deltax, deltay, e;
	x = 0; y = r;
	e = 1 - r;
	deltax = 3; deltay = 2 - r - r;
	Rect(pDC, x + O[0].x, y + O[0].y, clr);
	Rect(pDC, y + O[0].x, x + O[0].y, clr);
	Rect(pDC, -x + O[0].x, y + O[0].y, clr);
	Rect(pDC, -y + O[0].x, x + O[0].y, clr);
	Rect(pDC, -x + O[0].x, -y + O[0].y, clr);
	Rect(pDC, -y + O[0].x, -x + O[0].y, clr);
	Rect(pDC, x + O[0].x, -y + O[0].y, clr);
	Rect(pDC, y + O[0].x, -x + O[0].y, clr);
	while (x < y) {
		if (e < 0) {
			e += deltax;
			deltax += 2;
			x++;
		}
		else {
			e += (deltax + deltay);
			deltax += 2; deltay += 2;
			x++; y--;
		}
		Rect(pDC, x + O[0].x, y + O[0].y, clr);
		Rect(pDC, y + O[0].x, x + O[0].y, clr);
		Rect(pDC, -x + O[0].x, y + O[0].y, clr);
		Rect(pDC, -y + O[0].x, x + O[0].y, clr);
		Rect(pDC, -x + O[0].x, -y + O[0].y, clr);
		Rect(pDC, -y + O[0].x, -x + O[0].y, clr);
		Rect(pDC, x + O[0].x, -y + O[0].y, clr);
		Rect(pDC, y + O[0].x, -x + O[0].y, clr);
	}
}
//Bresenham算法画圆
void CGraphics_SoftwareView::Bresenham_Circle_alg(CDC * pDC, long r, COLORREF clr) //
{
	int x, y, delta, delta1, delta2, direction;
	x = 0; y = r;
	delta = 2 * (1 - r);
	while (y >= 0) {
		Rect(pDC, x + O[1].x, y + O[1].y, clr);		//第一象限
		Rect(pDC, -x + O[1].x, -y + O[1].y, clr);	//第三象限
		Rect(pDC, x + O[1].x, -y + O[1].y, clr);	//第四象限
		Rect(pDC, -x + O[1].x, y + O[1].y, clr);	//第二象限
		if (delta < 0) {
			delta1 = 2 * (delta + y) - 1;
			if (delta1 <= 0) direction = 1;
			else direction = 2;
		}
		else if (delta > 0) {
			delta2 = 2 * (delta - x) - 1;
			if (delta2 <= 0) direction = 2;
			else direction = 3;
		}
		else direction = 2;
		switch (direction) {
		case 1:x++; delta += 2 * x + 1;
			break;
		case 2:x++; y--; delta += 2 * (x - y + 1);
			break;
		case 3:y--; delta += (-2 * y + 1);
			break;
		}
	}
}
//中点算法画椭圆
void CGraphics_SoftwareView::MidPoint_Eclipse_Alg(CDC * pDC, int a, int b, COLORREF clr)
{
	int x, y;
	double d1, d2;
	x = 0; y = b;
	d1 = b*b + a*a*(-b + 0.25);
	Rect(pDC, x + O[2].x, y + O[2].y, clr);		//第一象限
	Rect(pDC, -x + O[2].x, -y + O[2].y, clr);	//第三象限
	Rect(pDC, x + O[2].x, -y + O[2].y, clr);	//第四象限
	Rect(pDC, -x + O[2].x, y + O[2].y, clr);	//第二象限
	while (b*b*(x + 1) < a*a*(y - 0.5)) {
		if (d1 < 0) {
			d1 += b * b * (2 * x + 3);
			x++;
		}
		else {
			d1 += (b * b * (2 * x + 3) + a * a *(-2 * y + 2));
			x++; y--;
		}
		Rect(pDC, x + O[2].x, y + O[2].y, clr);		//第一象限
		Rect(pDC, -x + O[2].x, -y + O[2].y, clr);	//第三象限
		Rect(pDC, x + O[2].x, -y + O[2].y, clr);	//第四象限
		Rect(pDC, -x + O[2].x, y + O[2].y, clr);	//第二象限
	}//上半部分,斜率的绝对值小于1
	d2 = sqrt(b * (x + 0.5)) + sqrt(a*(y - 1)) - sqrt(a*b);
	while (y > 0) {
		if (d2 < 0) {
			d2 += (b * b * (2 * x + 2) + a * a *(-2 * y + 3));
			x++; y--;
		}
		else {
			d2 += a * a * (-2 * y + 3);
			y--;
		}
		Rect(pDC, x + 1 + O[2].x, y + O[2].y, clr);		//第一象限
		Rect(pDC, -x - 1 + O[2].x, -y + O[2].y, clr);	//第三象限
		Rect(pDC, x + 1 + O[2].x, -y + O[2].y, clr);	//第四象限
		Rect(pDC, -x - 1 + O[2].x, y + O[2].y, clr);	//第二象限
	}
}


//重绘窗口函数
void CGraphics_SoftwareView::OnDraw(CDC* pDC)
{
	CGraphics_SoftwareDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (m_showWeb) {
		CString str;
			CPen pen(0,1,LINE_COLOR);
			pDC->SelectObject(&pen);
			for (int i = 2 * width; i <= 78 * width; i += width) {		//绘制网格
				if (((i - 2 * width) / width) % 5 == 0) {
					str.Format(_T("%d"), (i - 2 * width) / width);
					pDC->TextOut(0, i - 2, str);
					Rect(pDC, 2, (i - 2 * width) / width + 2, LINE_COLOR);
				}
				pDC->MoveTo(2 * width, i);
				pDC->LineTo(158 * width, i);
			}
			for (int i = 2 * width; i <= 158 * width; i += width) {

				if (((i - 2 * width) / width) % 5 == 0) {
					str.Format(_T("%d"), (i - 2 * width) / width);
					pDC->TextOut(i - 2, 0, str);
					Rect(pDC, (i - 2 * width) / width + 2, 2, LINE_COLOR);
				}
				pDC->MoveTo(i, 2 * width);
				pDC->LineTo(i, 78 * width);
			}
	}
	if (m_axis) {
		showCoordinateAxis();
	}
	if (m_rect) {
		DrawPolygon();
	}
	if (m_chooseAlg) {
		//DDA算法绘制直线
		if (!(p1[0].x == p1[0].y == p2[0].x == p2[0].y)) {
			DDA_Alg(pDC, p1[0], p2[0], RGB(255, 0, 0));
		}
		//中点画线法绘制直线
		if (!(p1[1].x == p1[1].y == p2[1].x == p2[1].y)) {
			Middle_Alg(pDC, p1[1], p2[1], RGB(0, 255, 0));
		}
		//Bresenham算法绘制直线
		if (!(p1[2].x == p1[2].y == p2[2].x == p2[2].y)) {
			Bresenham_Alg(pDC, p1[2], p2[2], RGB(0, 0, 255));
		}
	}
	if (R[0]) {
		//MessageBox(_T("m_Midpoint = true"));
		Rect(pDC, O[0].x, O[0].y, RGB(175, 125, 50));
		MidPoint_Circle(pDC, R[0], RGB(175, 125, 50));
	}
	if (R[1]) {
		//MessageBox(_T("m_Breseham = true"));
		Rect(pDC, O[1].x, O[1].y, RGB(75, 175, 75));
		Bresenham_Circle_alg(pDC, R[1], RGB(75, 175, 75));
	}
	if (A && B) {
		//MessageBox(_T("m_MidP_Eclipse = true"));
		Rect(pDC, O[2].x, O[2].y, RGB(50, 25, 175));
		MidPoint_Eclipse_Alg(pDC, A, B, RGB(50, 25, 175));
	}
	if (m_polygon) {
		Draw_Polygon_edge(number);
	}
	if (m_polygon_n) {
		Draw_polygon();
	}
}

// CGraphics_SoftwareView 打印

BOOL CGraphics_SoftwareView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGraphics_SoftwareView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CGraphics_SoftwareView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}


// CGraphics_SoftwareView 诊断

#ifdef _DEBUG
void CGraphics_SoftwareView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphics_SoftwareView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphics_SoftwareDoc* CGraphics_SoftwareView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphics_SoftwareDoc)));
	return (CGraphics_SoftwareDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphics_SoftwareView 消息处理程序

//直线扫描菜单
//响应菜单"DDA算法"
void CGraphics_SoftwareView::DDA_alg()
{
	m_chooseAlg = true;
	CDlg_Line dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);

	if (!(p1[0].x == p1[0].y == p2[0].x == p2[0].y)) {
		dlg.a = p1[0].x - 2; dlg.b = p1[0].y - 2;
		dlg.c = p2[0].x - 2; dlg.d = p2[0].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		p1[0].x = dlg.a + 2; p1[0].y = dlg.b + 2;
		p2[0].x = dlg.c + 2; p2[0].y = dlg.d + 2;
		Invalidate();
	}
}

//响应菜单"中点画线算法"
void CGraphics_SoftwareView::Middle_alg()
{
	m_chooseAlg = true;
	CDlg_Line dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	if (!(p1[1].x == p1[1].y == p2[1].x == p2[1].y)) {
		dlg.a = p1[1].x - 2; dlg.b = p1[1].y - 2;
		dlg.c = p2[1].x - 2; dlg.d = p2[1].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		p1[1].x = dlg.a + 2; p1[1].y = dlg.b + 2;
		p2[1].x = dlg.c + 2; p2[1].y = dlg.d + 2;
		Invalidate();
	}
}

//响应菜单"Bresenham画线算法"
void CGraphics_SoftwareView::Bresenham_alg()
{
	m_chooseAlg = true;
	m_showWeb = true;
	CDlg_Line dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);

	if (!(p1[2].x == p1[2].y == p2[2].x == p2[2].y)) {
		dlg.a = p1[2].x - 2; dlg.b = p1[2].y - 2;
		dlg.c = p2[2].x - 2; dlg.d = p2[2].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		p1[2].x = dlg.a + 2; p1[2].y = dlg.b + 2;
		p2[2].x = dlg.c + 2; p2[2].y = dlg.d + 2;
		Invalidate();
	}
}

//响应菜单"清除直线"
void CGraphics_SoftwareView::_Clear()
{
	m_chooseAlg = false;
	p1[0].x = p1[0].y = p1[1].x = p1[1].y = p1[2].x = p1[2].y = 0;
	p2[0].x = p2[0].y = p2[1].x = p2[1].y = p2[2].x = p2[2].y = 0;
	Invalidate();
}

//响应菜单"三者比较"
void CGraphics_SoftwareView::Compare_Line_Alg()
{
	m_chooseAlg = true;
	CDlg_Line dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	if (dlg.DoModal() == IDOK) {
		p1[0].x = p1[1].x = p1[2].x = dlg.a + 2; p1[0].y = p1[1].y = p1[2].y = dlg.b + 2;
		p2[0].x = p2[1].x = p2[2].x = dlg.c + 2; p2[0].y = p2[1].y = p2[2].y = dlg.d + 2;
		Invalidate();
	}
}

//画圆菜单
//响应菜单"中点画圆算法"
void CGraphics_SoftwareView::Middle_Circle_Alg()
{
	CDlg_Eclipse m_dlgEclipse;
	m_dlgEclipse.SetBackgroundColor(INSIDE_COLOR);
	if (R[0]) {
		m_dlgEclipse.x = O[0].x - 2; m_dlgEclipse.y = O[0].y - 2;
		m_dlgEclipse.r = R[0];
	}
	if (m_dlgEclipse.DoModal() == IDOK) {
		O[0].x = m_dlgEclipse.x + 2; O[0].y = m_dlgEclipse.y + 2;
		R[0] = m_dlgEclipse.r;
		Invalidate();
	}
}

//响应菜单"清除圆或椭圆"
void CGraphics_SoftwareView::Clear_Circle()
{
	m_showWeb = false;
	O[2].x = O[2].y = O[0].x = O[0].y = O[1].x = O[1].y = 0;
	R[0] = R[1] = 0;
	A = B = 0;
	Invalidate();
}

//响应菜单"Bresenham画圆算法"
void CGraphics_SoftwareView::Bresenham_Circle()
{
	m_showWeb = true;
	CDlg_Eclipse m_dlgEclipse;
	m_dlgEclipse.SetBackgroundColor(INSIDE_COLOR);
	if (R[1]) {
		m_dlgEclipse.x = O[1].x - 2; m_dlgEclipse.y = O[1].y - 2;
		m_dlgEclipse.r = R[1];
	}
	if (m_dlgEclipse.DoModal() == IDOK) {
		O[1].x = m_dlgEclipse.x + 2; O[1].y = m_dlgEclipse.y + 2;
		R[1] = m_dlgEclipse.r;
		Invalidate();
	}
}

//响应菜单"二者比较"
void CGraphics_SoftwareView::Compare_Circle_Alg()
{
	m_showWeb = true;
	CDlg_Eclipse m_dlgEclipse;
	m_dlgEclipse.SetBackgroundColor(INSIDE_COLOR);
	if (R[0] == R[1] != 0 && O[0].x == O[1].x && O[0].y == O[1].y) {
		m_dlgEclipse.x = O[0].x - 2; m_dlgEclipse.y = O[0].y - 2;
		m_dlgEclipse.r = R[0];
	}
	if (m_dlgEclipse.DoModal() == IDOK) {
		O[0].x = O[1].x = m_dlgEclipse.x + 2; O[0].y = O[1].y = m_dlgEclipse.y + 2;
		R[0] = R[1] = m_dlgEclipse.r;
		Invalidate();
	}
}

//响应菜单"中点画圆法画椭圆"
void CGraphics_SoftwareView::MidPoint_Eclipse()
{
	m_showWeb = true;
	CDlg_Eclipse m_dlgEclipse;
	m_dlgEclipse.SetBackgroundColor(INSIDE_COLOR);
	if (A && B) {
		m_dlgEclipse.a = A; m_dlgEclipse.b = B;
		m_dlgEclipse.x = O[2].x - 2; m_dlgEclipse.y = O[2].y - 2;
	}
	if (m_dlgEclipse.DoModal() == IDOK) {
		A = m_dlgEclipse.a; B = m_dlgEclipse.b;
		O[2].x = m_dlgEclipse.x + 2; O[2].y = m_dlgEclipse.y + 2;
		Invalidate();
	}
}

//多边形输入菜单
//五边形的输入
void CGraphics_SoftwareView::OnPantagon_filling()
{
	Dlg_polygon dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	number = 5;
	if (Point[0].x != -1 || Point[0].y != -1) {
		dlg.ax = Point[0].x - 2; dlg.ay = Point[0].y - 2;
		dlg.bx = Point[1].x - 2; dlg.by = Point[1].y - 2;
		dlg.cx = Point[2].x - 2; dlg.cy = Point[2].y - 2;
		dlg.dx = Point[3].x - 2; dlg.dy = Point[3].y - 2;
		dlg.ex = Point[4].x - 2; dlg.ey = Point[4].y - 2;																					
	}
	if (dlg.DoModal() == IDOK) {
		Point[0].x = dlg.ax + 2; Point[0].y = dlg.ay + 2;
		Point[1].x = dlg.bx + 2; Point[1].y = dlg.by + 2;
		Point[2].x = dlg.cx + 2; Point[2].y = dlg.cy + 2;
		Point[3].x = dlg.dx + 2; Point[3].y = dlg.dy + 2;
		Point[4].x = dlg.ex + 2; Point[4].y = dlg.ey + 2;
		m_polygon = true;
		Invalidate();
	}
}

//六边形的输入
void CGraphics_SoftwareView::OnSix_Side()
{
	Dlg_polygon dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	number = 6;
	if (Point[0].x != -1 || Point[0].y != -1) {
		dlg.ax = Point[0].x - 2; dlg.ay = Point[0].y - 2;
		dlg.bx = Point[1].x - 2; dlg.by = Point[1].y - 2;
		dlg.cx = Point[2].x - 2; dlg.cy = Point[2].y - 2;
		dlg.dx = Point[3].x - 2; dlg.dy = Point[3].y - 2;
		dlg.ex = Point[4].x - 2; dlg.ey = Point[4].y - 2;
		dlg.fx = Point[5].x - 2; dlg.fy = Point[5].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		Point[0].x = dlg.ax + 2; Point[0].y = dlg.ay + 2;
		Point[1].x = dlg.bx + 2; Point[1].y = dlg.by + 2;
		Point[2].x = dlg.cx + 2; Point[2].y = dlg.cy + 2;
		Point[3].x = dlg.dx + 2; Point[3].y = dlg.dy + 2;
		Point[4].x = dlg.ex + 2; Point[4].y = dlg.ey + 2;
		Point[5].x = dlg.fx + 2; Point[5].y = dlg.fy + 2;
		m_polygon = true;
		Invalidate();
	}
}

//七边形的输入
void CGraphics_SoftwareView::Onseven_side()
{
	Dlg_polygon dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	number = 7;
	if (Point[0].x != -1 || Point[0].y != -1) {
		dlg.ax = Point[0].x - 2; dlg.ay = Point[0].y - 2;
		dlg.bx = Point[1].x - 2; dlg.by = Point[1].y - 2;
		dlg.cx = Point[2].x - 2; dlg.cy = Point[2].y - 2;
		dlg.dx = Point[3].x - 2; dlg.dy = Point[3].y - 2;
		dlg.ex = Point[4].x - 2; dlg.ey = Point[4].y - 2;
		dlg.fx = Point[5].x - 2; dlg.fy = Point[5].y - 2;
		dlg.gx = Point[6].x - 2; dlg.gy = Point[6].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		Point[0].x = dlg.ax + 2; Point[0].y = dlg.ay + 2;
		Point[1].x = dlg.bx + 2; Point[1].y = dlg.by + 2;
		Point[2].x = dlg.cx + 2; Point[2].y = dlg.cy + 2;
		Point[3].x = dlg.dx + 2; Point[3].y = dlg.dy + 2;
		Point[4].x = dlg.ex + 2; Point[4].y = dlg.ey + 2;
		Point[5].x = dlg.fx + 2; Point[5].y = dlg.fy + 2;
		Point[6].x = dlg.gx + 2; Point[6].y = dlg.gy + 2;
		m_polygon = true;
		Invalidate();
	}
}

//八变形的输入
void CGraphics_SoftwareView::OnEight_Side()
{
	Dlg_polygon dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	number = 8;
	if (Point[0].x != -1 || Point[0].y != -1) {
		dlg.ax = Point[0].x - 2; dlg.ay = Point[0].y - 2;
		dlg.bx = Point[1].x - 2; dlg.by = Point[1].y - 2;
		dlg.cx = Point[2].x - 2; dlg.cy = Point[2].y - 2;
		dlg.dx = Point[3].x - 2; dlg.dy = Point[3].y - 2;
		dlg.ex = Point[4].x - 2; dlg.ey = Point[4].y - 2;
		dlg.fx = Point[5].x - 2; dlg.fy = Point[5].y - 2;
		dlg.gx = Point[6].x - 2; dlg.gy = Point[6].y - 2;
		dlg.hx = Point[7].x - 2; dlg.hy = Point[7].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		Point[0].x = dlg.ax + 2; Point[0].y = dlg.ay + 2;
		Point[1].x = dlg.bx + 2; Point[1].y = dlg.by + 2;
		Point[2].x = dlg.cx + 2; Point[2].y = dlg.cy + 2;
		Point[3].x = dlg.dx + 2; Point[3].y = dlg.dy + 2;
		Point[4].x = dlg.ex + 2; Point[4].y = dlg.ey + 2;
		Point[5].x = dlg.fx + 2; Point[5].y = dlg.fy + 2;
		Point[6].x = dlg.gx + 2; Point[6].y = dlg.gy + 2;
		Point[7].x = dlg.hx + 2; Point[7].y = dlg.hy + 2;
		m_polygon = true;
		Invalidate();
	}
}

//九边形的输入
void CGraphics_SoftwareView::OnNine_Side()
{
	Dlg_polygon dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	number = 9;
	if (Point[0].x != -1 || Point[0].y != -1) {
		dlg.ax = Point[0].x - 2; dlg.ay = Point[0].y - 2;
		dlg.bx = Point[1].x - 2; dlg.by = Point[1].y - 2;
		dlg.cx = Point[2].x - 2; dlg.cy = Point[2].y - 2;
		dlg.dx = Point[3].x - 2; dlg.dy = Point[3].y - 2;
		dlg.ex = Point[4].x - 2; dlg.ey = Point[4].y - 2;
		dlg.fx = Point[5].x - 2; dlg.fy = Point[5].y - 2;
		dlg.gx = Point[6].x - 2; dlg.gy = Point[6].y - 2;
		dlg.hx = Point[7].x - 2; dlg.hy = Point[7].y - 2;
		dlg.ix = Point[8].x - 2; dlg.iy = Point[8].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		Point[0].x = dlg.ax + 2; Point[0].y = dlg.ay + 2;
		Point[1].x = dlg.bx + 2; Point[1].y = dlg.by + 2;
		Point[2].x = dlg.cx + 2; Point[2].y = dlg.cy + 2;
		Point[3].x = dlg.dx + 2; Point[3].y = dlg.dy + 2;
		Point[4].x = dlg.ex + 2; Point[4].y = dlg.ey + 2;
		Point[5].x = dlg.fx + 2; Point[5].y = dlg.fy + 2;
		Point[6].x = dlg.gx + 2; Point[6].y = dlg.gy + 2;
		Point[7].x = dlg.hx + 2; Point[7].y = dlg.hy + 2;
		Point[8].x = dlg.ix + 2; Point[8].y = dlg.iy + 2;
		m_polygon = true;
		Invalidate();
	}
}

//十边形的输入
void CGraphics_SoftwareView::OnTen_Side()
{
	Dlg_polygon dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	number = 10;
	if (Point[0].x != -1 || Point[0].y != -1) {
		dlg.ax = Point[0].x - 2; dlg.ay = Point[0].y - 2;
		dlg.bx = Point[1].x - 2; dlg.by = Point[1].y - 2;
		dlg.cx = Point[2].x - 2; dlg.cy = Point[2].y - 2;
		dlg.dx = Point[3].x - 2; dlg.dy = Point[3].y - 2;
		dlg.ex = Point[4].x - 2; dlg.ey = Point[4].y - 2;
		dlg.fx = Point[5].x - 2; dlg.fy = Point[5].y - 2;
		dlg.gx = Point[6].x - 2; dlg.gy = Point[6].y - 2;
		dlg.hx = Point[7].x - 2; dlg.hy = Point[7].y - 2;
		dlg.ix = Point[8].x - 2; dlg.iy = Point[8].y - 2;
		dlg.jx = Point[9].x - 2; dlg.jy = Point[9].y - 2;
	}
	if (dlg.DoModal() == IDOK) {
		Point[0].x = dlg.ax + 2; Point[0].y = dlg.ay + 2;
		Point[1].x = dlg.bx + 2; Point[1].y = dlg.by + 2;
		Point[2].x = dlg.cx + 2; Point[2].y = dlg.cy + 2;
		Point[3].x = dlg.dx + 2; Point[3].y = dlg.dy + 2;
		Point[4].x = dlg.ex + 2; Point[4].y = dlg.ey + 2;
		Point[5].x = dlg.fx + 2; Point[5].y = dlg.fy + 2;
		Point[6].x = dlg.gx + 2; Point[6].y = dlg.gy + 2;
		Point[7].x = dlg.hx + 2; Point[7].y = dlg.hy + 2;
		Point[8].x = dlg.ix + 2; Point[8].y = dlg.iy + 2;
		Point[9].x = dlg.jx + 2; Point[9].y = dlg.jy + 2;
		m_polygon = true;
		Invalidate();
	}
}

//任意点绘制多边形算法
//求两点的距离的平方
int CGraphics_SoftwareView::destence(CPoint a,CPoint b) {
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

//给点的数组选择排序
void CGraphics_SoftwareView::selectSort(CPoint a[],int num) {
	CPoint temp;
	for (int i = 0; i < num; i++) {
		int k = i;
		for (int j = i; j < num; j++) {
			if (a[k].x > a[j].x) {
				k = j;
			}
		}
		if (k != i) {
			temp = a[i];
			a[i] = a[k];
			a[k] = temp;
		}
	}
}

//画多边形的边
void CGraphics_SoftwareView::Draw_Polygon_edge(int num)
{
	CDC *pDC = GetDC();

	//找出x最小和x最大的点
	CPoint Max, Min;
	Max = Min = Point[0];
	for (int i = 0; i < num ; i++) {
			if (Point[i].x > Max.x) {
				Max = Point[i];
			}
			if (Point[i].x < Min.x){ 
				Min = Point[i];
			}
	}

	//找出y介于Max.y和Min.y之下的点p
	//找出y介于Max.y和Min.y之下的点p
	CPoint p[NUM],q[NUM];
	int k = 0, j = 0;
	p[k] = Min;
	q[j] = Min;
	float Line_k = (float)(Max.y - Min.y) / (Max.x - Min.x);
	float Line_b = Min.y - Line_k * Min.x;
	for (int i = 0; i < num; i++) {
		if ((float)Point[i].y < Point[i].x * Line_k + Line_b) {
			k++;
			p[k] = Point[i];//p[k]是位于MinY和MaxY下方的点
		}
		else if ((float)Point[i].y > Point[i].x * Line_k + Line_b){
			j++;
			q[j] = Point[i];//q[j]是位于MinY和MaxY上方的点
		}
	}
	p[++k] = Max;
	q[++j] = Max;
	////设置种子点
	//Point[NUM].x = (Max.x + Min.x) / 2;
	//if (k == 1) {
	//	Point[NUM].y = (Max.y + Min.y) / 2 + 2;
	//}
	//else if(j == 1){
	//	Point[NUM].y = (Max.y + Min.y) / 2 - 2;
	//}
	//else {
	//	Point[NUM].y = (Max.y + Min.y) / 2;
	//}

	//对找到的点的x值进行排序
	if (k > 2)
	selectSort(p, k);
	if (j > 2)
	selectSort(q, j);
	//绘制直线
	for (int i = 0; i < k ; i++) {
		//MessageBox(_T("画边缘"));
		DDA_Alg(pDC, p[i], p[i+1], SIDE_COLOR);
	}
	for (int i = 0; i < j ; i++) {
		//MessageBox(_T("画边缘"));

		DDA_Alg(pDC, q[i], q[i+1],SIDE_COLOR);
	}
	for (int i = 0; i <= k; i++) {
		Point[i] = p[i];
	}
	int x = j -1;
	for (int i = k + 1; i < number; i++) {
		Point[i] = q[x];
		x--;
	}
}

//多边形的清除
void CGraphics_SoftwareView::OnPolygon_clear()
{
	number = number_n = 0;
	m_polygon = m_polygon_n = false;
	Point[0].x = Point[0].y = -1;
	Point[1] = Point[2] = Point[3] = Point[4] = Point[5]
		= Point[6] = Point[7] = Point[8] = Point[9] = Point[10]
		= Point[0];
	for (int i = 0; i < NUM*width; i++) {
		m_point[i].x = -1;
		m_point[i].y = -1;
	}
	Invalidate();
}

//输入多边形的点数
void CGraphics_SoftwareView::On_N_Side()
{
	CNumber_of_Point dlg;
	dlg.SetBackgroundColor(INSIDE_COLOR);
	if (dlg.DoModal() == IDOK) {
		number_n = dlg.m_Num_point;
		m_polygon_n = true;
	}
}

//多边形填充算法
//扫描线填充算法
void CGraphics_SoftwareView::OnFill_Alg_1()
{
	typedef struct XET										//结点，建立边表NET和活性边表AET
	{
		float x;
		float dx, ymax;
		struct XET* next;
	}AET, NET;
	int num_n=0;
	double x[NUM*width];
	double y[NUM*width];


	if (m_polygon) {
		num_n = number;	
		for (int i = 0; i < num_n; i++) {
			x[i] = Point[i].x;
			y[i] = Point[i].y;
		}
	}
	if (m_polygon_n) {
		num_n = number_n;
		for (int i = 0; i < num_n; i++) {
			x[i] = m_point[i].x;
			y[i] = m_point[i].y;
		}
	}
	//存放输入的点


	int MaxY = 0;						//找到最大和最小Y
	int MinY = 2000;
	for (int i = 0; i < num_n; i++)
	{
		if (y[i] > MaxY)
		{
			MaxY = (int)y[i];
		}

		if (y[i] < MinY)
		{
			MinY = (int)y[i];
		}
	}


	AET *pAET = new AET;				//初始化边表和新边表
	pAET->next = NULL;
	NET *pNET[1024];				
	//将各个pNET连接起来
	for (int i = MinY; i <= MaxY; i++)
	{
		pNET[i] = new NET;
		pNET[i]->next = NULL;
	}
	//*************************************************************************
	for (int i = MinY; i <= MaxY; i++)			//从MinY扫描到MaxX,并建立边表，即为边的性质
	{
		for (int j = 0; j < num_n; j++)		//从第一个顶点遍历
		{
			if (y[j] == i)						//判断是否和当前扫描线相交，扫描到顶点
			{
				if (y[(j - 1 + num_n) % num_n] > y[j])	//判断改顶点的前一个点是否是在改顶点上方
				{
					NET *p = new NET;
					p->x = (float)x[j];//记录横坐标
					p->ymax = (float)y[(j - 1 + num_n) % num_n];//记录纵坐标
					p->dx = ((float)x[(j - 1 + num_n) % num_n] - (float)x[j]) / ((float)y[(j - 1 + num_n) % num_n] - (float)y[j]);//记录斜率
					//在当前节点插入新节点
					p->next = pNET[i]->next;	
					pNET[i]->next = p;
				}

				if (y[(j + 1 + num_n) % num_n] > y[j])	//判断该顶点的下一个点是否在改顶点上方
				{
					NET *p = new NET;
					p->x = (float)x[j];
					p->ymax = (float)y[(j + 1 + num_n) % num_n];
					p->dx = ((float)x[(j + 1 + num_n) % num_n] - (float)x[j]) / ((float)y[(j + 1 + num_n) % num_n] - (float)y[j]);
					//在当前节点插入新节点
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
			}
		}
	}

	for (int i = MinY ; i <= MaxY; i++)				//	建立并更新活性边表AET
												// for循环中按下面的流程而不是《计算机图形学》徐长青第二版P38中Polygonfill算法中的while循环中的流程，
	{
		//CString str;
		////_stprintf(str, "数值=%d", n);
		//str.Format(_T("第%d条扫描线"), i - MinY);
		//MessageBox(str);
		// 这样可以处理书中的边界问题，无需开始时进行边缩短
		//计算新的交点x,更新AET********************************************************/
		NET *p = pAET->next;
		while (p != NULL)
		{
			p->x = p->x + p->dx;

			p = p->next;
		}
		//更新后新AET先排序*************************************************************/  
		//断表排序,不再开辟空间
		AET *tq = pAET;
		p = pAET->next;
		tq->next = NULL;

		while (p != NULL)
		{
			while (tq->next != NULL && p->x >= tq->next->x)
			{
				tq = tq->next;
			}
			//插入p节点
			NET *s = p->next;		//s是p的下一个节点
			p->next = tq->next;		//让p的下个节点为tq的下一个节点
			tq->next = p;			//tq的下一个节点为p
			p = s;					//让p指向s
			tq = pAET;
		}

		//(改进算法)先从AET表中删除ymax==i的结点****************************************/  
		AET *q = pAET;
		p = q->next;
		while (p != NULL)
		{
			if (p->ymax == i)
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}

		//将NET中的新点加入AET,并用插入法按X值递增排序**********************************/	 
		p = pNET[i]->next;
		q = pAET;
		while (p != NULL)
		{
			while (q->next != NULL && p->x >= q->next->x)//不递增时，跳过该结点
			{
				q = q->next;
			}
			NET	*s = p->next;		//s指向p的下一个结点
			p->next = q->next;		//p的下一个结点跟新
			q->next = p;			//q的下一个结点更新为p
			p = s;					//p结点更新
			q = pAET;				//更新q结点
		}

		/******配对填充颜色***************************************************************/
		p = pAET->next;
		if (i != MinY) {
			while (p != NULL &&	p->next != NULL)
			{
				CDC	*pDC = GetDC();
				for (float j = p->x; j <= p->next->x; j++)	//
				{
					Rect(pDC,round(j),i,INSIDE_COLOR);
				}
				p = p->next->next;		//考虑端点情况  
			}
		}
	}
	Draw_polygon();
}

//边填充算法
void CGraphics_SoftwareView::OnEageMark_Fill()
{
	bool Insideflag = false;
	HDC dc;
	dc = ::GetDC(m_hWnd);
	CDC *pDC;
	pDC = GetDC();
	
	//找出y的最大值和最小值
	int min_y = 0, max_y = 0, min_x = 0, max_x = 0;
	if (m_polygon) {
		min_y = max_y = Point[0].y;
		for (int i = 0; i < number; i++) {
			if (Point[i].x < min_x) {
				min_x = Point[i].x;
			}
			if (Point[i].x > max_x) {
				max_x = Point[i].x;
			}
			if (Point[i].y > max_y) {
				max_y = Point[i].y;
			}
			if (Point[i].y < min_y) {
				min_y = Point[i].y;
			}
		}
	}
	if (m_polygon_n) {
		min_y = max_y = m_point[0].y;
		for (int i = 0; i < number_n; i++) {
			if (m_point[i].x < min_x) {
				min_x = m_point[i].x;
			}
			if (m_point[i].x > max_x) {
				max_x = m_point[i].x;
			}
			if (m_point[i].y > max_y) {
				max_y = m_point[i].y;
			}
			if (m_point[i].y < min_y) {
				min_y = m_point[i].y;
			}
		}
	}
	//填充多边形
	for (int i = min_y + 1; i < max_y; i++) {
		int p_side_x[NUM*15];//记录该条扫描线扫到边界的横坐标
		memset(p_side_x,-1,NUM*15);//初始化每个值为 -1
		int k = 0;//记录边界点的个数
		int key = 0;
		for (int j = min_x; j <= max_x; j++) {
			if (GetPixel(dc, (j + 2)*width + width/2, (i)*width + width/2) == SIDE_COLOR) {
					p_side_x[k] = j;//找到一个边界点
					k++;//计数器加一
			}
			//if (k >= 1 && p_side_x[k - 1] + 1 < p_side_x[k]) {
			//	key++;
			//}
		}
//		if (key == 1) {
			for (int j = 0; j < k; j++) {
				for (int l = p_side_x[j] + 1; l < p_side_x[j + 1]; l++) {//当两点之间有空隙时填充

					Rect(pDC, l + 2, i, INSIDE_COLOR);
				}
			}
		//}

	}
}

//种子填充算法
void CGraphics_SoftwareView::OnSeed_Fill()
{
	GetSeed();
	HDC hdc;//用于获得像素点的颜色
	hdc = ::GetDC(m_hWnd);
	CDC *pDC;//用于给像素点着色
	pDC = GetDC();
	if (Seed.x != -1) {
		BoundaryFill_4(hdc, pDC, Seed.x, Seed.y);
	}
}

//种子填充递归函数
void CGraphics_SoftwareView::BoundaryFill_4(HDC hdc, CDC *pDC,int x, int y)
{
	int current;
	//获取当前像素点的颜色值
	current = GetPixel(hdc, x*width + width / 2, y*width + width / 2);
	if ((current != SIDE_COLOR) && current != INSIDE_COLOR){
		Rect(pDC, x, y,INSIDE_COLOR);
		//向上扫描
		BoundaryFill_4(hdc, pDC, x, y + 1);
		//向左扫描
		BoundaryFill_4(hdc, pDC, x - 1, y);
		//向右扫描
		BoundaryFill_4(hdc, pDC, x + 1, y);
		//向下扫描
		BoundaryFill_4(hdc, pDC, x, y - 1);
	}
}

//扫描线种子填充算法
void CGraphics_SoftwareView::On_Scanline_seed_fill()
{
	CStack S;
	CDC *pDC = GetDC();
	GetSeed();
	bool bSpanFill;
	S.Push(Seed);
	int xleft, xright;//记录区间最左端与最右端像素的横坐标
	CPoint PopPoint, PointTemp;//出栈点和辅助运算点
	while (S.empty())//如果栈不为空
	{
		PopPoint=S.Pop();//让栈顶点出栈
		//如果该点是已填充的点则视为无效点，返回循环获取下一个栈顶点
		if (pDC->GetPixel(PopPoint.x * width + width/2, PopPoint.y * width + width/2) == INSIDE_COLOR)
			continue;
		PointTemp = PopPoint;
		//向右填充
		while (pDC->GetPixel(PointTemp.x * width + width/2,PointTemp.y * width + width/2) != SIDE_COLOR && 
			pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != INSIDE_COLOR)
		{
			Rect(pDC, PointTemp.x, PointTemp.y, INSIDE_COLOR);
			PointTemp.x++;
		}
		xright = PointTemp.x - 1;//记录右边界像素点的横坐标
		//向左填充
		PointTemp.x = PopPoint.x - 1;
		while (pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != SIDE_COLOR &&
			pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != INSIDE_COLOR)
		{
			Rect(pDC, PointTemp.x, PointTemp.y, INSIDE_COLOR);
			PointTemp.x--;
		}
		xleft = PointTemp.x + 1;//记录左边界像素点的横坐标
		//处理上一条扫描线
		PointTemp.x = xleft;
		PointTemp.y = PointTemp.y + 1;//上移
		while (PointTemp.x < xright)
		{
			bSpanFill = FALSE;
			//向上找到
			while (pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != SIDE_COLOR &&
				pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != INSIDE_COLOR)
			{
				bSpanFill = TRUE;
				PointTemp.x++;
			}
			if (bSpanFill)
			{
				if (PointTemp.x == xright && pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != SIDE_COLOR &&
					pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != INSIDE_COLOR)
					PopPoint = PointTemp;
				else
				{
					PopPoint.x = PointTemp.x - 1;
					PopPoint.y = PointTemp.y;
				}
				S.Push(PopPoint);
				bSpanFill = FALSE;
			}
			while ((pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) == SIDE_COLOR && PointTemp.x < xright) ||
				(pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) == INSIDE_COLOR && PointTemp.x < xright)) 
				{
					PointTemp.x++;
				}
		}
		//处理下一条扫描线
		PointTemp.x = xleft;
		PointTemp.y = PointTemp.y - 2;
		while (PointTemp.x < xright)
		{
			bSpanFill = FALSE;
			while (pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != SIDE_COLOR &&
				pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != INSIDE_COLOR)
			{
				bSpanFill = TRUE;
				PointTemp.x++;
			}
			if (bSpanFill)
			{
				if (PointTemp.x == xright && pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != SIDE_COLOR &&
					pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) != INSIDE_COLOR)
					PopPoint = PointTemp;
				else
				{
					PopPoint.x = PointTemp.x - 1;
					PopPoint.y = PointTemp.y;
				}
				S.Push(PopPoint);
				bSpanFill = FALSE;
			}
			while ((pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) == SIDE_COLOR && PointTemp.x < xright) ||
				(pDC->GetPixel(PointTemp.x * width + width / 2, PointTemp.y * width + width / 2) == INSIDE_COLOR && PointTemp.x < xright))
				PointTemp.x++;
		}
	}
}

//初始化种子函数
void CGraphics_SoftwareView::GetSeed()
{
	int max_x, min_x, max_y, min_y;
	if (m_polygon) {
		min_x = max_x = Point[0].x;
		min_y = max_y = Point[0].y;
		//获取多边形所在的矩形区域
		for (int i = 0; i < number; i++) {
			if (Point[i].x < min_x) {
				min_x = Point[i].x;
			}
			if (Point[i].x > max_x) {
				max_x = Point[i].x;
			}
			if (Point[i].y < min_y) {
				min_y = Point[i].y;
			}
			if (Point[i].y > max_y) {
				max_y = Point[i].y;
			}
		}
		//默认中心点为种子
		Seed.x = (min_x + max_x) / 2;
		Seed.y = (min_y + max_y) / 2;
		if(Isinside(Seed)==true){}//中心点不在多边形内时，随机生成

		else {
			int dx = max_x - min_x;
			int dy = max_y - min_y;
			do {
				srand((unsigned)time(NULL));
				Seed.x = rand() % dx + min_x;
				srand((unsigned)time(NULL));
				Seed.y = rand() % dy + min_y;
			}
			while (Isinside(Seed)==true);//直到随机点在多边形内
		}

	}
	if (m_polygon_n) {
		//获取多边形所在的矩形区域
		min_x = max_x = m_point[0].x;
		min_y = max_y = m_point[0].y;
		for (int i = 0; i < number_n; i++) {
			if (m_point[i].x < min_x) {
				min_x = m_point[i].x;
			}
			if (m_point[i].x > max_x) {
				max_x = m_point[i].x;
			}
			if (m_point[i].y < min_y) {
				min_y = m_point[i].y;
			}
			if (m_point[i].y > max_y) {
				max_y = m_point[i].y;
			}
		}
		//默认中心点为种子
		Seed.x = (min_x + max_x) / 2;
		Seed.y = (min_y + max_y) / 2;
		if (Isinside(Seed) == true) {}//中心点不在多边形内时，随机生成
		else {
			int dx = max_x - min_x;
			int dy = max_y - min_y;
			do {
				srand((unsigned)time(NULL));
				Seed.x = rand() % dx + min_x;
				srand((unsigned)time(NULL));
				Seed.y = rand() % dy + min_y;
			} 
			while (Isinside(Seed)==true);
		}
	}
}

//判断生成的种子点是否在多边形内，是返回true，否返回false
bool CGraphics_SoftwareView::Isinside(CPoint point) {
	int x, y;
	CDC *pDC;
	pDC = GetDC();
	//向右扫描
	x = point.x;
	y = point.y;
	do {
		x++;
		if (x==156) {
			MessageBox(_T("种子点不对"));
			return false;
		}
	} while (pDC->GetPixel(x*width + width/2, y*width + width / 2) == SIDE_COLOR);
	//向左扫描
	x = point.x;
	y = point.y;
	do {
		x--;
		if (x == -1) {
			MessageBox(_T("种子点不对"));
			return false;
		}
	} while (pDC->GetPixel(x*width + width / 2, y*width + width / 2) == SIDE_COLOR);
	//向下扫描
	x = point.x;
	y = point.y;
	do {
		y--;
		if (y == -1) {
			MessageBox(_T("种子点不对"));
			return false;
		}
	} while (pDC->GetPixel(x*width + width / 2, y*width + width / 2) == SIDE_COLOR);
	//向上扫描
	x = point.x;
	y = point.y;
	do {
		y++;
		if (y == 76) {
			MessageBox(_T("种子点不对"));
			return false;
		}
	} while (pDC->GetPixel(x*width + width / 2, y*width + width / 2) == SIDE_COLOR);

	return true;
}

//栅栏填充算法
void CGraphics_SoftwareView::On_FanceFill()
{
	CDC *pDC = GetDC();
	double k, x;
	int max_y, min_y;
	if (m_polygon_n) {
		int max_x = m_point[0].x;
		for (int i = 0; i < number_n; i++) {
			if (max_x < m_point[i].x) {
				max_x = m_point[i].x;
			}
		}
		for (int i = 0; i < number_n; i++) {
			k = (double)(m_point[(i + 1) % number_n].x - m_point[i].x) / (m_point[(i + 1) % number_n].y - m_point[i].y);
			if (m_point[i].y > m_point[(i + 1) % number_n].y) {
				min_y = m_point[(i + 1) % number_n].y;
				max_y = m_point[i].y;
				x = (double)m_point[(i + 1) % number_n].x;
			}
			else {
				max_y = m_point[(i + 1) % number_n].y;
				min_y = m_point[i].y;
				x = (double)m_point[i].x;
			}
			for (int y = min_y; y < max_y; y++) {
				for (int m = round(x + 0.5); m < max_x; m++) {
					//Sleep(10);
					if (pDC->GetPixel(m*width + width / 2, y*width + width / 2) == INSIDE_COLOR && 
						pDC->GetPixel(m*width + width / 2, y*width + width / 2) != SIDE_COLOR) {
						Rect(pDC,m,y,RGB(255,255,255));
					}
					else if(pDC->GetPixel(m*width + width / 2, y*width + width / 2) != SIDE_COLOR){
						Rect(pDC, m, y, INSIDE_COLOR);
					}
				}
				x += k;
			}
		}
	}
}

//画多边形，用于重绘
void CGraphics_SoftwareView::Draw_polygon() {
	CDC *pDC;
	pDC = GetDC();
	for (int i = 1; i < number_n; i++) {
		DDA_Alg(pDC, m_point[i], m_point[i - 1], SIDE_COLOR);
		if (i == number_n - 1) {
			DDA_Alg(pDC, m_point[0], m_point[number_n - 1], SIDE_COLOR);
		}
	}
}

//响应左键按下的函数
void CGraphics_SoftwareView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDC *pDC;
	pDC = GetDC();
	m_bDraw = true;
	Seed = point;
	Rect(pDC, point.x / width, point.y / width, POINT_COLOR);
	if (m_point[number_n - 1].x == -1) {
		Rect(pDC, point.x / width, point.y / width, POINT_COLOR);
		for (int i = 0; i < number_n; i++) {
			if (m_point[i].x == -1) {
				m_point[i].x = point.x / width;
				m_point[i].y = point.y / width;
				if (i >= 1) {
					DDA_Alg(pDC, m_point[i], m_point[i - 1], SIDE_COLOR);
				}
				if (i == number_n - 1) {
					DDA_Alg(pDC, m_point[0], m_point[number_n - 1], SIDE_COLOR);
				}
				break;
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

//响应右键按下的函数
void CGraphics_SoftwareView::OnRButtonDown(UINT nFlags, CPoint point)
{
	MessageBox(_T("刷新！"));
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}

//响应鼠标移动函数
void CGraphics_SoftwareView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值						//判断是否选择的事随意曲线
		CPen pen(0, 1, SIDE_COLOR);	//创建画笔，设定相关参数
		CDC *pDC = GetDC();
		pDC->SelectObject(&pen);
		if (m_bDraw == true) {						//鼠标左键已按下
			Rect(pDC,point.x/width,point.y/width,SIDE_COLOR);				//绘图
		}
	CView::OnMouseMove(nFlags, point);
}

//左键抬起
void CGraphics_SoftwareView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDraw = false;
	CView::OnLButtonUp(nFlags, point);
}

//显示网格
void CGraphics_SoftwareView::On_Web()
{
	m_showWeb = true;
	Invalidate();
}

//清除网格
void CGraphics_SoftwareView::On_Webclear()
{
	m_showWeb = false;
	Invalidate();
}

//显示坐标系
void CGraphics_SoftwareView::showCoordinateAxis()
{
	m_axis = true;
	CDC *pDC = GetDC();

	pDC->MoveTo(10,350);//x轴
	pDC->LineTo(1200,350);
	pDC->MoveTo(1192, 345);
	pDC->LineTo(1200, 350);
	pDC->MoveTo(1200, 350);
	pDC->LineTo(1192, 355);//正方向
	pDC->MoveTo(650,10);//y轴
	pDC->LineTo(650,650);
	pDC->MoveTo(650, 10);
	pDC->LineTo(645,18);
	pDC->MoveTo(650, 10);
	pDC->LineTo(655,18);//正方向
	pDC->TextOut(635, 355, _T("O"));
	pDC->TextOut(1200, 355, _T("X"));
	pDC->TextOut(635, 10, _T("Y"));
	pDC->ReleaseOutputDC();
}

//隐藏坐标系
void CGraphics_SoftwareView::On_closeCoordinate()
{
	m_axis = false;
	m_rect = false;
	Invalidate();
}

//矩形显示
void CGraphics_SoftwareView::On_Rectangle()
{
	m_rect = true;
	m_num = 4;
	P[0].x = -100 ; P[0].y = -50;
	P[1].x = 100; P[1].y = -50 ;
	P[2].x = 100 ; P[2].y = 50 ;
	P[3].x = -100 ; P[3].y = 50 ;
	trans.SetMat(P, m_num);
	Invalidate(TRUE);
}

//六边形显示
void CGraphics_SoftwareView::Onhexagon()
{
	m_rect = true;
	m_num = 6;
	P[0].x = -40; P[0].y = 69.2;
	P[1].x = 40; P[1].y = 69.2;
	P[2].x = 80; P[2].y = 0;
	P[3].x = 40; P[3].y = -69.2;
	P[4].x = -40; P[4].y = -69.2;
	P[5].x = -80; P[5].y = 0;
	trans.SetMat(P, m_num);
	Invalidate(TRUE);
}

//八边形显示
void CGraphics_SoftwareView::Onoctagon()
{
	m_rect = true;
	m_num = 8;
	P[0].x = -15; P[0].y = 36.2;
	P[1].x = 15; P[1].y = 36.2;
	P[2].x = 36.2; P[2].y = 15;
	P[3].x = 36.2; P[3].y = -15;
	P[4].x = 15; P[4].y = -36.2;
	P[5].x = -15; P[5].y = -36.2;
	P[6].x = -36.2; P[6].y = -15;
	P[7].x = -36.2; P[7].y = 15;
	trans.SetMat(P, m_num);
	Invalidate(TRUE);
}

//画多边形，用于变换
void CGraphics_SoftwareView::DrawPolygon()
{
	CDC *pDC = GetDC();
	CPoint_2D t;
	for (int i = 0; i<m_num; i++)//绘制多边形
	{
		if (i == 0)
		{
			pDC->MoveTo(P[i].x + DX,P[i].y + DY );
			t = P[i];
		}
		else
		{
			pDC->LineTo(P[i].x + DX, P[i].y + DY);
		}
	}
	pDC->LineTo(t.x + DX, t.y + DY);//闭合多边形
}

//二维图形变换
//向左移动
void CGraphics_SoftwareView::On_left()
{
	trans.Translate(-10, 0);
	Invalidate(TRUE);
}

//向右运动
void CGraphics_SoftwareView::OnTright()
{
	trans.Translate(10, 0);
	Invalidate(TRUE);
}

//向下运动
void CGraphics_SoftwareView::OnTdown()
{
	trans.Translate(0, 10);
	Invalidate(TRUE);
}

//向上运动
void CGraphics_SoftwareView::OnTup()
{
	trans.Translate(0, -10);
	Invalidate(TRUE);
}

//放大
void CGraphics_SoftwareView::OnTincrease()
{
	trans.Scale(2,2);
	Invalidate(TRUE);
}

//缩小
void CGraphics_SoftwareView::OnTdecrease()
{
	trans.Scale(0.5, 0.5);
	Invalidate(TRUE);
}

//设置角度为30度
void CGraphics_SoftwareView::On_Angle_30()
{
	m_Angle = 30;
}

//设置角度为60度
void CGraphics_SoftwareView::On_Angle_60()
{
	m_Angle = 60;
}

//设置角度为90度
void CGraphics_SoftwareView::On_Angle_90()
{
	m_Angle = 90;
}

//设置角度为180度
void CGraphics_SoftwareView::On_Angle_180()
{
	m_Angle = 180;
}

//顺时针旋转
void CGraphics_SoftwareView::OnRclockwise()
{
	if (m_Angle != 0) {
		CPoint_2D p_temp = (P[0] + P[2]) / 2;
		trans.Rotate(m_Angle, p_temp);
		Invalidate(TRUE);
	}
	else {
		MessageBox(_T("请选择旋转的角度！"));
	}

}

//逆时针旋转
void CGraphics_SoftwareView::OnRcunterclockwise()
{
	if (m_Angle != 0) {
		CPoint_2D p_temp = (P[0] + P[2]) / 2;
		trans.Rotate(-m_Angle, p_temp);
		Invalidate(TRUE);
	}
	else {
		MessageBox(_T("请选择旋转的角度！"));
	}
}

//关于X轴对称
void CGraphics_SoftwareView::OnRxaxis()
{
	trans.ReflectX();
	Invalidate(TRUE);
}

//关于Y轴对称
void CGraphics_SoftwareView::OnRyaxis()
{
	trans.ReflectY();
	Invalidate(TRUE);
}

//关于原点对称
void CGraphics_SoftwareView::OnRorg()
{
	trans.ReflectOrg();
	Invalidate(TRUE);
}

//X轴错切
void CGraphics_SoftwareView::OnSxdorectionneg()
{
	trans.Shear(0,1);
	Invalidate(TRUE);
}

void CGraphics_SoftwareView::OnSxdirectionplus()
{
	trans.Shear(0,-1);
	Invalidate(TRUE);
}

//Y轴错切
void CGraphics_SoftwareView::OnSydirectionneg()
{
	trans.Shear(1, 0);
	Invalidate(TRUE);
}

void CGraphics_SoftwareView::OnSydirectionplus()
{
	trans.Shear(-1, 0);
	Invalidate(TRUE);
}

//三维图形变换展示
void CGraphics_SoftwareView::OnTransform_3D()
{
	CTransform_3D_Dlg dlg;
	dlg.DoModal();
}

//三维球体展示
void CGraphics_SoftwareView::OnBall_Display()
{
	CBall_Display_Dlg ball_dlg;
	ball_dlg.DoModal();
}
