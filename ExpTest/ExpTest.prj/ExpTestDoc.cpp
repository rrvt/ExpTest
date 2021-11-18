// ExpTestDoc.cpp : implementation of the ExpTestDoc class


#include "stdafx.h"
#include "ExpTestDoc.h"
#include "ExtraResource.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "IndexDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "ExpTest.h"
#include "ExpTestView.h"
#include "Store.h"
#include "StoreP.h"
#include "ToolBar.h"


// ExpTestDoc

IMPLEMENT_DYNCREATE(ExpTestDoc, CDoc)

BEGIN_MESSAGE_MAP(ExpTestDoc, CDoc)

  ON_COMMAND(ID_Btn1,          &onOption11)
  ON_COMMAND(ID_Option11,      &onOption11)
  ON_COMMAND(ID_Option12,      &onOption12)
  ON_COMMAND(ID_Option13,      &onOption13)
  ON_COMMAND(ID_Option14,      &onOption14)
  ON_COMMAND(ID_Option15,      &onOption15)

  ON_COMMAND(ID_Btn2,          &onOption21)
  ON_COMMAND(ID_Option21,      &onOption21)
  ON_COMMAND(ID_Option22,      &onOption22)
  ON_COMMAND(ID_Option23,      &onOption23)
  ON_COMMAND(ID_Option24,      &onOption24)

  ON_COMMAND(ID_Btn3,          &onOption31)
  ON_COMMAND(ID_Option31,      &onOption31)
  ON_COMMAND(ID_Option32,      &onOption32)
  ON_COMMAND(ID_Option33,      &onOption33)
  ON_COMMAND(ID_Option34,      &onOption34)
  ON_COMMAND(ID_Option35,      &onOption35)

  ON_COMMAND(ID_Btn4,          &onOption41)
  ON_COMMAND(ID_Option41,      &onOption41)
  ON_COMMAND(ID_Option42,      &onOption42)
  ON_COMMAND(ID_Option43,      &onOption43)
  ON_COMMAND(ID_Option44,      &onOption44)

  ON_COMMAND(ID_File_Save,     &OnFileSave)
  ON_COMMAND(ID_Options,       &OnOptions)

#ifdef Examples
  ON_COMMAND(ID_Test,          &OnTest)
  ON_COMMAND(ID_SelDataStr,    &displayDataStore)

  ON_COMMAND(ID_MyBtn,         &myButton)

  ON_CBN_SELCHANGE(ID_CB,      &OnComboBoxChng)
  ON_COMMAND(      ID_CB,      &OnComboBoxChng)

  ON_COMMAND(ID_EditBox,       &OnTBEditBox)


#endif
END_MESSAGE_MAP()


// ExpTestDoc construction/destruction

