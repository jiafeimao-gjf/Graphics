// Ball_Display_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphics_Software.h"
#include "Ball_Display_Dlg.h"
#include "afxdialogex.h"
#include "OpenGlInit.h"
#include "OptionList.h"


// CBall_Display_Dlg 对话框

IMPLEMENT_DYNAMIC(CBall_Display_Dlg, CDialogEx)

CBall_Display_Dlg::CBall_Display_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, m_nPattern(1)
	, m_nLighting(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_xTranBool = TRUE;
	m_yTranBool = TRUE;
	m_zTranBool = TRUE;

	m_fTranslateX = 0.0f;	//初始位置
	m_fTranslateY = 0.0f;
	m_fTranslateZ = 0.0f;
	m_fRotateX = 0.0f;
	m_fRotateY = 0.0f;
	m_fRotateZ = 0.0f;
}

CBall_Display_Dlg::~CBall_Display_Dlg()
{

}


void CBall_Display_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBall_Display_Dlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBall_Display_Dlg 消息处理程序


void CBall_Display_Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (Optiondlg.m_Display) {
		m_nRadius = Optiondlg.m_cRadius.GetPos();
		m_nCount = Optiondlg.m_cFaceCount.GetPos();
		m_nLighting = Optiondlg.m_rLighting;
		m_fRotateX += (FLOAT)Optiondlg.m_cRotateX.GetPos();
		m_fRotateY += (FLOAT)Optiondlg.m_cRotateY.GetPos();
		m_fRotateZ += (FLOAT)Optiondlg.m_cRotateZ.GetPos();

		//	CString str;
		//	str.Format("当前球体面数为：%d", ((int)(8 * pow(4, m_cFaceCount.GetPos()))));
		//	m_cCurFace.SetWindowText(_T((int)(8 * pow(4, m_cFaceCount.GetPos()))));
		//	m_cCurFace.SetWindowText(str);

		if (m_fTranslateX > 30)
			m_xTranBool = false;
		else if (m_fTranslateX < -30)
			m_xTranBool = true;
		if (m_xTranBool)
			m_fTranslateX += (FLOAT)(Optiondlg.m_cTranslateX.GetPos()*0.1);
		else
			m_fTranslateX -= (FLOAT)(Optiondlg.m_cTranslateX.GetPos()*0.1);

		if (m_fTranslateY > 15)
			m_yTranBool = false;
		else if (m_fTranslateY < -15)
			m_yTranBool = true;
		if (m_yTranBool)
			m_fTranslateY += (FLOAT)(Optiondlg.m_cTranslateY.GetPos()*0.1);
		else
			m_fTranslateY -= (FLOAT)(Optiondlg.m_cTranslateY.GetPos()*0.1);

		if (m_fTranslateZ > 20)
			m_zTranBool = false;
		else if (m_fTranslateZ < -20)
			m_zTranBool = true;
		if (m_zTranBool)
			m_fTranslateZ += (FLOAT)(Optiondlg.m_cTranslateZ.GetPos()*0.1);
		else
			m_fTranslateZ -= (FLOAT)(Optiondlg.m_cTranslateZ.GetPos()*0.1);


		if (0 == Optiondlg.m_rPattern)
			m_nPattern = GL_LINE_LOOP;
		else
			m_nPattern = GL_TRIANGLES;
	}

	InvalidateRect(NULL, FALSE);	//视图重绘，调用了OnDraw()
	CDialogEx::OnTimer(nIDEvent);
}


void CBall_Display_Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	if (Optiondlg.m_Display) {
		DrawScene();
	}
	else {
		UpdateWindow();
	}
}


int CBall_Display_Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pDC = new CClientDC(this);		//Windows当前的绘图设备上下文对象指针
	ASSERT(m_pDC != NULL);

	if (!OpenGLInit(m_pDC, m_hglrc))	//初始化OpenGL的显示情况
		return -1;

	SetTimer(0, 10, NULL);				//放置定时器	
	return 0;
}


void CBall_Display_Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	OpenGLExit(m_pDC, m_hglrc);
}


void CBall_Display_Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION);	//投影变换
	glLoadIdentity();

	if (cx <= cy)	//根据窗口大小调整正射投影矩阵
		glOrtho(-20.0, 20.0, -20.0*(GLfloat)cy / (GLfloat)cx,
			20.0*(GLfloat)cy / (GLfloat)cx, -50.0, 50.0);
	else
		glOrtho(-20.0*(GLfloat)cx / (GLfloat)cy,
			20.0*(GLfloat)cx / (GLfloat)cy, -20.0, 20.0, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);		//这二句不能少，否则图形看不出效果
	glLoadIdentity();				//设置变换模式为模型变换
}

