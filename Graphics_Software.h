
// Graphics_Software.h : Graphics_Software Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGraphics_SoftwareApp:
// �йش����ʵ�֣������ Graphics_Software.cpp
//

class CGraphics_SoftwareApp : public CWinApp
{
public:
	CGraphics_SoftwareApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphics_SoftwareApp theApp;
