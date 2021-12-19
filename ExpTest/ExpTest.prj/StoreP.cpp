// ExpandableP Store Example


#include "stdafx.h"
#include "StoreP.h"
#include "FileIO.h"
#include "NotePad.h"


StoreP storeP;


void Words::copy(Words& wrds) {
  serial  = wrds.serial;
  thisOne = wrds.thisOne;
  zero    = wrds.zero;
  one     = wrds.one;
  two     = wrds.two;
  three   = wrds.three;
  rest    = wrds.rest;
  }


bool Words::nextWord(String& s, String& word) {
int pos = s.find(_T(' '));

  if (pos > 0) {word = s.substr(0, pos);  s = s.substr(pos);  s.trim();  return true;}

  if (s.length()) {word = s; s.clear(); return true;}

  return false;
  }




void StoreP::load(TCchar* filePath) {
String path = filePath;
FileIO fil;
String line;
int    i = 0;

  clear();

  if (fil.open(path, FileIO::Read)) {
    notePad << filePath << " opened" << nCrlf << nCrlf;

    while (fil.read(line)) {
      line.trim();   if (!line.isEmpty()) {Words& words = data.nextData();  words.load(line);}
      }
    }

  fil.close();
  }


void StoreP::loadSorted(TCchar* filePath) {
String path = filePath;
FileIO fil;
String line;

  clear();

  if (fil.open(path, FileIO::Read)) {
    notePad << filePath << " opened" << nCrlf << nCrlf;

    while (fil.read(line)) {
      if (!line.trim().isEmpty()) {Words* words = data.allocate();    words->load(line);   data = words;}
      }
    }

  fil.close();
  }


void Words::load(String& line) {
static ushort x = 0;
String s = line;

  serial = ++x;

  s.trim();
  if (!nextWord(s, zero))  return;
  if (!nextWord(s, one))   return;
  if (!nextWord(s, two))   return;
  if (!nextWord(s, three)) return;

  rest = s;

  s.format(_T("%i: %s"), serial, one.str());   one   = s;
  s.format(_T("%i: %s"), serial, two.str());   two   = s;
  s.format(_T("%i: %s"), serial, three.str()); three = s;
  s.format(_T("%i: %s"), serial, rest.str());  rest  = s;
  }


void StoreP::display() {
StorePIter iter(*this);
Words*     words;
String     s;

  notePad << nClrTabs << nSetRTab(5) << nSetTab(7);

  notePad << _T("No. of Entries in StoreP: ") << nData() << nCrlf << nCrlf;

  for (words = iter(); words; words = iter++) {
    s.format(_T("%3i: "), iter.index());

    notePad << s.str();   words->display();   notePad << nCrlf;
    }
  }



void Words::display() {
int x = serial;

  notePad << nTab << x << nTab;
                               if (zero.isEmpty())  return;
  notePad << zero;             if (one.isEmpty())   return;
  notePad << _T(' ') << one;   if (two.isEmpty())   return;
  notePad << _T(' ') << two;   if (three.isEmpty()) return;
  notePad << _T(' ') << three; if (rest.isEmpty())  return;
  notePad << _T(' ') << rest;
  }

