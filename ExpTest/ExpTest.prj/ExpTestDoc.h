// ExpTestDoc.h : interface of the ExpTestDoc class


#pragma once
#include "CDoc.h"
#include "findDlg.h"
#include "MainFrame.h"


enum DataSource {NotePadSrc, StoreSrc,  StoreAppdSrc,  StoreSortSrc,
                             StorePSrc, StorePNextSrc, StorePAppdSrc, StorePSortSrc};


class ExpTestDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;

protected: // create from serialization only

  ExpTestDoc() noexcept;
  DECLARE_DYNCREATE(ExpTestDoc)

public:

  virtual BOOL OnNewDocument();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds = NotePadSrc);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~ExpTestDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  bool loadFile(DataSource dataSrc, TCchar* title);
  void saveFile(TCchar* title, TCchar* suffix, TCchar* fileType);


  void testLine(int n);
  void wholePage();

  bool getSrchTgt(TCchar* explanation, String& target);


// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onFileOpen();

  afx_msg void onSaveStr();
  afx_msg void onSaveStrP();
  afx_msg void onSaveNotePad();

  afx_msg void onEditCopy();

#ifdef Examples
  afx_msg void OnTest();
  afx_msg void displayDataStore();

  afx_msg void onLoadStr();
  afx_msg void onAppendStr();
  afx_msg void onLoadSortStr();
  afx_msg void onSortStr();
  afx_msg void onRESrchStr();
  afx_msg void onLinSrchStr();
  afx_msg void onBinSrchStr();
  afx_msg void onDisplayStore();

  afx_msg void onLoadStrP();
  afx_msg void onLoadNextStrP();
  afx_msg void onLoadAppdStrP();
  afx_msg void onLoadSortStrP();
  afx_msg void onSortStrP();
  afx_msg void onRESrchStrP();
  afx_msg void onLinSrchStrP();
  afx_msg void onBinSrchStrP();
  afx_msg void onDisplayStoreP();

  afx_msg void OnTestEditBoxes();
#endif
  };




#if 0
  afx_msg void myButton();
  afx_msg void OnComboBoxChng();
  afx_msg void OnTBEditBox();
  afx_msg void myButton1();
#endif
