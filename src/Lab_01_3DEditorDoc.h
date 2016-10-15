
// Lab_01_3DEditorDoc.h : interface of the CLab_01_3DEditorDoc class
//


#pragma once



class CLab_01_3DEditorDoc : public CDocument
{
protected: // create from serialization only
	CLab_01_3DEditorDoc();
	DECLARE_DYNCREATE(CLab_01_3DEditorDoc)

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLab_01_3DEditorDoc)
public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CLab_01_3DEditorDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CLab_01_3DEditorDoc)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