ExpTestDoc::ExpTestDoc() noexcept : dataSource(NotePadSrc) {
  pathDlgDsc = PathDlgDsc(_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt"));
  }

ExpTestDoc::~ExpTestDoc() { }



void ExpTestDoc::onOption11()
                            {if (askPath()) {storeP.load(path); storeP.display();}  display(NotePadSrc);}
void ExpTestDoc::onOption12() {linearSrchP();  display(NotePadSrc);}
void ExpTestDoc::onOption13() {binarySrchP();  display(NotePadSrc);}
void ExpTestDoc::onOption14() {insertDelP();   display(NotePadSrc);}
void ExpTestDoc::onOption15() {
  storeP.sort();   notePad << nCrlf << _T("Sorted Result") << nCrlf;

  storeP.display();   display(NotePadSrc);
  }


void ExpTestDoc::onOption21()
                   {if (askPath()) {storeP.loadSorted(path);   storeP.display();}   display(NotePadSrc);}

void ExpTestDoc::onOption22() {linearSrchP();  display(NotePadSrc);}
void ExpTestDoc::onOption23() {binarySrchP();  display(NotePadSrc);}
void ExpTestDoc::onOption24() {insertDelP();   display(NotePadSrc);}


void ExpTestDoc::linearSrchP() {
StorePIter iter(storeP);
Words*     words;

  notePad.clear();

  notePad << _T("Linear Search of StoreP Object") << nCrlf;

  notePad << nClrTabs << nSetTab(40) << nSetTab(50);

  for (words = iter(); words; words = iter++) dspRslt(words->zero, storeP.find(words->zero));
  }


void ExpTestDoc::binarySrchP() {
StorePIter iter(storeP);
Words*     words;

  notePad.clear();

  notePad << _T("Binary Search of StoreP Object") << nCrlf;

  notePad << nClrTabs << nSetTab(40) << nSetTab(50);

  for (words = iter(); words; words = iter++) dspRslt(words->zero, storeP.bSearch(words->zero));
  }


void ExpTestDoc::insertDelP() {
IndexDlg dlg;
String   s;
int      x;
uint     i;
Words    words;
int      n = storeP.nData();

  words.serial = 999;
  words.zero   = _T("XXXXXX");
  words.one    = _T("YYYYYYY");

  dlg.indexReq = s.format(_T("%s %i"), _T("Pick an index (zero indexing) between 0 and "), n);

  if (dlg.DoModal() != IDOK) return;

  s = dlg.index;   x = s.stoi(i);

  if (!storeP.insert(x, words)) {notePad << _T("Insertion Failed") << nCrlf; return;}

  notePad << nCrlf << _T("After Insertion") << nCrlf << nCrlf;    storeP.display();

  if (!storeP.del(x)) {notePad << _T("Deletion Failed") << nCrlf; return;}

  notePad << nCrlf << _T("After Delete") << nCrlf << nCrlf;    storeP.display();
  }



void ExpTestDoc::dspRslt(TCchar* key, Words* words) {

  notePad << _T("Key: ") << key << nTab;

  if (words) {notePad << _T(" -- found: ") << nTab;   display(words);}
  else        notePad << _T(" *** not found ***");

  notePad << nCrlf;
  }


void ExpTestDoc::display(Words* words) {
                               notePad << words->zero;
  if (!words->one.isEmpty())   notePad << _T(", ") << words->one;
  if (!words->two.isEmpty())   notePad << _T(", ") << words->two;
  if (!words->three.isEmpty()) notePad << _T(", ") << words->three;
  if (!words->rest.isEmpty())  notePad << _T(", ") << words->rest;
  }


#ifdef SimpleStore

void ExpTestDoc::onOption31()
                            {if (askPath()) {store.load(path); store.display();}    display(NotePadSrc);}
#else
void ExpTestDoc::onOption31() { }
#endif

void ExpTestDoc::onOption32() {linearSrch();   display(NotePadSrc);}
void ExpTestDoc::onOption33() {binarySrch();   display(NotePadSrc);}
void ExpTestDoc::onOption34() {insertDel();    display(NotePadSrc);}
void ExpTestDoc::onOption35() {

  store.sort();   notePad << nCrlf << _T("Sorted Result") << nCrlf;

  store.display();   display(NotePadSrc);
  }

#ifdef SimpleStore

void ExpTestDoc::onOption41()
                      {if (askPath()) {store.loadSorted(path);  store.display();}   display(NotePadSrc);}
#else
void ExpTestDoc::onOption41() { }
#endif


void ExpTestDoc::onOption42() {linearSrch();   display(NotePadSrc);}
void ExpTestDoc::onOption43() {binarySrch();   display(NotePadSrc);}
void ExpTestDoc::onOption44() {insertDel();    display(NotePadSrc);}


bool ExpTestDoc::askPath() {

  notePad.clear();

  pathDlgDsc = PathDlgDsc(_T("Data File"), pathDlgDsc.name, _T("txt"), _T("*.txt"));

  return getPathDlg(pathDlgDsc, path);
  }


#ifdef SimpleStore

void ExpTestDoc::linearSrch() {
StoreIter iter(store);
Datum*    datum;

  notePad.clear();

  notePad << _T("Linear Search of StoreP Object") << nCrlf;

  notePad << nClrTabs << nSetRTab(10) << nSetTab(12) << nSetRTab(25) << nSetTab(27);

  for (datum = iter(); datum; datum = iter++) dspRslt(datum->key, store.find(datum->key));
  }


void ExpTestDoc::binarySrch() {
StoreIter iter(store);
Datum*    datum;

  notePad.clear();

  notePad << _T("Binary Search of StoreP Object") << nCrlf;

  notePad << nClrTabs << nSetRTab(10) << nSetTab(12) << nSetRTab(25) << nSetTab(27);

  for (datum = iter(); datum; datum = iter++) dspRslt(datum->key, store.bSearch(datum->key));
  }


void ExpTestDoc::insertDel() {
IndexDlg dlg;
String   s;
int      x;
uint     i;
Datum    datum;
int      n = store.nData();

  datum.key    = 999999;
  datum.line   = _T("XXXXXX YYYYYYY");

  dlg.indexReq = s.format(_T("%s %i"), _T("Pick an index (zero indexing) between 0 and "), n);

  if (dlg.DoModal() != IDOK) return;

  s = dlg.index;   x = s.stoi(i);

  if (!store.insert(x, datum)) {notePad << _T("Insertion Failed") << nCrlf; return;}

  notePad << nCrlf << _T("After Insertion") << nCrlf << nCrlf;    store.display();

  if (!store.del(x)) {notePad << _T("Deletion Failed") << nCrlf; return;}

  notePad << nCrlf << _T("After Delete") << nCrlf << nCrlf;    store.display();
  }


void ExpTestDoc::dspRslt(ulong key, Datum* datum) {

  notePad << _T("Key: ") << nTab << key << nTab;

  if (datum) {notePad << _T(" -- found: ") << nTab << datum->key << nTab << datum->line;}
  else        notePad << _T(" *** not found ***");

  notePad << nCrlf;
  }
#else
void ExpTestDoc::linearSrch() { }
void ExpTestDoc::binarySrch() { }
#endif


BOOL ExpTestDoc::OnNewDocument() {return CDocument::OnNewDocument();}

#ifdef Examples

static TCchar* cbText[] = {_T("Zeta"),
                           _T("Beta"),
                           _T("Alpha"),
                           _T("Omega"),
                           _T("Phi"),
                           _T("Mu"),
                           _T("Xi"),
                           _T("Omicron"),
                           _T("Pi"),
                           _T("Rho"),
                           _T("Sigma"),
                           _T("Nu"),
                           _T("Kappa"),
                           _T("Iota")
                           };


void ExpTestDoc::myButton() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int n = noElements(cbText);
int i;
int x;

  dataSource = NotePadSrc;

  notePad << _T("My Button") << nCrlf;

  if (!cb) {invalidate();  return;}

//  cb->SetText(_T("Greeks"));

  for (i = 0; i < n; i++) if (cb->findExact(cbText[i]) < 0) {

    x = cb->AddSortedItem(cbText[i], i);                           //AddSortedItem

    String s;  s.format(_T("%02i: "), i);

    notePad << s << _T("Pos = ") << x << _T(". Added ") << cbText[i] << nCrlf;
    }

  cb->SelectItem(-1);
  cb->SetText(_T("Greeks"));

  notePad << _T("Greeks") << nCrlf;  display(NotePadSrc);
  }


