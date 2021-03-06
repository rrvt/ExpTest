// ExpTestDoc.h : interface of the ExpTestDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"


enum DataSource {NotePadSrc, StoreSrc, FontSrc};


class ExpTestDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;

protected: // create from serialization only

  ExpTestDoc() noexcept;
  DECLARE_DYNCREATE(ExpTestDoc)

public:

  virtual BOOL OnNewDocument();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~ExpTestDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void testLine(int n);
  void wholePage();

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnFileOpen();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();

#ifdef Examples
  afx_msg void OnTest();
  afx_msg void displayDataStore();
  afx_msg void myButton();

  afx_msg void OnComboBoxChng();

  afx_msg void OnTBEditBox();
  afx_msg void myButton1();
  afx_msg void onOption11();
  afx_msg void onOption12();
  afx_msg void onOption13();
  afx_msg void onOption21();
  afx_msg void onOption22();
  afx_msg void onOption23();
  afx_msg void OnTestEditBoxes();
#endif
  };
