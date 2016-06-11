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
	void Translate(double, double);//ƽ�Ʊ任����
	void Scale(double, double);//�����任����
	void Scale(double, double, CPoint_2D);//����������ı����任����
	void Rotate(double);//��ת�任����
	void Rotate(double, CPoint_2D);//�������������ת�任����
	void ReflectOrg();//ԭ�㷴��任����
	void ReflectX();//X�ᷴ��任����
	void ReflectY();//Y�ᷴ��任����
	void Shear(double, double);//���б任����
	void MultiMatrix();//�������
public:
	double T[3][3];//�任����
	CPoint_2D *POld;//ָ�������޸����꣬�ﵽͼ�α任
	int num;//ͼ�ζ���ĸ���
};

