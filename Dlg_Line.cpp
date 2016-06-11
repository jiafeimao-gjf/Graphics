// Dlg_Line.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphics_Software.h"
#include "Graphics_SoftwareView.h"
#include "Dlg_Line.h"
#include "afxdialogex.h"


// CDlg_Line 对话框

IMPLEMENT_DYNAMIC(CDlg_Line, CDialogEx)

CDlg_Line::CDlg_Line(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, a(0)
	, b(0)
	, c(0)
	, d(0)
{
}

CDlg_Line::~CDlg_Line()
{
}

void CDlg_Line::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, a);
	DDX_Text(pDX, IDC_EDIT2, b);
	DDX_Text(pDX, IDC_EDIT3, c);
	DDX_Text(pDX, IDC_EDIT4, d);
	DDV_MinMaxInt(pDX, a, 0, 150);
	DDV_MinMaxInt(pDX, c, 0, 150);
	DDV_MinMaxInt(pDX, b, 0, 70);
	DDV_MinMaxInt(pDX, d, 0, 70);
}


BEGIN_MESSAGE_MAP(CDlg_Line, CDialogEx)
END_MESSAGE_MAP()


// CDlg_Line 消息处理程序