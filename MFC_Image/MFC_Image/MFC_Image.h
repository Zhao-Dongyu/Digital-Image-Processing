
// MFC_Image.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_ImageApp: 
// �йش����ʵ�֣������ MFC_Image.cpp
//

class CMFC_ImageApp : public CWinApp
{
public:
	CMFC_ImageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_ImageApp theApp;