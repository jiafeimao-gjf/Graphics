#include "stdafx.h"
#include "Point_2D.h"


CPoint_2D::CPoint_2D()
	: x(0)
	, y(0)
	, w(1)
{
}


CPoint_2D::~CPoint_2D()
{
}

CPoint_2D::CPoint_2D(int _x, int _y,int _w)
{
	x = _x;
	y = _y;
	w = _w;
}

CPoint_2D operator +(const CPoint_2D &p1, const CPoint_2D &p2)
{
	CPoint_2D p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

CPoint_2D operator -(const CPoint_2D &p1, const CPoint_2D &p2)
{
	CPoint_2D p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CPoint_2D operator *(const CPoint_2D &p1, double k)//点和常量的积
{
	CPoint_2D p;
	p.x = p1.x*k;
	p.y = p1.y*k;
	return p;
}

CPoint_2D operator *(double k, const CPoint_2D &p1)//点和常量的积
{
	CPoint_2D p;
	p.x = k*p1.x;
	p.y = k*p1.y;
	return p;
}

CPoint_2D operator /(const CPoint_2D &p1, double k)//点和常量的除
{
	if (fabs(k)<1e-6)
		k = 1.0;
	CPoint_2D p;
	p.x = p1.x / k;
	p.y = p1.y / k;
	return p;
}

CPoint_2D operator+=(const CPoint_2D &p1, const CPoint_2D &p2)
{
	CPoint_2D p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

CPoint_2D operator-=(const CPoint_2D &p1, const CPoint_2D &p2)
{
	CPoint_2D p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CPoint_2D operator*=(const CPoint_2D &p1, double k)
{
	CPoint_2D p;
	p.x = p1.x*k;
	p.y = p1.y*k;
	return p;
}

CPoint_2D operator/=(const CPoint_2D &p1, double k)
{
	if (fabs(k)<1e-6)
		k = 1.0;
	CPoint_2D p;
	p.x = p1.x / k;
	p.y = p1.y / k;
	return p;
}