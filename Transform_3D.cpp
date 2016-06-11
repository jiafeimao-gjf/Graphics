#include "stdafx.h"
#include "Transform_3D.h"


CTransform_3D::CTransform_3D()
	:POld(NULL)
	,num(0)
{
}


CTransform_3D::~CTransform_3D()
{
}

void CTransform_3D::SetMat(CPoint_3D *p, int _num)
{
	POld = p;
	num = _num;
}

void CTransform_3D::Identity()
{
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0; T[0][3] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0; T[1][3] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0; T[2][3] = 0.0;
	T[3][0] = 0.0; T[3][1] = 0.0; T[3][2] = 0.0; T[3][3] = 1.0;
}

void CTransform_3D::Translate(double tx, double ty, double tz)
{
	Identity();
	T[3][0] = tx;
	T[3][1] = ty;
	T[3][2] = tz;
	MultiMatrix();
}

void CTransform_3D::Scale(double sx, double sy, double sz)
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	T[2][2] = sz;
	MultiMatrix();
}

void CTransform_3D::Scale(double sx, double sy, double sz, CPoint_3D p)
{
	Translate(-p.x, -p.y, -p.z);
	Scale(sx, sy, sz);
	Translate(p.x, p.y, p.z);
}

void CTransform_3D::RotateX(double beta)
{
	Identity();
	double rad = beta*PI / 180;
	T[1][1] = cos(rad); T[1][2] = sin(rad);
	T[2][1] = -sin(rad); T[2][2] = cos(rad);
	MultiMatrix();
}

void CTransform_3D::RotateX(double beta, CPoint_3D p)
{
	Translate(-p.x, -p.y, -p.z);
	RotateX(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform_3D::RotateY(double beta)
{
	Identity();
	double rad = beta*PI / 180;
	T[0][0] = cos(rad); T[0][2] = -sin(rad);
	T[2][0] = sin(rad); T[2][2] = cos(rad);
	MultiMatrix();
}

void CTransform_3D::RotateY(double beta, CPoint_3D p)
{
	Translate(-p.x, -p.y, -p.z);
	RotateY(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform_3D::RotateZ(double beta)
{
	Identity();
	double rad = beta*PI / 180;
	T[0][0] = cos(rad); T[0][1] = sin(rad);
	T[1][0] = -sin(rad); T[1][1] = cos(rad);
	MultiMatrix();
}

void CTransform_3D::RotateZ(double beta, CPoint_3D p)
{
	Translate(-p.x, -p.y, -p.z);
	RotateZ(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform_3D::ReflectX()
{
	Identity();
	T[1][1] = -1;
	T[2][2] = -1;
	MultiMatrix();
}

void CTransform_3D::ReflectY()
{
	Identity();
	T[0][0] = -1;
	T[2][2] = -1;
	MultiMatrix();
}

void CTransform_3D::ReflectZ()
{
	Identity();
	T[0][0] = -1;
	T[1][1] = -1;
	MultiMatrix();
}

void CTransform_3D::ReflectXOY()
{
	Identity();
	T[2][2] = -1;
	MultiMatrix();
}

void CTransform_3D::ReflectYOZ()
{
	Identity();
	T[0][0] = -1;
	MultiMatrix();
}

void CTransform_3D::ReflectZOX()
{
	Identity();
	T[1][1] = -1;
	MultiMatrix();
}

void CTransform_3D::ShearX(double d, double g)
{
	Identity();
	T[1][0] = d;
	T[2][0] = g;
	MultiMatrix();
}

void CTransform_3D::ShearY(double b, double h)
{
	Identity();
	T[0][1] = b;
	T[2][1] = h;
	MultiMatrix();
}

void CTransform_3D::ShearZ(double c, double f)
{
	Identity();
	T[0][2] = c;
	T[1][2] = f;
	MultiMatrix();
}

void CTransform_3D::MultiMatrix()
{
	CPoint_3D *PNew = new CPoint_3D[num];
	for (int i = 0; i<num; i++)
	{
		PNew[i] = POld[i];
	}
	for (int j = 0; j<num; j++)
	{
		POld[j].x = PNew[j].x*T[0][0] + PNew[j].y*T[1][0] + PNew[j].z*T[2][0] + PNew[j].w*T[3][0];
		POld[j].y = PNew[j].x*T[0][1] + PNew[j].y*T[1][1] + PNew[j].z*T[2][1] + PNew[j].w*T[3][1];
		POld[j].z = PNew[j].x*T[0][2] + PNew[j].y*T[1][2] + PNew[j].z*T[2][2] + PNew[j].w*T[3][2];
		POld[j].w = PNew[j].x*T[0][3] + PNew[j].y*T[1][3] + PNew[j].z*T[2][3] + PNew[j].w*T[3][3];
	}
	delete[]PNew;
}