void CBall_Display_Dlg::DrawScene()
{
	//在屏幕上显出图形
	if (m_hglrc)					//设置当前绘图设备为OpenGL的设备情景对象
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	else
		return;

	glDrawBuffer(GL_BACK);		//指定在后台缓存中绘制图形
	glLoadIdentity();			//初始化变换矩阵

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glShadeModel(GL_SMOOTH);

	//光照
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };

	GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	if (1 == m_nLighting)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	//变换
	glTranslated(m_fTranslateX, 0.0, 0.0);
	glTranslated(0.0, m_fTranslateY, 0.0);
	glTranslated(0.0, 0.0, m_fTranslateZ);

	//旋转
	glRotated(m_fRotateX, 1.0, 0.0, 0.0);
	glRotated(m_fRotateY, 0.0, 1.0, 0.0);
	glRotated(m_fRotateZ, 0.0, 0.0, 1.0);

	//画图
	DrawGeometry();
	//画图结束
	glPopMatrix();
	glFinish();					//结束整个绘制

	SwapBuffers(wglGetCurrentDC());	//交换前后缓存
	glDrawBuffer(GL_FRONT);			//绘制前景
}

void CBall_Display_Dlg::NormalTriangle(float * v1, float * v2, float * v3, float * vout)
{
	//求三点构成的三角形面的法向量
	GLfloat v12[3], v23[3];
	for (int i = 0; i < 3; i++) {
		v12[i] = v2[i] - v1[i];
		v23[i] = v3[i] - v2[i];
	}

	vout[0] = v12[1] * v23[2] - v12[2] * v23[1];
	vout[1] = -(v12[0] * v23[2] - v12[2] * v23[0]);
	vout[2] = v12[0] * v23[1] - v12[1] * v23[0];
	Normalize(vout, 1);
}

void CBall_Display_Dlg::Normalize(float * v, float radius)
{
	//向量的标准化,以模长为radius进行标准化
	GLfloat d = (GLfloat)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		return;
	}
	v[0] /= d; v[1] /= d; v[2] /= d;
	v[0] *= radius; v[1] *= radius; v[2] *= radius;
}

void CBall_Display_Dlg::DrawTriangle(float * v1, float * v2, float * v3)
{
	//以三点为顶点画三角形
	GLfloat normal[3] = { 0,0,0 };
	NormalTriangle(v1, v2, v3, normal);//求取面法向量
	glBegin(m_nPattern);
		glNormal3fv(normal);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
	glEnd();
}

void CBall_Display_Dlg::SubDivide(float * v1, float * v2, float * v3, int count)
{
	//把count为级数，对一个三角形面的子划分
	if (0 >= count)	//count=0,则画由三点构成的三角形
	{
		DrawTriangle(v1, v2, v3);
	}
	else
	{
		GLfloat v12[3], v23[3], v31[3];
		GLint i;
		for (i = 0; i < 3; i++) {
			v12[i] = (v1[i] + v2[i]) / 2;
			v23[i] = (v2[i] + v3[i]) / 2;
			v31[i] = (v3[i] + v1[i]) / 2;
		}
		Normalize(v12, (float)m_nRadius);	//扩展模长
		Normalize(v23, (float)m_nRadius);
		Normalize(v31, (float)m_nRadius);

		SubDivide(v1, v12, v31, count - 1);
		SubDivide(v2, v23, v12, count - 1);
		SubDivide(v3, v31, v23, count - 1);
		SubDivide(v12, v23, v31, count - 1);
	}
}

void CBall_Display_Dlg::DrawGeometry()
{
	//在此处画球体
	GLfloat r = (GLfloat)m_nRadius;
	GLfloat vdata[6][3] = {	//初始点坐标
		{ r,0.0,0.0 },{ -r,0.0,0.0 },
		{ 0.0,r,0.0 },{ 0.0,-r,0.0 },
		{ 0.0,0.0,r },{ 0.0,0.0,-r }
	};
	GLuint tindices[8][3] = {//初始面的构造
		{ 2,4,0 },{ 2,0,5 },{ 2,5,1 },{ 2,1,4 },
		{ 3,0,4 },{ 3,5,0 },{ 3,1,5 },{ 3,4,1 }
	};

	/*以下坐标是参考书上的初值,为正20面体,效果会比自定义的要好些
	const float X = (float)0.525731112119133606*m_nRadius;
	const float Z = (float)0.850650808352039932*m_nRadius;
	static GLfloat vdata[12][3] = {
	{-X,0.0,Z},{X,0.0,Z},{-X,0.0,-Z},{X,0.0,-Z},
	{0.0,Z,X},{0.0,Z,-X},{0.0,-Z,X},{0.0,-Z,-X},
	{Z,X,0.0},{-Z,X,0.0},{Z,-X,0.0},{-Z,-X,0.0}
	};
	static GLuint tindices[20][3] = {
	{0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
	{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
	{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
	{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};*/

	for (int i = 0; i < 8; i++) {
		SubDivide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0], m_nCount);
	}
}


BOOL CBall_Display_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Optiondlg.Create(IDD_Control_BALL,this);
	Optiondlg.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
