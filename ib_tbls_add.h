
// ib_tbls_add.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cib_tbls_addApp:
// �йش����ʵ�֣������ ib_tbls_add.cpp
//

class Cib_tbls_addApp : public CWinApp
{
public:
	Cib_tbls_addApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cib_tbls_addApp theApp;