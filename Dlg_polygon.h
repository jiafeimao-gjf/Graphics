#pragma once


// Dlg_polygon �Ի���

class Dlg_polygon : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_polygon)

public:
	Dlg_polygon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_polygon();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int ax;
	int ay;
	int bx;
	int by;
	int cx;
	int cy;
	int dx;
	int dy;
	int ex;
	int ey;
	int fx;
	int fy;
	int gx;
	int gy;
	int hx;
	int hy;
	int ix;
	int iy;
	int jx;
	int jy;
};