void ExpTestDoc::OnComboBoxChng() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int        i;
String     s;
int        x;
MainFrame* mf = theApp.mainFrm();

  if (!cb)   return;
  i  = cb->GetCurSel();    if (i < 0) return;
  s  = cb->GetItem(i);
  x  = cb->GetItemData(i);   mf->SetFocus();

  notePad << _T("On Change, Item = ") << s << _T(", Data = ") << x << nCrlf;

  display(NotePadSrc);
  }



void ExpTestDoc::OnTBEditBox() {
TBEditBox*  eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String      s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }


void ExpTestDoc::myButton1() {
TBEditBox* eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String     s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }




void ExpTestDoc::OnTestEditBoxes() {display(NotePadSrc);}


// ExpTestDoc commands


void ExpTestDoc::OnTest() {
int n;

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = options.orient == Landscape ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display(NotePadSrc);
  }


void ExpTestDoc::testLine(int n) {
int i;

  for (i = 0; i < n; i++) {

    if (!i) notePad << _T('|'); else notePad << i;

    notePad << _T("123456789");
    }

  notePad << _T('|') << nCrlf;
  }


void ExpTestDoc::wholePage() {
int    i;
int    j;
String s;

  notePad << nSetRTab(4) << nSetTab(6) << nSetTab(8) << nSetRTab(12) << nSetTab(14);

  for (i = 0; i < 100; i++) {
    s.format(_T("%3i:"), i);

    notePad << nTab << s << nTab << _T("X") << nTab << _T("Y") << nTab << i << nTab;

    for (j = i+1; j < i+68; j++) {s.format(_T("%i"), j);   s = s.substr(s.length()-1);  notePad << s;}

    notePad << nCrlf;
    }
  }


void ExpTestDoc::displayDataStore() {display(NotePadSrc);}

#endif


void ExpTestDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void ExpTestDoc::display(DataSource ds) {dataSource = ds; invalidate();}





void ExpTestDoc::OnFileSave() {if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);}


// UglyDoc serialization

void ExpTestDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : notePad.archive(ar); return;
#ifdef Examples
  //    case NotePadSrc: store.store(ar); return;
#endif
      default         : return;
      }

  else
#if 1
  return;
#else
    switch(dataSource) {
#ifdef Examples
    //  case NotePadSrc : store.load(ar); return;
#endif
      case FontSrc  :
      default       : return;
      }
#endif
  }


// ExpTestDoc diagnostics

#ifdef _DEBUG
void ExpTestDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void ExpTestDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

