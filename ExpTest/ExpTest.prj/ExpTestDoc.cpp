 // ExpTestDoc.cpp : implementation of the ExpTestDoc class


#include "pch.h"
#include "ExpTestDoc.h"
#include "ExpTest.h"
#include "ExpTestView.h"
#include "ClipLine.h"
#include "filename.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Printer.h"
#include "RegExpr.h"
#include "Resource.h"
#include "Store.h"
#include "StoreP.h"


static TCchar* REexplanation =
                     _T("This is an unachored search of the title screen with the regular expression ")
                     _T("target in the edit box below.\n\n")
                     _T("  ^  - At beginning of line indicates an achored match\n")
                     _T("  $  - At end of line must match the end of the line\n")
                     _T("  .  - Matches any character\n")
                     _T("  [] - Set, Collection of characters to match at the position in the line\n")
                     _T("  *  - Kleene Closure of preceding pattern (Tchar, metachar or set\n")
                     _T("  \\  - Escape, next character used literally\n")
                     _T("  \\t - Tab character\n\n")
                     _T("  Sets (i.e. [...])\n")
                     _T("  ^  - When First character in set, indicates match is not a character in set\n")
                     _T("  -  - When not first character indicates an inclusive range of characters\n")
                     _T("  \\  - Escape, When not last character in set, include next character in set");

static TCchar* LinExplanation =
                     _T("This is a linear search of the data vector.  The equality test is made of each ")
                     _T("of the title strings prefix that is the same length as the input target.  It ")
                     _T("stops searching when a match is found.")
                     _T("")
                     _T("")
                     _T("")
                     _T("")
                     _T("")
                     _T("");

static TCchar* BinExplanation =
                     _T("This is a binary search of the data vector.  The vector must be sorted.")
                     _T("The comparisons with the target string is the prefix ")
                     _T("of the title strings prefix that is the same length as the input target.  It ")
                     _T("stops searching when a match is found.")
                     _T("")
                     _T("")
                     _T("")
                     _T("")
                     _T("");



// ExpTestDoc

IMPLEMENT_DYNCREATE(ExpTestDoc, CDoc)

BEGIN_MESSAGE_MAP(ExpTestDoc, CDoc)
  ON_COMMAND(      ID_File_Open,     &onFileOpen)

  ON_COMMAND(      ID_SavePopup,     &onSaveStr)
  ON_COMMAND(      ID_SaveStr,       &onSaveStr)
  ON_COMMAND(      ID_SaveStrP,      &onSaveStrP)
  ON_COMMAND(      ID_SaveNotePad,   &onSaveNotePad)

  ON_COMMAND(      ID_EDIT_COPY,     &onEditCopy)

#ifdef Examples
  ON_COMMAND(      ID_Test,           &OnTest)
  ON_COMMAND(      ID_SelDataStr,     &displayDataStore)

  ON_COMMAND(      ID_Menu1,          &onLoadStr)
  ON_COMMAND(      ID_LoadStr,        &onLoadStr)
  ON_COMMAND(      ID_AppendStr,      &onAppendStr)
  ON_COMMAND(      ID_LoadSortStr,    &onLoadSortStr)
  ON_COMMAND(      ID_SortStr,        &onSortStr)
  ON_COMMAND(      ID_RESrchStr,      &onRESrchStr)
  ON_COMMAND(      ID_LinSrchStr,     &onLinSrchStr)
  ON_COMMAND(      ID_BinSrchStr,     &onBinSrchStr)
  ON_COMMAND(      ID_DisplayStore,   &onDisplayStore)

  ON_COMMAND(      ID_Menu2,          &onLoadStrP)
  ON_COMMAND(      ID_LoadStrP,       &onLoadStrP)
  ON_COMMAND(      ID_LoadNextStrP,   &onLoadNextStrP)
  ON_COMMAND(      ID_LoadAppdStrP,   &onLoadAppdStrP)
  ON_COMMAND(      ID_LoadSortStrP,   &onLoadSortStrP)
  ON_COMMAND(      ID_SortStrP,       &onSortStrP)
  ON_COMMAND(      ID_RESrchStrP,     &onRESrchStrP)
  ON_COMMAND(      ID_LinSrchStrP,    &onLinSrchStrP)
  ON_COMMAND(      ID_BinSrchStrP,    &onBinSrchStrP)
  ON_COMMAND(      ID_DisplayStoreP,  &onDisplayStoreP)
#endif
END_MESSAGE_MAP()


// ExpTestDoc construction/destruction

ExpTestDoc::ExpTestDoc() noexcept : dataSource(NotePadSrc) {
  pathDlgDsc(_T("Ugly Example"), _T(""), _T("csv"), _T("*.csv"));
  }

ExpTestDoc::~ExpTestDoc() { }


