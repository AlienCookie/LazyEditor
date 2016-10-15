
// Lab_01_3DEditor.h : main header file for the Lab_01_3DEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLab_01_3DEditorApp:
// See Lab_01_3DEditor.cpp for the implementation of this class
//

class CLab_01_3DEditorApp : public CWinApp
{
public:
	CLab_01_3DEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab_01_3DEditorApp theApp;
