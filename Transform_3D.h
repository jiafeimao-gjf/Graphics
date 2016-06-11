#pragma once
#include "Point_3D.h"
class CTransform_3D
{
public:
	CTransform_3D();
	~CTransform_3D();
	void SetMat(CPoint_3D *, int);
	void Identity();
	void Translate(double, double, double);//ƽ�Ʊ任����
	void Scale(double, double, double);//�����任����
	void Scale(double, double, double, CPoint_3D);//����������ı����任����
	void RotateX(double);//��ת�任����
	void RotateX(double, CPoint_3D);//�����������X��ת�任����
	void RotateY(double);//��ת�任����
	void RotateY(double, CPoint_3D);//�����������Y��ת�任����
	void RotateZ(double);//��ת�任����
	void RotateZ(double, CPoint_3D);//�����������Z��ת�任����
	void ReflectX();//X�ᷴ��任����
	void ReflectY();//Y�ᷴ��任����
	void ReflectZ();//Z�ᷴ��任����
	void ReflectXOY();//XOY�淴��任����
	void ReflectYOZ();//YOZ�淴��任����
	void ReflectZOX();//XOZ�淴��任����
	void ShearX(double, double);//X������б任����
	void ShearY(double, double);//Y������б任����
	void ShearZ(double, double);//Z������б任����
	void MultiMatrix();//�������
public:
	double T[4][4];
	CPoint_3D *POld;
	int num;
};

