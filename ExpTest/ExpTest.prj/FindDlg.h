#pragma once
#include "afxdialogex.h"


// FindDlg dialog

class FindDlg : public CDialogEx {

  DECLARE_DYNAMIC(FindDlg)

public:

CString explanation;
CString target;

               FindDlg(CWnd* pParent = nullptr);          // standard constructor
  virtual     ~FindDlg();

  virtual BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_FindDlg };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
