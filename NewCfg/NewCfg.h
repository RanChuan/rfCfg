
// NewCfg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNewCfgApp: 
// �йش����ʵ�֣������ NewCfg.cpp
//

class CNewCfgApp : public CWinApp
{
public:
	CNewCfgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNewCfgApp theApp;