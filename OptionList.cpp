// OptionList.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphics_Software.h"
#include "OptionList.h"
#include "afxdialogex.h"


// COptionList 对话框

IMPLEMENT_DYNAMIC(COptionList, CDialogEx)

COptionList::COptionList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Control_BALL, pParent)
	, m_rPattern(0)
	, m_rLighting(-1)
	, m_Display(false)
{

}

COptionList::~COptionList()
{
}

void COptionList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_RADIUS, m_cRadius);
	DDX_Control(pDX, IDC_SLIDER_FACE_COUNT, m_cFaceCount);
	DDX_Control(pDX, IDC_SLIDER_TRANSLATE_AXIS_X, m_cTranslateX);
	DDX_Control(pDX, IDC_SLIDER_TRANSLATE_AXIS_Y, m_cTranslateY);
	DDX_Control(pDX, IDC_SLIDER_TRANSLATE_AXIS_Z, m_cTranslateZ);
	DDX_Control(pDX, IDC_SLIDER_ROTATE_AXIS_X, m_cRotateX);
	DDX_Control(pDX, IDC_SLIDER_ROTATE_AXIS_Y, m_cRotateY);
	DDX_Control(pDX, IDC_SLIDER_ROTATE_AXIS_Z, m_cRotateZ);
}


BEGIN_MESSAGE_MAP(COptionList, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_PATTERN, &COptionList::OnBnClickedRadioPattern)
	ON_BN_CLICKED(IDC_RADIO_PATTERN2, &COptionList::OnBnClickedRadioPattern2)
	ON_BN_CLICKED(IDC_RADIO_LIGHTING, &COptionList::OnBnClickedRadioLighting)
	ON_BN_CLICKED(IDC_RADIO_LIGHTING2, &COptionList::OnBnClickedRadioLighting2)
	ON_BN_CLICKED(IDC_DISPLAY, &COptionList::OnBnClickedDisplay)
	ON_BN_CLICKED(IDC_HIDE, &COptionList::OnBnClickedHide)
END_MESSAGE_MAP()


// COptionList 消息处理程序


void COptionList::OnBnClickedRadioPattern()
{
	m_rPattern = 0;
}


void COptionList::OnBnClickedRadioPattern2()
{
	m_rPattern = 1;
}

void COptionList::OnBnClickedRadioLighting()
{
	m_rLighting = 0;
}


void COptionList::OnBnClickedRadioLighting2()
{
	m_rLighting = 1;
}


BOOL COptionList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_cRadius.SetRange(1, 20);
	m_cRadius.SetPos(6);
	m_cFaceCount.SetRange(0, 7);
	m_cFaceCount.SetPos(3);

	m_cTranslateX.SetRange(0, 10);
	m_cTranslateY.SetRange(0, 10);
	m_cTranslateZ.SetRange(0, 10);
	m_cTranslateX.SetPos(2);
	m_cTranslateY.SetPos(2);
	m_cTranslateZ.SetPos(2);
	m_cRotateX.SetRange(0, 10);
	m_cRotateY.SetRange(0, 10);
	m_cRotateZ.SetRange(0, 10);
	m_cRotateX.SetPos(1);
	m_cRotateY.SetPos(1);
	m_cRotateZ.SetPos(1);

	//CString str("");
	//str.Format("当前球体面数为：%d", (INT(8 * pow(4, m_cFaceCount.GetPos()))));
	//m_cCurFace.SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void COptionList::OnBnClickedDisplay()
{
	m_Display = true;
}


void COptionList::OnBnClickedHide()
{
	m_Display = false;
}
