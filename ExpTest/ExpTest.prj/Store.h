// Store Example


#pragma once
#include "Archive.h"
#include "CSVLex.h"
#include "CSVOut.h"
#include "Expandable.h"
#include "IterT.h"
#include "qsort.h"
#include "RegExpr.h"


class Datum {

public:

public:
String title;
String channel;
Date   date;
String comment;
bool   bobPresent;
bool   maureenPresent;

  Datum() : bobPresent(false), maureenPresent(false) { }
  Datum(Datum& dtm) {copy(dtm);}

  bool load(CSVLex& lex);
  void save(CSVOut& csv);

  void display(int tab);

  Datum& operator=(Datum& dtm) {copy(dtm); return *this;}

  // Required for Insertion Sort, i.e. data = dtm;           // _tcsicmp
  bool operator>= (Datum& dtm) {return _tcsicmp(title, dtm.title) >= 0;}

  // Required for Qsort
  bool operator<= (Datum& dtm)      {return _tcsicmp(title, dtm.title) <= 0;}
  bool operator>  (Datum& dtm)      {return _tcsicmp(title, dtm.title) >  0;}

  // Required for Binary Search                                         // Also required for linear search
  bool     operator== (const String& ttl);   // {return _tcsicmp(this->title, title) == 0;}
  bool     operator<  (const String& ttl);   // {return _tcsicmp(this->title, title) <  0;}
  bool     operator>  (const String& ttl);   // {return _tcsicmp(this->title, title) >  0;}

  bool     operator== (Datum& dtm)  {return _tcsicmp(title, dtm.title) == 0;}

  // Needed for Regular Expression Searches

  bool     operator== (RegExpr& re) {return re.match(title);}

private:

  bool getLexTok(CSVLex& lex, String& s);

  void copy(Datum& dtm);
  };


class Store;
typedef IterT<Store, Datum> StoreIter;


class Store {

int                  ttlLng;
Expandable<Datum, 2> data;

public:

  Store() { }
 ~Store() { }

  void load(Archive& ar);
  void loadAppend(Archive& ar);
  void loadSorted(Archive& ar);

  void save(Archive& ar);

  void sort() {qsort(&data[0], &data[data.end()-1]);}

  Datum* bSearch(const String& title) {return data.bSearch(title);}
  Datum* find(   const String& title) {return data.find(title);}

  void display();
  void display2();

private:

  int findBrk(String& s, int brk);

  // returns either a pointer to data (or datum) at index i in array or zero

  Datum* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int    nData()      {return data.end();}                       // returns number of data items in array

  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename StoreIter;
  };


extern Store store;
