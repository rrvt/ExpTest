// ExpandableP Store Example


#pragma once
#include "Archive.h"
#include "CSVLex.h"
#include "CSVOut.h"
#include "Date.h"
#include "ExpandableP.h"
#include "IterT.h"
#include "qsort.h"
#include "RegExpr.h"


class Dtm {

public:

public:
String title;
String channel;
Date   date;
String comment;
bool   bobPresent;
bool   maureenPresent;

         Dtm() : bobPresent(false), maureenPresent(false) { }
         Dtm(Dtm& dtm) {copy(dtm);}

  bool   load(CSVLex& lex);
  void   save(CSVOut& csv);

  void   display(int tab);

  Dtm&   operator= (Dtm& dtm) {copy(dtm); return *this;}

  // Required for Insertion Sort, i.e. data = dtm;           // _tcsicmp
  bool   operator>= (Dtm& dtm) {return _tcsicmp(title, dtm.title) >= 0;}

  // Required for Qsort
  bool   operator<= (Dtm& dtm)      {return _tcsicmp(title, dtm.title) <= 0;}
  bool   operator>  (Dtm& dtm)      {return _tcsicmp(title, dtm.title) >  0;}

  // Required for Binary Search                                         // Also required for linear search
  bool   operator== (const String& title);     // {return _tcsicmp(this->title, title) == 0;}
  bool   operator<  (const String& title);     // {return _tcsicmp(this->title, title) <  0;}
  bool   operator>  (const String& title);     // {return _tcsicmp(this->title, title) >  0;}

  bool   operator== (Dtm& dtm)  {return _tcsicmp(title, dtm.title) == 0;}

  // Needed for Regular Expression Searches

  bool     operator== (RegExpr& re) {return re.match(title);}

private:

  bool   getLexTok(CSVLex& lex, String& s);

  void   copy(Dtm& dtm);
  };



typedef DatumPtrT<Dtm, String> DtmP;
class StoreP;
typedef IterT<StoreP, Dtm> StorePIter;


class StoreP {

int                               ttlLng;
ExpandableP<Dtm, String, DtmP, 2> data;

public:

  StoreP() { }
 ~StoreP() { }

  void load(Archive& ar);
  void loadNext(Archive& ar);
  void loadAppend(Archive& ar);
  void loadSorted(Archive& ar);

  void save(Archive& ar);

  void sort() {qsort(&data[0], &data[data.end()-1]);}

  void display();

  Dtm* bSearch(String& key) {return data.bSearch(key);}
  Dtm* find(   String& key) {return data.find(key);}

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  Dtm* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}       // note: data[i].p

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename StorePIter;
  };


extern StoreP storeP;
