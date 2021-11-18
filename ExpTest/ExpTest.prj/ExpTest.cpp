// ExpTest.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "ExpTest.h"
#include "AboutDlg.h"
#include "ExtraResource.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "Options.h"
#include "ExpTestDoc.h"
#include "ExpTestView.h"


ExpTest theApp;                       // The one and only ExpTest object
IniFile     iniFile;


// ExpTest

BEGIN_MESSAGE_MAP(ExpTest, CWinAppEx)
  ON_COMMAND(ID_File_New,         &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &OnHelp)
  ON_COMMAND(ID_App_About,        &OnAppAbout)
END_MESSAGE_MAP()


// ExpTest initialization

BOOL ExpTest::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

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

  setAppName(_T("Exp Test")); setTitle(_T("Do Test"));

  view()->setFont(_T("Arial"), 12.0);

  options.load();    view()->setOrientation(options.orient);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



void ExpTest::OnFilePrintSetup() {
PrtrOrient orient;

  view()->setPrntrOrient(getDevMode());

    CWinApp::OnFilePrintSetup();

  orient = view()->getPrntrOrient(getDevMode());

  options.setOrient(orient);   view()->setOrientation(options.orient);
  }


int ExpTest::ExitInstance() {

#ifdef DebugMemoryLeaks
  _CrtDumpMemoryLeaks();
#endif

  return CApp::ExitInstance();
  }


void ExpTest::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void ExpTest::OnAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

