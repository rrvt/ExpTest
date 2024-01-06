// Store Example


#include "pch.h"
#include "Store.h"
#include "FileIO.h"
#include "NotePad.h"


Store store;


// Use data[i] to reference Datum to load.  Since it fails the last index, it is deleted

void Store::load(Archive& ar) {
CSVLex lex(ar);
int    i;

  data.clear();

  for (i = 0; data[i].load(lex) == true; i++) continue;

  data.del(i);
  }


// Load a local copy of Datum, then append it into the data with the "+=" operator

void Store::loadAppend(Archive& ar) {
CSVLex lex(ar);
Datum  dtm;

  data.clear();

  while (dtm.load(lex)) data += dtm;
  }


// Load a local copy of Datum, then insertion sort into the data with the "=" operator

void Store::loadSorted(Archive& ar) {
CSVLex lex(ar);
Datum  dtm;

  data.clear();

  while (dtm.load(lex)) data = dtm;
  }


// Load one Dtm object and succeed, else fail

bool Datum::load(CSVLex& lex) {
String s;

  if (!getLexTok(lex, title)) return false;
  if (!getLexTok(lex, channel)) return false;
  if (!getLexTok(lex, s)) return false;        date << s;
  if (!getLexTok(lex, comment)) return false;
  if (!getLexTok(lex, s)) return false;        bobPresent     = s == _T("1");
  if (!getLexTok(lex, s)) return false;        maureenPresent = s == _T("1");

  return true;
  }


//enum CSVtokCode {NoToken, WhiteToken, StringToken, CommaToken, EolToken, EOFToken, IllegalToken};

bool Datum::getLexTok(CSVLex& lex, String& s) {
CSVtokCode code  = lex.get_token();    if (code == EOFToken) return false;
CSVtokCode code1 = lex.token1.code;

  if (code == StringToken && (code1 == CommaToken || code1 == EolToken)) {
    s = lex.token.name;  lex.accept_two_tokens(); return true;
    }

  if (code == CommaToken || code == EolToken) {s.clear();  lex.accept_token(); return true;}

  return false;
  }


// Iteratorate over the entire vector, saving each node

void Store::save(Archive& ar) {
CSVOut    csv(ar);
StoreIter iter(*this);
Datum*    dtm;

  for (dtm = iter(); dtm; dtm = iter++) dtm->save(csv);
  }


// CSVOut makes sure that the comma is not confused with a comma in each string, other than that it
// just outputs each string followed by a comma.

void Datum::save(CSVOut& csv) {
  csv << title.trim()   << _T(',');
  csv << channel.trim() << _T(',');
  csv << date           << _T(',');
  csv << comment.trim() << _T(',');
  csv << bobPresent     << _T(',');
  csv << maureenPresent;
  csv << vCrlf;
  }


// Display each object in the vector.  Since the titles are different lengths it finds the longest one
// first, then does the output.

void Store::display() {
StoreIter iter(*this);
Datum*    dtm;

  for (dtm = iter(), ttlLng = 0; dtm; dtm = iter++)
                                        {int lng = dtm->title.length();   if (lng > ttlLng) ttlLng = lng;}
  notePad.clear();

  for (dtm = iter(); dtm; dtm = iter++) {dtm->display(ttlLng);}
  }


// Proportional fonts use less space than fixed width fonts so the tab is reduced

void Datum::display(int tab) {
int x = (tab * 25) / 32;

  notePad << nClrTabs << nSetTab(x) << nSetRTab(x+22) << nSetTab(x+24) << nSetTab(x+30);
  notePad << title << nTab << channel;
  notePad << nTab << date;
  notePad << nTab << (bobPresent ? _T("Bob") : _T("  "));
  notePad << nTab << (maureenPresent ? _T("Maureen") : _T(""));
  notePad << nCrlf;
  }



// Required for Binary Search, "==" also required for linear search
// Comparisons without regard to case

bool Datum::operator== (const String& ttl)
                   {int lng = ((String&)ttl).length();   return _tcsicmp(title.substr(0, lng), ttl) == 0;}


bool Datum::operator<  (const String& ttl)
                   {int lng = ((String&)ttl).length();   return _tcsicmp(title.substr(0, lng), ttl) <  0;}


bool Datum::operator>  (const String& ttl)
                   {int lng = ((String&)ttl).length();   return _tcsicmp(title.substr(0, lng), ttl) >  0;}


void Datum::copy(Datum& d) {
  title          = d.title;
  channel        = d.channel;
  date           = d.date;
  comment        = d.comment;
  bobPresent     = d.bobPresent;
  maureenPresent = d.maureenPresent;
  }

