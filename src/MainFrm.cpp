
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Lab_01_3DEditor.h"
#include "Lab_01_3DEditorView.h"
#include <stdexcept>
#include "MainFrm.h"

using std::runtime_error;


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_CUBEBUTTON,
	ID_PIRAMIDE_BUTTON,
	ID_ROTATE_BUTTON,
	ID_MOVE_BUTTON,
	ID_SCALE_BUTTON,
	ID_COLORBUTTON,
	ID_SAVE_BUTTON,
	ID_LOAD_BUTTON//,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINTOOL) ||

		!m_wndToolBar.SetButtons(buttons,
			sizeof(buttons) / sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	/*mySld = new CSliderCtrl();
	mySld->Create(WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(300, 0, 500, 30), this, ID_CUBE_BUTTON);*/

	// TODO: Remove this if you don't want tool tips
	/*MyEdit = new CEdit();
	if (MyEdit != NULL) MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER,
		CRect(240, 10, 340, 50), this, 1234);*/
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	CFrameWnd::OnPaletteChanged(pFocusWnd);

	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CMainFrame::OnQueryNewPalette()
{
	int        i;
	CPalette    *pOldPal;
	CLab_01_3DEditorView   *pView = (CLab_01_3DEditorView *)GetActiveView();
	CClientDC   dc(pView);


	pOldPal = dc.SelectPalette(&pView->m_cPalette, FALSE);
	i = dc.RealizePalette();
	dc.SelectPalette(pOldPal, FALSE);

	if (i > 0)
		InvalidateRect(NULL);


	return CFrameWnd::OnQueryNewPalette();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// remove this flag to remove " - Untitled" from the frame's caption

	cs.style &= ~FWS_ADDTOTITLE;

	return CFrameWnd::PreCreateWindow(cs);
}