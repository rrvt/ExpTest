// ExpTestView.cpp : implementation of the ExpTestView class


#include "stdafx.h"
#include "ExpTestView.h"
#include "ExpTest.h"
#include "ExpTestDoc.h"
#include "Options.h"
#include "Resources.h"


// ExpTestView

IMPLEMENT_DYNCREATE(ExpTestView, CScrView)

BEGIN_MESSAGE_MAP(ExpTestView, CScrView)
END_MESSAGE_MAP()


ExpTestView::ExpTestView() noexcept :
                                    #ifdef Examples
                                      dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()),
                                    #endif
                                    dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL ExpTestView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void ExpTestView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void ExpTestView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case NotePadSrc : prtNote.print(*this);  break;
#ifdef Examples
//      case StoreSrc   : prtStore.print(*this); break;
#endif
      }

  else
    switch(ds) {
      case NotePadSrc : dspNote.display(*this);  break;
#ifdef Examples
//      case StoreSrc   : dspStore.display(*this); break;
#endif
      }


  CScrView::onPrepareOutput(printing);
  }


void ExpTestView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
//    case StoreSrc   : setOrientation(options.orient); break;
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void ExpTestView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
#ifdef Examples
//    case StoreSrc   : prtStore.footer(dev, pageNo); break;
#endif
    }
  }



void ExpTestView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
//    case StoreSrc   : break;
    }
  }


void ExpTestView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
//    case StoreSrc   : break;
    }
  }


// ExpTestView diagnostics

#ifdef _DEBUG

void ExpTestView::AssertValid() const {CScrollView::AssertValid();}

void ExpTestView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
ExpTestDoc* ExpTestView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ExpTestDoc))); return (ExpTestDoc*)m_pDocument;}

#endif //_DEBUG
