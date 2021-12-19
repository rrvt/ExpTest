// Store Example


#pragma once
#include "Expandable.h"
#include "IterT.h"
#include "qsort.h"


class Datum {

public:

ulong  key;                         // A 5 digit key created to be unique
String line;                        // Line from the file

  Datum() : key(0) { }
  Datum(Datum& dtm) {copy(dtm);}

  Datum& operator=(Datum& dtm) {copy(dtm); return *this;}

  // Required for Insertion Sort, i.e. data = dtm;
  bool operator>= (Datum& dtm) {return key >= dtm.key;}
  bool operator== (Datum& dtm) {return key == dtm.key;}

  // Required for Qsort
  bool operator>  (Datum& dtm) {return key >  dtm.key;}
  bool operator<= (Datum& dtm) {return key <= dtm.key;}

  // Required for Binary Search
  bool     operator== (ulong key) {return this->key == key;}
  bool     operator<  (ulong key) {return this->key <  key;}
  bool     operator>  (ulong key) {return this->key >  key;}

private:

  void copy(Datum& dtm) {key = dtm.key;  line = dtm.line;}
  };


class Store;
typedef IterT<Store, Datum> StoreIter;


class Store {

String               path;
Expandable<Datum, 2> data;

public:

  Store() { }
 ~Store() { }

  void load(TCchar* filePath);
  void appendDatum(TCchar* filePath);
  void loadSorted(TCchar* filePath);

  // allocate a record, copy datum into it and insert into data, succeeds if insertion  performed

  bool insert(int x, Datum& datum) {return data(x, datum);}
  bool insert(int x, Datum* datum) {return data(x, *datum);}

  bool del(int x) {return data.del(x);}   // delete record at index x, succeeds if deletion performed

  void sort() {qsort(&data[0], &data[data.end()-1]);}

  Datum* bSearch(int key) {return data.bSearch(key);}
  Datum* find( ulong key) {return data.find(key);}

  void display();

  int   nData()      {return data.end();}                       // returns number of data items in array

private:

  // returns either a pointer to datum at index i in array or zero

  Datum* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename StoreIter;
  };


extern Store store;
