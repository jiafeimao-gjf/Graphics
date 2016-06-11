// Number_of_Point.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphics_Software.h"
#include "Number_of_Point.h"
#include "afxdialogex.h"


// CNumber_of_Point 对话框

IMPLEMENT_DYNAMIC(CNumber_of_Point, CDialogEx)

CNumber_of_Point::CNumber_of_Point(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_Num_point(0)
{

}

CNumber_of_Point::~CNumber_of_Point()
{
}

void CNumber_of_Point::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Num_point);
	DDV_MinMaxInt(pDX, m_Num_point, 3, 100);
}


BEGIN_MESSAGE_MAP(CNumber_of_Point, CDialogEx)
END_MESSAGE_MAP()


// CNumber_of_Point 消息处理程序
