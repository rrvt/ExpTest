// ExpTest.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "ExpTest.h"
#include "AboutDlg.h"
#include "ExpTestDoc.h"
#include "ExpTestView.h"
#include "FileName.h"
#include "IniFile.h"
#include "NotePad.h"
#include "Resource.h"

ExpTest theApp;                       // The one and only ExpTest object
IniFile     iniFile;


// ExpTest

BEGIN_MESSAGE_MAP(ExpTest, CWinAppEx)

  ON_COMMAND(ID_Help,      &onHelp)
  ON_COMMAND(ID_App_About, &onAppAbout)

END_MESSAGE_MAP()


// ExpTest initialization

BOOL ExpTest::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  roamPath = getPath(iniFile.getAppDataPath(m_pszHelpFilePath));
  appPath  = getPath(m_pszHelpFilePath);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(ExpTestDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(ExpTestView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

//  EnableShellOpen(); RegisterShellFileTypes(TRUE);       // Enable DDE Execute open

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("Expandable Test")); setTitle(_T("Result Window"));

  view()->setFont(_T("Arial"), 12.0);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



int ExpTest::ExitInstance() {

#ifdef DebugMemoryLeaks
  _CrtDumpMemoryLeaks();
#endif

  return CApp::ExitInstance();
  }


void ExpTest::onHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void ExpTest::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

