// ExpandableP Store Example


#pragma once
#include "ExpandableP.h"
#include "FileIO.h"
#include "IterT.h"
#include "qsort.h"


class Words {
public:

ushort serial;
bool   thisOne;
String zero;
String one;
String two;
String three;
String rest;

  Words() : serial(0), thisOne(false) { }
  Words(Words& wrds) {copy(wrds);}
 ~Words() {zero.clear(); one.clear(); two.clear(); three.clear(); rest.clear();}

  Words& operator= (Words& wrds) {copy(wrds); return *this;}

  void load(String& line);

  void display();

  // Required for Insertion Sort, i.e. data = dtm;
  bool operator>= (Words& w) {return zero >= w.zero;}
  bool operator== (Words& w) {return zero == w.zero;}

  bool operator<= (Words& w) {return zero <=  w.zero;}
  bool operator>  (Words& w) {return zero >   w.zero;}

  // Required for Binary Search
  bool operator== (TCchar* key) {return zero == key;}
  bool operator<  (TCchar* key) {return zero <  key;}
  bool operator<= (TCchar* key) {return zero <= key;}
  bool operator>  (TCchar* key) {return zero >  key;}

private:

  void copy(Words& wrds);

  bool nextWord(String& s, String& word);
  };


class StoreP;
typedef IterT<StoreP, Words> StorePIter;
typedef DatumPtrT<Words> WordsP;


class StoreP {

ExpandableP<Words, WordsP, 2> data;

public:

  StoreP() { }
 ~StoreP() {data.clear();}

  void clear() {data.clear();}

  void load(TCchar* filePath);
  void loadSorted(TCchar* filePath);


  // allocate a record, copy words into it and insert into data, succeeds when item is inserted,
  // else fails

  bool insert(int x, Words& words) {return data(x, words);}

  // insert an allocated record into data, succeeds when item is inserted, else fails

  bool insert(int x, Words* words) {return data(x, words);}

  void sort() {qsort(&data[0], &data[nData()-1]);}

  // find words based on pointer in data and delete, succeeds when item is deleted, else fails

  bool del(Words* words) {return data.del(words);}

  // delete record at index x, succeeds when item is deleted, else fails

  bool del(int x)        {return data.del(x);}

  void display();

  Words* bSearch(TCchar* key) {return data.bSearch(key);}
  Words* find(   TCchar* key) {return data.find(key);}

  int   nData()      {return data.end();}                       // returns number of data items in array

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  Words* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}       // note: data[i].p

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename StorePIter;
  };


extern StoreP storeP;
