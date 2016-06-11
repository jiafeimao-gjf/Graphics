// Transform_3D_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphics_Software.h"
#include "Transform_3D_Dlg.h"

// CTransform_3D_Dlg 对话框

IMPLEMENT_DYNAMIC(CTransform_3D_Dlg, CDialogEx)

CTransform_3D_Dlg::CTransform_3D_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{
}

CTransform_3D_Dlg::~CTransform_3D_Dlg()
{
}

void CTransform_3D_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTransform_3D_Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Left, &CTransform_3D_Dlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_Right, &CTransform_3D_Dlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_Up, &CTransform_3D_Dlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_Down, &CTransform_3D_Dlg::OnBnClickedDown)
	ON_BN_CLICKED(IDC_Front, &CTransform_3D_Dlg::OnBnClickedFront)
	ON_BN_CLICKED(IDC_Back, &CTransform_3D_Dlg::OnBnClickedBack)
	ON_BN_CLICKED(IDC_Bigger, &CTransform_3D_Dlg::OnBnClickedBigger)
	ON_BN_CLICKED(IDC_Small, &CTransform_3D_Dlg::OnBnClickedSmall)
	ON_BN_CLICKED(IDC_YOZ, &CTransform_3D_Dlg::OnBnClickedYoz)
	ON_BN_CLICKED(IDC_XOZ, &CTransform_3D_Dlg::OnBnClickedXoz)
	ON_BN_CLICKED(IDC_XOY, &CTransform_3D_Dlg::OnBnClickedXoy)
	ON_BN_CLICKED(IDC_XAxis, &CTransform_3D_Dlg::OnBnClickedXaxis)
	ON_BN_CLICKED(IDC_YAxis, &CTransform_3D_Dlg::OnBnClickedYaxis)
	ON_BN_CLICKED(IDC_ZAxis, &CTransform_3D_Dlg::OnBnClickedZaxis)
	ON_BN_CLICKED(IDC_XDirectionplus, &CTransform_3D_Dlg::OnBnClickedXdirectionplus)
	ON_BN_CLICKED(IDC_YDirectionplus, &CTransform_3D_Dlg::OnBnClickedYdirectionplus)
	ON_BN_CLICKED(IDC_ZDirectionplus, &CTransform_3D_Dlg::OnBnClickedZdirectionplus)
	ON_BN_CLICKED(IDC_Reset, &CTransform_3D_Dlg::OnBnClickedReset)
END_MESSAGE_MAP()


// CTransform_3D_Dlg 消息处理程序

void CTransform_3D_Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()


	CPen *pen = new CPen(0,10,RGB(0,25,40));
	dc.SelectObject(pen);
	for (int i = 30; i < 660;i+=10) {
		dc.MoveTo(i,30);
		dc.LineTo(i,540);
	}
	delete pen;
	pen = new CPen(0, 1, RGB(0, 255, 0));
	dc.SelectObject(pen);
	dc.MoveTo(DX - 35, DY + 15);
	dc.LineTo(550 - 35, 300 + 15);
	dc.TextOut(550 - 35,310 + 15,_T("Y"));
	delete pen;
	pen = new CPen(0, 1, RGB(255, 0, 0));
	dc.SelectObject(pen);
	dc.MoveTo(DX - 35, DY + 15);
	dc.LineTo(300 -35,30 + 15);
	dc.TextOut(320 - 35, 20 + 15, _T("Z"));
	delete pen;
	pen = new CPen(0, 1, RGB(0, 0, 255));
	dc.SelectObject(pen);
	dc.MoveTo(DX - 35, DY + 15);
	dc.LineTo(520 - 35,520 + 15);
	dc.TextOut(510 -35 , 510 +15, _T("X"));
	delete pen;
	DrawPolygon(&dc);

}


void CTransform_3D_Dlg::ReadPoint()
{
	double a = -50;//立方体边长为a
				   //顶点的三维坐标(x,y,z)
	P[0].x = 0; P[0].y = 0; P[0].z = 0;
	P[1].x = a; P[1].y = 0; P[1].z = 0;
	P[2].x = a; P[2].y = a; P[2].z = 0;
	P[3].x = 0; P[3].y = a; P[3].z = 0;
	P[4].x = 0; P[4].y = 0; P[4].z = a;
	P[5].x = a; P[5].y = 0; P[5].z = a;
	P[6].x = a; P[6].y = a; P[6].z = a;
	P[7].x = 0; P[7].y = a; P[7].z = a;
}

