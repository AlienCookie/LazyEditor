
// Lab_01_3DEditorView.h : interface of the CLab_01_3DEditorView class
//

#pragma once
#include "openGL.h"

class CLab_01_3DEditorView : public CView
{
protected: // create from serialization only
	CLab_01_3DEditorView();
	DECLARE_DYNCREATE(CLab_01_3DEditorView)

	// Attributes
public:
//	CLab_01_3DEditorDoc* GetDocument() const;

	CPalette    m_cPalette;
	CPalette    *m_pOldPalette;
	CRect       m_oldRect;
	float       m_fRadius;
	CClientDC   *m_pDC;

	// Operations
public:
	void Init();
	void CreateRGBPalette(void);
	BOOL bSetupPixelFormat(void);
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void DrawScene(void);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLab_01_3DEditorView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
									//}}AFX_VIRTUAL

									// Implementation
public:
	virtual ~CLab_01_3DEditorView();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//BOOL    m_play;
	CString Title;
	int Width, Height;
	COpenGLRender OpenGLRender;
	// Generated message map functions
protected:
	//{{AFX_MSG(CLab_01_3DEditorView)

	afx_msg void OnCubeCreate();
	afx_msg void OnPiramideCreate();
	afx_msg void OnRotateMode();
	afx_msg void OnScaleMode();
	afx_msg void OnMoveMode();

	//afx_msg void OnUpdateFilePlay(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT, short, CPoint);
	afx_msg void OnMButtonDown(UINT, CPoint);
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg void OnLButtonDown(UINT, CPoint);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void OnColor();
	void OnSave();
	void OnLoad();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in cubeview.cpp
inline CCubeDoc* CLab_01_3DEditorView::GetDocument()
{
	return (CCubeDoc*)m_pDocument;
}
#endif

/*class CLab_01_3DEditorView : public CView
{
protected: // create from serialization only
	CLab_01_3DEditorView();
	DECLARE_DYNCREATE(CLab_01_3DEditorView)

// Attributes
public:
	CLab_01_3DEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
// Implementation
public:
	virtual ~CLab_01_3DEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Lab_01_3DEditorView.cpp
inline CLab_01_3DEditorDoc* CLab_01_3DEditorView::GetDocument() const
   { return reinterpret_cast<CLab_01_3DEditorDoc*>(m_pDocument); }
#endif
*/
