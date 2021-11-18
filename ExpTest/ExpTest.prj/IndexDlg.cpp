// IndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IndexDlg.h"


// IndexDlg dialog

IMPLEMENT_DYNAMIC(IndexDlg, CDialogEx)

IndexDlg::IndexDlg(CWnd* pParent) : CDialogEx(IDD_Index, pParent), indexReq(_T("")), index(_T("")) { }


IndexDlg::~IndexDlg() { }


void IndexDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_IndexReq, indexReq);
  DDX_Text(pDX, IDC_Index,    index);
  }


BEGIN_MESSAGE_MAP(IndexDlg, CDialogEx)
END_MESSAGE_MAP()

