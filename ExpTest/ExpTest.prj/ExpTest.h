// ExpTest.h : main header file for the ExpTest application

#pragma once
#include "CApp.h"
#include "MainFrame.h"


class ExpTestDoc;
class ExpTestView;


class ExpTest : public CApp {

String roamPath;
String appPath;

public:

               ExpTest() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          ExpTestDoc*  doc()         {return (ExpTestDoc*)  CApp::getDoc();}
          ExpTestView* view()        {return (ExpTestView*) CApp::getView();}
          MainFrame*       mainFrm()     {return (MainFrame*)       m_pMainWnd;}
          String&          roamingPath() {return roamPath;}
          String&          thisAppPath() {return appPath;}

  DECLARE_MESSAGE_MAP()

  afx_msg void onAppAbout();
  afx_msg void onHelp();
  };


extern ExpTest theApp;

inline void             invalidate() {theApp.invalidate();}
inline ExpTestDoc*  doc()        {return theApp.doc();}
inline ExpTestView* view()       {return theApp.view();}
inline MainFrame*       mainFrm()    {return theApp.mainFrm();}
inline ToolBar&         getToolBar() {return mainFrm()->getToolBar();}

