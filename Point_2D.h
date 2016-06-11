#pragma once
class CPoint_2D
{
public:
	CPoint_2D();
	~CPoint_2D();
	CPoint_2D(int,int,int);
	friend CPoint_2D operator +(const CPoint_2D &, const CPoint_2D &);
	friend CPoint_2D operator -(const CPoint_2D &, const CPoint_2D &);
	friend CPoint_2D operator *(const CPoint_2D &, double);
	friend CPoint_2D operator *(double, const CPoint_2D &);
	friend CPoint_2D operator /(const CPoint_2D &, double);
	friend CPoint_2D operator+=(const CPoint_2D &, const CPoint_2D &);
	friend CPoint_2D operator-=(const CPoint_2D &, const CPoint_2D &);
	friend CPoint_2D operator*=(const CPoint_2D &, double);
	friend CPoint_2D operator/=(const CPoint_2D &, double);
public:
	double x;
	double y;
	double w;
};