BOOL ExpTestDoc::OnNewDocument() {return CDocument::OnNewDocument();}

#ifdef Examples


void ExpTestDoc::onLoadStr()  {

  notePad.clear();   notePad << _T("Load Source to Expandable") << nCrlf << nCrlf;

  loadFile(StoreSrc, _T("Text file"));   display();
  }


void ExpTestDoc::onAppendStr() {
  notePad.clear();   notePad << _T("Load Source to Expandable by appending") << nCrlf << nCrlf;

  loadFile(StoreAppdSrc, _T("Text file"));   display();
  }


void ExpTestDoc::onLoadSortStr() {
  notePad.clear();   notePad << _T("Load Source to Expandable Sorted") << nCrlf << nCrlf;

  loadFile(StoreSortSrc, _T("Text file"));   display();
  }


void ExpTestDoc::onSortStr() {store.sort();}


void ExpTestDoc::onRESrchStr() {
String    target;
RegExpr   re;
StoreIter iter(store);
Datum*    dtm;
int       tab;

  if (!getSrchTgt(REexplanation, target)) return;

  notePad.clear();   re.setPattern(target);

  for (tab = 0, dtm = iter(); dtm; dtm = iter++)
                                  if (*dtm == re && tab < dtm->title.length()) tab = dtm->title.length();

  for (dtm = iter(); dtm; dtm = iter++) if (*dtm == re) dtm->display(tab);

  display();
  }


void ExpTestDoc::onLinSrchStr() {
String target;
Datum* dtm;

  if (!getSrchTgt(LinExplanation, target)) return;

  dtm = store.find(target);    if (!dtm) return;

  notePad.clear();   dtm->display(dtm->title.length());   display();
  }


void ExpTestDoc::onBinSrchStr() {
String target;
Datum* dtm;

  if (!getSrchTgt(BinExplanation, target)) return;

  dtm = store.bSearch(target);    if (!dtm) return;

  notePad.clear();   dtm->display(dtm->title.length());   display();
  }


bool ExpTestDoc::getSrchTgt(TCchar* explanation, String& target) {
FindDlg dlg;

  dlg.explanation = explanation;   dlg.target = target;

  if (dlg.DoModal() == IDOK) {target = dlg.target;   return true;}

  return false;
  }


void ExpTestDoc::onDisplayStore()
                          {notePad << _T("Display Store") << nCrlf << nCrlf; store.display(); display();}


void ExpTestDoc::onLoadStrP() {
  notePad.clear();   notePad << _T("Load Source to ExpandableP") << nCrlf << nCrlf;

  loadFile(StorePSrc, _T("Text file"));   display();
  }


void ExpTestDoc::onLoadAppdStrP() {
  notePad.clear();   notePad << _T("Load Source to ExpandableP") << nCrlf << nCrlf;

  loadFile(StorePAppdSrc, _T("Text file"));   display();
  }


void ExpTestDoc::onLoadNextStrP() {
  notePad.clear();   notePad << _T("Load Source to ExpandableP") << nCrlf << nCrlf;

  loadFile(StorePNextSrc, _T("Text file"));   display();
  }


void ExpTestDoc::onLoadSortStrP() {
  notePad.clear();   notePad << _T("Load Source to ExpandableP") << nCrlf << nCrlf;

  loadFile(StorePSortSrc, _T("Text file"));   display();
  }


void ExpTestDoc::onSortStrP() {storeP.sort();}


void ExpTestDoc::onRESrchStrP() {
String     target;
RegExpr    re;
StorePIter iter(storeP);
Dtm*       dtm;
int        tab;

  if (!getSrchTgt(REexplanation, target)) return;

  notePad.clear();   re.setPattern(target);

  for (tab = 0, dtm = iter(); dtm; dtm = iter++)
                                  if (*dtm == re && tab < dtm->title.length()) tab = dtm->title.length();

  for (dtm = iter(); dtm; dtm = iter++) if (*dtm == re) dtm->display(tab);

  display();
  }


void ExpTestDoc::onLinSrchStrP() {
String target;
Dtm*   dtm;

  if (!getSrchTgt(LinExplanation, target)) return;

  dtm = storeP.find(target);    if (!dtm) return;

  notePad.clear();   dtm->display(dtm->title.length());   display();
  }


void ExpTestDoc::onBinSrchStrP() {
String target;
Dtm*   dtm;

  if (!getSrchTgt(LinExplanation, target)) return;

  dtm = storeP.bSearch(target);    if (!dtm) return;

  notePad.clear();   dtm->display(dtm->title.length());   display();
  }


void ExpTestDoc::onDisplayStoreP()
                     {notePad << _T("Display StoreP") << nCrlf << nCrlf;   storeP.display();   display();}


void ExpTestDoc::OnTestEditBoxes() {display();}


// ExpTestDoc commands


