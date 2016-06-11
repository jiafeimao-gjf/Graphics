
#include "stdafx.h"
#include "Point_3D.h"


CPoint_3D::CPoint_3D()
	:z(0)
{

}

CPoint_3D::CPoint_3D(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}


CPoint_3D::~CPoint_3D()
{
}
