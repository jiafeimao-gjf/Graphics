#pragma once
#include "Point_2D.h"
class CPoint_3D :
	public CPoint_2D
{
public:
	CPoint_3D();
	CPoint_3D(double,double,double);
	~CPoint_3D();
public:
	double z;
};

