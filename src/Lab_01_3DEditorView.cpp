
// Lab_01_3DEditorView.cpp : implementation of the CLab_01_3DEditorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab_01_3DEditor.h"
#endif

#include "Lab_01_3DEditorDoc.h"
#include "Lab_01_3DEditorView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorView

IMPLEMENT_DYNCREATE(CLab_01_3DEditorView, CView)

BEGIN_MESSAGE_MAP(CLab_01_3DEditorView, CView)
	//{{AFX_MSG_MAP(CLab_01_3DEditorView)
	ON_COMMAND(ID_CUBEBUTTON, OnCubeCreate)
	ON_COMMAND(ID_PIRAMIDE_BUTTON, OnPiramideCreate)
	ON_COMMAND(ID_MOVE_BUTTON, OnMoveMode)
	ON_COMMAND(ID_SCALE_BUTTON, OnScaleMode)
	ON_COMMAND(ID_ROTATE_BUTTON, OnRotateMode)
	ON_COMMAND(ID_COLORBUTTON, OnColor)
	ON_COMMAND(ID_SAVE_BUTTON, OnSave)
	ON_COMMAND(ID_LOAD_BUTTON, OnLoad)
	//ON_COMMAND(ID_CUBE_BUTTON, OnColor)

	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
//	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorView construction/destruction

CLab_01_3DEditorView::CLab_01_3DEditorView()
{
	m_pDC = NULL;
	m_pOldPalette = NULL;
}

CLab_01_3DEditorView::~CLab_01_3DEditorView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorView drawing

void CLab_01_3DEditorView::OnDraw(CDC* /*pDC*/)
{
//	CLab_01_3DEditorDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);


}

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorView diagnostics

#ifdef _DEBUG
void CLab_01_3DEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CLab_01_3DEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/*CLab_01_3DEditorDoc* CLab_01_3DEditorView::GetDocument() const // non-debug version 
{
	//SSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab_01_3DEditorDoc)));
	//return (CLab_01_3DEditorDoc*)m_pDocument;
	return STATIC_DOWNCAST(CLab_01_3DEditorDoc, m_pDocument);
}*/
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLab_01_3DEditorView message handlers

void CLab_01_3DEditorView::OnCubeCreate()
{
	OpenGLRender.addObject(CubeType);

}

void CLab_01_3DEditorView::OnPiramideCreate()
{
	OpenGLRender.addObject(PiramidType);
}

void CLab_01_3DEditorView::OnRotateMode()
{
	OpenGLRender.setMode(Rotate);
}

void CLab_01_3DEditorView::OnScaleMode()
{
	OpenGLRender.setMode(Scale);
}

void CLab_01_3DEditorView::OnMoveMode()
{
	OpenGLRender.setMode(Move);
}


BOOL CLab_01_3DEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// An OpenGL window must be created with the following flags and must not
	// include CS_PARENTDC for the class style. Refer to SetPixelFormat
	// documentation in the "Comments" section for further information.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

int CLab_01_3DEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	Init(); // initialize OpenGL

	return 0;
}

void CLab_01_3DEditorView::OnDestroy()
{
	HGLRC   hrc;

	KillTimer(1);

	hrc = ::wglGetCurrentContext();

	::wglMakeCurrent(NULL, NULL);

	if (hrc)
		::wglDeleteContext(hrc);

	if (m_pOldPalette)
		m_pDC->SelectPalette(m_pOldPalette, FALSE);

	if (m_pDC)
		delete m_pDC;

	CView::OnDestroy();
}

void CLab_01_3DEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	Width = cx;
	Height = cy;

	OpenGLRender.Resize(Width, Height);
}

void CLab_01_3DEditorView::OnTimer(UINT_PTR nIDEvent)
{
	DrawScene();

	CView::OnTimer(nIDEvent);

	// Eat spurious WM_TIMER messages
	MSG msg;
	while (::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));
}

BOOL CLab_01_3DEditorView::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CLab_01_3DEditorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
	DrawScene();
	// Do not call CView::OnPaint() for painting messages
}

void CLab_01_3DEditorView::OnColor()
{
	OpenGLRender.onColor();
}

void CLab_01_3DEditorView::OnSave()
{
	OpenGLRender.onSave();
}

void CLab_01_3DEditorView::OnLoad()
{
	OpenGLRender.onLoad();
}

/////////////////////////////////////////////////////////////////////////////
// GL helper functions

void CLab_01_3DEditorView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int         n;
	HGLRC       hrc;
	GLfloat     fMaxObjSize, fAspect;
	GLfloat     fNearPlane, fFarPlane;

	m_pDC = new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if (!bSetupPixelFormat())
		return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	//CreateRGBPalette();

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	OpenGLRender.Init();
}

BOOL CLab_01_3DEditorView::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |          // support OpenGL
		PFD_DOUBLEBUFFER,             // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		//MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}

	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
	//	MessageBox("SetPixelFormat failed");
		return FALSE;
	}

	return TRUE;
}



#pragma warning(disable : 4244)
void CLab_01_3DEditorView::CreateRGBPalette()
{
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE *pPal;
	int n, i;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);


}
#pragma warning(default : 4244)

void CLab_01_3DEditorView::DrawScene(void)
{

	
	OpenGLRender.Render();

	SwapBuffers(wglGetCurrentDC());

	Invalidate(FALSE);


}


BOOL CLab_01_3DEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	OpenGLRender.mouseWheel(zDelta);
	return 0;
}

void CLab_01_3DEditorView::OnMButtonDown(UINT nFlags, CPoint point)
{
//	OpenGLRender.addObject();
}

void CLab_01_3DEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	static CPoint prev = point;
	switch (nFlags)
	{
	case MK_MBUTTON:

		break;
	case MK_LBUTTON:
		OpenGLRender.LButtonMove(point);
		OpenGLRender.cursor = point;
		break;
	case MK_RBUTTON:
		OpenGLRender.RButtonMove(point);
		OpenGLRender.cursor = point;
		break;
	default:
		OpenGLRender.cursor = point;
		break;
	}
}

void CLab_01_3DEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	OpenGLRender.pickObject(point);
}

//void CLab_01_3DEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	UINT leter = nChar;
//	switch (nChar)
//	{
//	case 77:
//		OpenGLRender.setMode(Move);
//		break;
//	case 82:
//		OpenGLRender.setMode(Rotate);
//		break;
//	case 83:
//		OpenGLRender.setMode(Scale);
//		break;
//	}
//	CView::OnKeyDown(nChar, nRepCnt, nFlags);
//}

void CLab_01_3DEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	OpenGLRender.setSelct(false);
	OpenGLRender.setOnObject(false);
	CView::OnLButtonUp(nFlags, point);
}


void CLab_01_3DEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case 88:
		OpenGLRender.onSelected();
		break;
	case 'y':

		break;
	case 'z':

		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