void CTransform_3D_Dlg::ReadFace()
{
	//面的边数、面的顶点编号
	F[0].SetNum(4); F[0].vI[0] = 4; F[0].vI[1] = 5; F[0].vI[2] = 6; F[0].vI[3] = 7;//后面,看不见
	F[1].SetNum(4); F[1].vI[0] = 0; F[1].vI[1] = 3; F[1].vI[2] = 2; F[1].vI[3] = 1;//前面
	F[2].SetNum(4); F[2].vI[0] = 0; F[2].vI[1] = 4; F[2].vI[2] = 7; F[2].vI[3] = 3;//左面
	F[3].SetNum(4); F[3].vI[0] = 1; F[3].vI[1] = 2; F[3].vI[2] = 6; F[3].vI[3] = 5;//右面，看不见
	F[4].SetNum(4); F[4].vI[0] = 2; F[4].vI[1] = 3; F[4].vI[2] = 7; F[4].vI[3] = 6;//底面，看不见
	F[5].SetNum(4); F[5].vI[0] = 0; F[5].vI[1] = 1; F[5].vI[2] = 5; F[5].vI[3] = 4;//顶面
}

void CTransform_3D_Dlg::ObliqueProject(CPoint_3D p)
{
	ScreenP.x = p.x - p.z / sqrt(2.0);
	ScreenP.y = p.y - p.z / sqrt(2.0);
}

void CTransform_3D_Dlg::DrawPolygon(CDC *pDC)
{
	int face[6] = { 0,3,4,1,2,5 };
	CPen *pen = NULL;
	for (int nFace = 0; nFace < 6; nFace++)
	{
		if(face[nFace] == 1 || face[nFace] ==2 || face[nFace] == 5){
			pen = new CPen(0, 1, COLOR_POLYGON_FRONT);
		}
		else {
			pen = new CPen(2, 1, COLOR_POLYGON_BACK);
		}
		CPoint_2D t;
		for (int nVertex = 0; nVertex<F[face[nFace]].vN; nVertex++)//顶点循环，vN=4
		{
			pDC->SelectObject(pen);
			ObliqueProject(P[F[face[nFace]].vI[nVertex]]);//斜等测投影
			if (0 == nVertex)
			{
				pDC->MoveTo(ScreenP.x + DX, ScreenP.y + DY);
				t = ScreenP;
			}
			else {
				pDC->LineTo(ScreenP.x + DX, ScreenP.y + DY);
			}
		}
		pDC->LineTo(t.x + DX, t.y + DY);//闭合多边形
		//if (nFace == 5) nFace = 0;
	}
	delete pen;
}




BOOL CTransform_3D_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ReadPoint();
	ReadFace();
	trans.SetMat(P, 8);
	SetBackgroundColor(RGB(107,106,71));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTransform_3D_Dlg::OnBnClickedLeft()
{
	trans.Translate(-10, 0, 0);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedRight()
{
	trans.Translate(10, 0, 0);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedUp()
{
	trans.Translate(0, 10, 0);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedDown()
{
	trans.Translate(0, -10, 0);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedFront()
{
	trans.Translate(0, 0, 10);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedBack()
{
	trans.Translate(0, 0, -10);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedBigger()
{
	trans.Scale(2, 2, 2);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedSmall()
{
	trans.Scale(0.5, 0.5, 0.5);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedYoz()
{
	trans.ReflectYOZ();
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedXoz()
{
	trans.ReflectZOX();
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedXoy()
{
	trans.ReflectXOY();
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedXaxis()
{
	trans.RotateX(30, P[0]);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedYaxis()
{
	trans.RotateY(30, P[0]);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedZaxis()
{
	trans.RotateZ(30,P[0]);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedXdirectionplus()
{
	trans.ShearX(1,1);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedYdirectionplus()
{
	trans.ShearY(-1,-1);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedZdirectionplus()
{
	trans.ShearZ(-1,-1);
	OnPaint();
	Invalidate(FALSE);
}


void CTransform_3D_Dlg::OnBnClickedReset()
{
	ReadPoint();
	OnPaint();
	Invalidate(FALSE);
	UpdateWindow();
}
