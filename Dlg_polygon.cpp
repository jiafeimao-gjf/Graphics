// Dlg_polygon.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphics_Software.h"
#include "Dlg_polygon.h"
#include "afxdialogex.h"


// Dlg_polygon 对话框

IMPLEMENT_DYNAMIC(Dlg_polygon, CDialogEx)

Dlg_polygon::Dlg_polygon(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, ax(0)
	, ay(0)
	, bx(0)
	, by(0)
	, cx(0)
	, cy(0)
	, dx(0)
	, dy(0)
	, ex(0)
	, ey(0)
	, fx(0)
	, fy(0)
	, gx(0)
	, gy(0)
	, hx(0)
	, hy(0)
	, ix(0)
	, iy(0)
	, jx(0)
	, jy(0)
{

}

Dlg_polygon::~Dlg_polygon()
{
}

void Dlg_polygon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ax);
	DDV_MinMaxInt(pDX, ax, 0, 150);
	DDX_Text(pDX, IDC_EDIT8, ay);
	DDV_MinMaxInt(pDX, ay, 0, 75);
	DDX_Text(pDX, IDC_EDIT3, bx);
	DDV_MinMaxInt(pDX, bx, 0, 150);
	DDX_Text(pDX, IDC_EDIT9, by);
	DDV_MinMaxInt(pDX, by, 0, 75);
	DDX_Text(pDX, IDC_EDIT5, cx);
	DDV_MinMaxInt(pDX, cx, 0, 150);
	DDX_Text(pDX, IDC_EDIT11, cy);
	DDV_MinMaxInt(pDX, cy, 0, 75);
	DDX_Text(pDX, IDC_EDIT6, dx);
	DDV_MinMaxInt(pDX, dx, 0, 150);
	DDX_Text(pDX, IDC_EDIT12, dy);
	DDV_MinMaxInt(pDX, dy, 0, 75);
	DDX_Text(pDX, IDC_EDIT10, ex);
	DDV_MinMaxInt(pDX, ex, 0, 150);
	DDX_Text(pDX, IDC_EDIT13, ey);
	DDV_MinMaxInt(pDX, ey, 0, 75);
	DDX_Text(pDX, IDC_EDIT2, fx);
	DDV_MinMaxInt(pDX, fx, 0, 150);
	DDX_Text(pDX, IDC_EDIT16, fy);
	DDV_MinMaxInt(pDX, fy, 0, 75);
	DDX_Text(pDX, IDC_EDIT4, gx);
	DDV_MinMaxInt(pDX, gx, 0, 150);
	DDX_Text(pDX, IDC_EDIT17, gy);
	DDV_MinMaxInt(pDX, gy, 0, 75);
	DDX_Text(pDX, IDC_EDIT14, hx);
	DDV_MinMaxInt(pDX, hx, 0, 150);
	DDX_Text(pDX, IDC_EDIT18, hy);
	DDV_MinMaxInt(pDX, hy, 0, 75);
	DDX_Text(pDX, IDC_EDIT7, ix);
	DDV_MinMaxInt(pDX, ix, 0, 150);
	DDX_Text(pDX, IDC_EDIT19, iy);
	DDV_MinMaxInt(pDX, iy, 0, 75);
	DDX_Text(pDX, IDC_EDIT15, jx);
	DDV_MinMaxInt(pDX, jx, 0, 150);
	DDX_Text(pDX, IDC_EDIT20, jy);
	DDV_MinMaxInt(pDX, jy, 0, 75);
}


BEGIN_MESSAGE_MAP(Dlg_polygon, CDialogEx)
END_MESSAGE_MAP()


// Dlg_polygon 消息处理程序
