
// Lab_01_3DEditorDoc.cpp : implementation of the CLab_01_3DEditorDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab_01_3DEditor.h"
#endif

#include "Lab_01_3DEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorDoc

IMPLEMENT_DYNCREATE(CLab_01_3DEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CLab_01_3DEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CLab_01_3DEditorDoc)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorDoc construction/destruction

CLab_01_3DEditorDoc::CLab_01_3DEditorDoc()
{
	// TODO: add one-time construction code here

}

CLab_01_3DEditorDoc::~CLab_01_3DEditorDoc()
{
}

BOOL CLab_01_3DEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorDoc serialization

void CLab_01_3DEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorDoc diagnostics

#ifdef _DEBUG
void CLab_01_3DEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLab_01_3DEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG