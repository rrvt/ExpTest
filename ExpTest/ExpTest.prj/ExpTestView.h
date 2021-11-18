// ExpTestView.h : interface of the ExpTestView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"
#ifdef Examples
#include "StoreRpt.h"
#endif


class ExpTestDoc;


class ExpTestView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;
#ifdef Examples
StoreRpt   dspStore;
StoreRpt   prtStore;
#endif

protected: // create from serialization only

  ExpTestView() noexcept;

  DECLARE_DYNCREATE(ExpTestView)

public:

  virtual ~ExpTestView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  ExpTestDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in ExpTestView.cpp
inline ExpTestDoc* ExpTestView::GetDocument() const
   { return reinterpret_cast<ExpTestDoc*>(m_pDocument); }
#endif

