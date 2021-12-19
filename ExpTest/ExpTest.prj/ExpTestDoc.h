// ExpTestDoc.h : interface of the ExpTestDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"

class Words;
class Datum;
#define SimpleStore

enum DataSource {NotePadSrc};


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

  bool askPath();
  void linearSrchP();
  void binarySrchP();
  void insertDelP();
  void display(Words* words);

  void linearSrch();
  void binarySrch();
  void insertDel();
  void dspRslt(TCchar* key, Words* words);
  void dspRslt(ulong   key, Datum* datum);

  void testLine(int n);
  void wholePage();

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onOption11();
  afx_msg void onOption12();
  afx_msg void onOption13();
  afx_msg void onOption14();
  afx_msg void onOption15();

  afx_msg void onOption21();
  afx_msg void onOption22();
  afx_msg void onOption23();
  afx_msg void onOption24();

  afx_msg void onOption31();
  afx_msg void onOption32();
  afx_msg void onOption33();
  afx_msg void onOption34();
  afx_msg void onOption35();

  afx_msg void onOption41();
  afx_msg void onOption42();
  afx_msg void onOption43();
  afx_msg void onOption44();

  afx_msg void OnFileSave();
  afx_msg void OnOptions();

#ifdef Examples
  afx_msg void OnTest();
  afx_msg void displayDataStore();
  afx_msg void myButton();

  afx_msg void OnComboBoxChng();

  afx_msg void OnTBEditBox();
  afx_msg void myButton1();
  afx_msg void OnTestEditBoxes();
#endif
  };
