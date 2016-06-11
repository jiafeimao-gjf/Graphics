#pragma once
#include "Point_3D.h"
class CTransform_3D
{
public:
	CTransform_3D();
	~CTransform_3D();
	void SetMat(CPoint_3D *, int);
	void Identity();
	void Translate(double, double, double);//平移变换矩阵
	void Scale(double, double, double);//比例变换矩阵
	void Scale(double, double, double, CPoint_3D);//相对于任意点的比例变换矩阵
	void RotateX(double);//旋转变换矩阵
	void RotateX(double, CPoint_3D);//相对于任意点的X旋转变换矩阵
	void RotateY(double);//旋转变换矩阵
	void RotateY(double, CPoint_3D);//相对于任意点的Y旋转变换矩阵
	void RotateZ(double);//旋转变换矩阵
	void RotateZ(double, CPoint_3D);//相对于任意点的Z旋转变换矩阵
	void ReflectX();//X轴反射变换矩阵
	void ReflectY();//Y轴反射变换矩阵
	void ReflectZ();//Z轴反射变换矩阵
	void ReflectXOY();//XOY面反射变换矩阵
	void ReflectYOZ();//YOZ面反射变换矩阵
	void ReflectZOX();//XOZ面反射变换矩阵
	void ShearX(double, double);//X方向错切变换矩阵
	void ShearY(double, double);//Y方向错切变换矩阵
	void ShearZ(double, double);//Z方向错切变换矩阵
	void MultiMatrix();//矩阵相乘
public:
	double T[4][4];
	CPoint_3D *POld;
	int num;
};

