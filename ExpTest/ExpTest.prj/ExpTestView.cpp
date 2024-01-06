// ExpTestView.cpp : implementation of the ExpTestView class


#include "pch.h"
#include "ExpTestView.h"
#include "ExpTest.h"
#include "ExpTestDoc.h"
#include "ClipLine.h"
#include "IniFile.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"
#include "RptOrientDlgTwo.h"


static TCchar* StrOrietnKey = _T("StoreX");


IMPLEMENT_DYNCREATE(ExpTestView, CScrView)

BEGIN_MESSAGE_MAP(ExpTestView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()

  ON_WM_CONTEXTMENU()                     // Right Mouse Popup Menu
  ON_COMMAND(ID_Pup0, &onCopy)
  ON_COMMAND(ID_Pup1, &onPup1)
  ON_COMMAND(ID_Pup2, &onPup2)

END_MESSAGE_MAP()


ExpTestView::ExpTestView() noexcept {
ResourceData res;
String       pn;

  if (res.getProductName(pn)) prtNote.setTitle(pn);

  sub.LoadMenu(IDR_PopupMenu);
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


BOOL ExpTestView::PreCreateWindow(CREATESTRUCT& cs) {return CScrView::PreCreateWindow(cs);}


void ExpTestView::OnInitialUpdate() {CScrView::OnInitialUpdate();}


void ExpTestView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void ExpTestView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("StoreX:");

  if (dlg.DoModal() == IDOK) {
    saveRptOrietn();
    }
  }


void ExpTestView::initRptOrietn() { }


void ExpTestView::saveRptOrietn() {
  saveNoteOrietn();
  }



void ExpTestView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);     break;
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void ExpTestView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    }
  }


void ExpTestView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this); break;
    }
  }


void ExpTestView::displayHeader(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspHeader(dev);   break;
    }
  }


void ExpTestView::displayFooter(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspFooter(dev);   break;
    }
  }


void ExpTestView::printHeader(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc: prtNote.prtHeader(dev, pageNo);   break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void ExpTestView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    }
  }



void ExpTestView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void ExpTestView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void ExpTestView::OnLButtonDown(UINT nFlags, CPoint point)
                        {clipLine.set(point);   invalidate();   CScrView::OnLButtonDown(nFlags, point);}


void ExpTestView::OnLButtonDblClk(UINT nFlags, CPoint point)
  {clipLine.set(point);   RedrawWindow();   clipLine.load();   CScrView::OnLButtonDblClk(nFlags, point);}


void ExpTestView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
            {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }


void ExpTestView::onCopy() {clipLine.load();  invalidate();}


void ExpTestView::onPup1() {  }


void ExpTestView::onPup2() {  }


// ExpTestView diagnostics

#ifdef _DEBUG

void ExpTestView::AssertValid() const {CScrollView::AssertValid();}

void ExpTestView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}     // non-debug version is inline
                                             // non-debug version is inline
ExpTestDoc* ExpTestView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ExpTestDoc))); return (ExpTestDoc*)m_pDocument;}

#endif //_DEBUG



