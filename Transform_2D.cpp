#include "stdafx.h"
#include "Transform_2D.h"
#include <cstdlib>
#include <string>
#include "Graphics_SoftwareDoc.h"
#include "Graphics_SoftwareView.h"

CTransform_2D::CTransform_2D()
{
	POld = NULL;
	num = 0;
	Identity();
}


CTransform_2D::~CTransform_2D()
{
}

void CTransform_2D::SetMat(CPoint_2D *p, int n)
{	
	num = n;
	POld = p;
}

//µ•Œªæÿ’Û
void CTransform_2D::Identity()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) T[i][j] = 1.0;
			else T[i][j] = 0.0;
		}
	}
}

//∆Ω“∆±‰ªªæÿ’Û
void CTransform_2D::Translate(double tx, double ty) 
{
	Identity();
	T[2][0] = tx;
	T[2][1] = ty;
	MultiMatrix();
}

//±»¿˝±‰ªªæÿ’Û
void CTransform_2D::Scale(double sx, double sy)
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	MultiMatrix();
}

void CTransform_2D::Scale(double sx, double sy, CPoint_2D p)
{
	Translate(-p.x, -p.y);
	Scale(sx, sy);
	Translate(p.x, p.y);
}

void CTransform_2D::Rotate(double beta)
{ 
	Identity();
	double rad = beta*PI / 180;
	T[0][0] = cos(rad); T[0][1] = sin(rad);
	T[1][0] = -sin(rad); T[1][1] = cos(rad);
	MultiMatrix();
}

void CTransform_2D::Rotate(double beta, CPoint_2D p)
{
	Translate(-p.x, -p.y);
	Rotate(beta);
	Translate(p.x, p.y);
}

void CTransform_2D::ReflectOrg()
{
	Identity();
	T[0][0] = -1;
	T[1][1] = -1;
	MultiMatrix();
}

void CTransform_2D::ReflectX()
{
	Identity();
	T[0][0] = 1;
	T[1][1] = -1;
	MultiMatrix();
}

void CTransform_2D::ReflectY()
{
	Identity();
	T[0][0] = -1;
	T[1][1] = 1;
	MultiMatrix();
}

void CTransform_2D::Shear(double b, double c)
{
	Identity();
	T[0][1] = b;
	T[1][0] = c;
	MultiMatrix();
}

void CTransform_2D::MultiMatrix()
{
		CPoint_2D *PNew = new CPoint_2D[num];
		for (int i = 0; i< num; i++)
		{
			PNew[i] = POld[i];
			PNew;
			POld;
		}
		for (int j = 0; j< num; j++)
		{
			POld[j].x = PNew[j].x*T[0][0] + PNew[j].y*T[1][0] + PNew[j].w*T[2][0];
			POld[j].y = PNew[j].x*T[0][1] + PNew[j].y*T[1][1] + PNew[j].w*T[2][1];
			POld[j].w = PNew[j].x*T[0][2] + PNew[j].y*T[1][2] + PNew[j].w*T[2][2];
		}
		delete[] PNew;
}

