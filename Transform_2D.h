#pragma once
#include "Point_2D.h"
#include <cstdlib>

class CTransform_2D
{
public:
	CTransform_2D();
	~CTransform_2D();
	void SetMat(CPoint_2D *, int);
	void Identity();
	void Translate(double, double);//平移变换矩阵
	void Scale(double, double);//比例变换矩阵
	void Scale(double, double, CPoint_2D);//相对于任意点的比例变换矩阵
	void Rotate(double);//旋转变换矩阵
	void Rotate(double, CPoint_2D);//相对于任意点的旋转变换矩阵
	void ReflectOrg();//原点反射变换矩阵
	void ReflectX();//X轴反射变换矩阵
	void ReflectY();//Y轴反射变换矩阵
	void Shear(double, double);//错切变换矩阵
	void MultiMatrix();//矩阵相乘
public:
	double T[3][3];//变换矩阵
	CPoint_2D *POld;//指针用于修改坐标，达到图形变换
	int num;//图形定点的个数
};