void ExpTestDoc::OnTest() {
int n;

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = printer.orient == LandOrient ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display();
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


void ExpTestDoc::displayDataStore() { }

#endif


void ExpTestDoc::onEditCopy() {clipLine.load();}


void ExpTestDoc::onFileOpen() {

  notePad.clear();

  pathDlgDsc(_T("Ugly Example"), pathDlgDsc.name, _T("csv"), _T("*.csv"));

  if (!setOpenPath(pathDlgDsc)) return;

  pathDlgDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));
  }


void ExpTestDoc::onSaveStr()  {dataSource = StoreSrc;    saveFile(_T("Save File"), _T(""), _T("csv"));}


void ExpTestDoc::onSaveStrP() {dataSource = StorePSrc;   saveFile(_T("Save File"), _T(""), _T("csv"));}


void ExpTestDoc::onSaveNotePad()
    {   if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);  }


void ExpTestDoc::display(DataSource ds) {dataSource = ds; invalidate();}


bool ExpTestDoc::loadFile(DataSource dataSrc, TCchar* title) {

  pathDlgDsc(title, pathDlgDsc.name, _T("csv"), _T("*.csv"));

  dataSource = dataSrc;  if (!setOpenPath(pathDlgDsc)) return false;

  pathDlgDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) {messageBox(_T(" Not Loaded!")); return false;}

  return true;
  }


void ExpTestDoc::saveFile(TCchar* title, TCchar* suffix, TCchar* fileType) {
String fileName = path;
int    pos      = fileName.find_last_of(_T('\\'));
String ext      = _T("*."); ext += fileType;
String ttl      = title;    ttl += _T(" Output");

  fileName = fileName.substr(pos+1);   pos = fileName.find_first_of(_T('.'));
  fileName = fileName.substr(0, pos);  fileName += suffix;

  pathDlgDsc(ttl, fileName, fileType, ext);

  if (setSaveAsPath(pathDlgDsc)) {backupFile(5);   OnSaveDocument(path);}
  }


// UglyDoc serialization

void ExpTestDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {

      case StoreSrc   : store.save(ar);      return;          // Save content of store
      case StorePSrc  : storeP.save(ar);     return;          // Save content of storeP
      case NotePadSrc : notePad.archive(ar); return;          // Save what is seen in the window
      default         : return;
      }

  else
    switch(dataSource) {
      case StoreSrc     : store.load(ar);         return;     // Load by indexing into data
      case StoreAppdSrc : store.loadAppend(ar);   return;     // Load local Datum and copy at end of data
                                                              // vector with "+=" operator
      case StoreSortSrc : store.loadSorted(ar);   return;     // Load local Datum and copy into data
                                                              // sorted with "=" operator
      case StorePSrc    : storeP.load(ar);        return;     // Copy allocated Dtm object address into
                                                              // vector indexed by i.
      case StorePNextSrc: storeP.loadNext(ar);    return;     // Copy loaded dtm object to end of vector
      case StorePAppdSrc: storeP.loadAppend(ar);  return;     // Append allocated Dtm object to data using
                                                              // the "+=" operator
      case StorePSortSrc: storeP.loadSorted(ar);  return;     // Insertion sort the Dtm object into data
                                                              // using the "=" operator
      default           : return;
      }
  }


// ExpTestDoc diagnostics

#ifdef _DEBUG
void ExpTestDoc::AssertValid() const {         CDocument::AssertValid();}
void ExpTestDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG






#if 0

static CbxItem cbxText[] = {{_T("Zeta"),     1},
                            {_T("Beta"),     2},
                            {_T("Alpha"),    3},
                            {_T("Omega"),    4},
                            {_T("Phi"),      5},
                            {_T("Mu"),       6},
                            {_T("Xi"),       7},
                            {_T("Omicron"),  8},
                            {_T("Pi"),       9},
                            {_T("Rho"),     10},
                            {_T("Sigma"),   11},
                            {_T("Nu"),      12},
                            {_T("Kappa"),   13},
                            {_T("Iota"),    14}
                            };
static TCchar* CbxCaption = _T("Greeks");


void ExpTestDoc::OnComboBoxChng() {
ToolBar& toolBar = getToolBar();
String   s;
int      x;

  if (toolBar.getCbxSel(ID_CBox, s, x))
                               notePad << _T("On Change, Item = ") << s << _T(", Data = ") << x << nCrlf;
  display();
  }


void ExpTestDoc::OnTBEditBox() {
ToolBar& toolBar = getToolBar();
String   s;

  if (toolBar.getEbxText(ID_EditBox, s)) notePad << s << nCrlf;

  display();
  }


void ExpTestDoc::myButton1() {
ToolBar& toolBar = getToolBar();
String   s;

  if (toolBar.getEbxText(ID_EditBox, s)) notePad << s << nCrlf;

  display();
  }
#endif

