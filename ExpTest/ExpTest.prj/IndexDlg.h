// Test Index dialog Box


#pragma once
#include "Resource.h"


// IndexDlg dialog

class IndexDlg : public CDialogEx {

  DECLARE_DYNAMIC(IndexDlg)

public:
CString indexReq;
CString index;

  IndexDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~IndexDlg();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Index };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
