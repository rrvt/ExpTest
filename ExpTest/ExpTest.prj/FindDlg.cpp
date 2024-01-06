// FindDlg.cpp : implementation file
//

#include "pch.h"
#include "ExpTest.h"
#include "afxdialogex.h"
#include "FindDlg.h"
#include "Resource.h"


// FindDlg dialog

IMPLEMENT_DYNAMIC(FindDlg, CDialogEx)

FindDlg::FindDlg(CWnd* pParent) : CDialogEx(IDD_FindDlg, pParent), explanation(_T("")), target(_T("")) { }

FindDlg::~FindDlg() { }


void FindDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_Explanation, explanation);
  DDX_Text(pDX, IDC_Target,      target);
  }


BEGIN_MESSAGE_MAP(FindDlg, CDialogEx)
END_MESSAGE_MAP()


// FindDlg message handlers


BOOL FindDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // TODO:  Add extra initialization here

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
