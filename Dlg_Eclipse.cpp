// Dlg_Eclipse.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphics_Software.h"
#include "Dlg_Eclipse.h"
#include "afxdialogex.h"


// CDlg_Eclipse 对话框

IMPLEMENT_DYNAMIC(CDlg_Eclipse, CDialogEx)

CDlg_Eclipse::CDlg_Eclipse(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, x(0)
	, y(0)
	, a(0)
	, b(0)
	, r(0)
{

}

CDlg_Eclipse::~CDlg_Eclipse()
{
}

void CDlg_Eclipse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, x);
	DDX_Text(pDX, IDC_EDIT2, y);
	DDX_Text(pDX, IDC_EDIT6, a);
	DDV_MinMaxFloat(pDX, a, 0, 75);
	DDX_Text(pDX, IDC_EDIT7, b);
	DDV_MinMaxFloat(pDX, b, 0, 35);
	DDX_Text(pDX, IDC_EDIT3, r);
	DDV_MinMaxInt(pDX, r, 0, 35);
	DDV_MinMaxInt(pDX, x, 0, 150);
	DDV_MinMaxInt(pDX, y, 0, 75);
}


BEGIN_MESSAGE_MAP(CDlg_Eclipse, CDialogEx)
END_MESSAGE_MAP()

// CDlg_Eclipse 消息处理程序

