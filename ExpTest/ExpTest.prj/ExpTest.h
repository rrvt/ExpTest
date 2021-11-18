// ExpTest.h : main header file for the ExpTest application

#pragma once
#include "CApp.h"


class ExpTestDoc;
class ExpTestView;
class MainFrame;


// ExpTest:
// See ExpTest.cpp for the implementation of this class

class ExpTest : public CApp {

public:

               ExpTest() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          ExpTestDoc*  doc()  {return (ExpTestDoc*)  CApp::getDoc();}
          ExpTestView* view() {return (ExpTestView*) CApp::getView();}
          MainFrame*       mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern ExpTest theApp;

inline void             invalidate() {theApp.invalidate();}
inline ExpTestDoc*  doc()        {return theApp.doc();}
inline ExpTestView* view()       {return theApp.view();}

