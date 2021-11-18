// Store Example


#include "stdafx.h"
#include "Store.h"
#include "FileIO.h"
#include "NotePad.h"
#include "Random.h"


Store store;


void Store::load(TCchar* filePath) {
FileIO fil;
int    i;
String line;
Random rand(213);

  path = filePath;   data.clear();

  if (fil.open(path, FileIO::Read)) {
    notePad << filePath << " opened" << nCrlf << nCrlf;

    for (i = 0; fil.read(line); i++) {
      Datum& dtm = data[i];
      ulong  r   = ulong(rand.next() * 1000.0);             // construct a random number

      dtm.key = r * 100 + i; dtm.line = line.trimRight();   // Shift the random number and make unique
      }
    }

  fil.close();
  }


void Store::appendDatum(TCchar* filePath) {
FileIO fil;
String line;
int    i = 0;
Random rand(213);

  path = filePath;   data.clear();

  if (fil.open(path, FileIO::Read)) {
    notePad << filePath << " opened" << nCrlf;

    while (fil.read(line)) {
      Datum dtm;
      ulong r = ulong(rand.next() * 1000.0);

      dtm.key = r * 100 + i++;   dtm.line = line.trimRight();   data += dtm;
      }
    }

  fil.close();
  }


void Store::loadSorted(TCchar* filePath) {
FileIO fil;
String line;
int    i = 0;
Random rand(213);

  path = filePath;   data.clear();

  if (fil.open(path, FileIO::Read)) {
    notePad << filePath << " opened" << nCrlf << nCrlf;

    while (fil.read(line)) {
      Datum dtm;
      ulong r = ulong(rand.next() * 1000.0);

      dtm.key = r * 100 + i++; dtm.line = line.trimRight();   data = dtm;
      }
    }

  fil.close();
  }


void Store::display() {
int    n = data.end();
int    i;
String s;

  notePad << nClrTabs << nSetRTab(3) << nSetRTab(13) << nSetTab(15);

  notePad << _T("No. of Entries in Store: ") << nData() << nCrlf << nCrlf;

  for (i = 0; i < n; i++) {
    Datum& d = data[i];

    notePad << nTab << i << nTab << d.key << nTab << d.line << nCrlf;
    }
  }


#if 0
void Store::display2() {
StoreIter iter(*this);
Datum*    dtm;
String    s;

  notePad << _T("No. of Entries in StoreP: ") << nData() << nCrlf << nCrlf;

  for (dtm = iter(); dtm; dtm = iter++) {
    s.format(_T("%3i/%5i: "), iter.index(),  dtm->key);

    notePad << s << dtm->line;
    }
  }
#endif

