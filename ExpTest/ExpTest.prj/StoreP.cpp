// ExpandableP Store Example


#include "pch.h"
#include "StoreP.h"
#include "FileIO.h"
#include "NotePad.h"


StoreP storeP;


// Allocate a Dtm, load the object allocated and copy address of dtm into vector indexed by i.
// Deallocate the last object since the load into it failed.

void StoreP::load(Archive& ar) {
CSVLex lex(ar);
Dtm*   dtm;
int    i;

  data.clear();

  for (i = 0, dtm = data.allocate(); dtm->load(lex); i++, dtm = data.allocate()) data[i].p = dtm;
  data.deallocate(dtm);
  }


// Copy loaded dtm object to the next entry in data at the end of the vector

void StoreP::loadNext(Archive& ar) {
CSVLex lex(ar);
Dtm    dtm;

  data.clear();

  while (dtm.load(lex)) data.nextData() = dtm;
  }


// Allocate a Dtm, load the object allocated and append ("+=" operator) the object to the vector.
// Deallocate the last object since the load into it failed.

void StoreP::loadAppend(Archive& ar) {
CSVLex lex(ar);
Dtm*   dtm;

  data.clear();

  for (dtm = data.allocate(); dtm->load(lex); dtm = data.allocate()) data += dtm;
  data.deallocate(dtm);
  }


// Allocate a Dtm, load the object allocated and insertion sort ("=" operator) the object to the vector.
// Deallocate the last object since the load into it failed.

void StoreP::loadSorted(Archive& ar) {
CSVLex lex(ar);
Dtm*   dtm;

  data.clear();

  for (dtm = data.allocate(); dtm->load(lex); dtm = data.allocate()) data = dtm;
  data.deallocate(dtm);
  }


// Load one Dtm object and succeed, else fail

bool Dtm::load(CSVLex& lex) {
String s;

  if (!getLexTok(lex, title)) return false;
  if (!getLexTok(lex, channel)) return false;
  if (!getLexTok(lex, s)) return false;        date << s;
  if (!getLexTok(lex, comment)) return false;
  if (!getLexTok(lex, s)) return false;        bobPresent     = s == _T("1");
  if (!getLexTok(lex, s)) return false;        maureenPresent = s == _T("1");

  return true;
  }


// Returns one token bounded by a comma or end of line
//enum CSVtokCode {NoToken, WhiteToken, StringToken, CommaToken, EolToken, EOFToken, IllegalToken};

bool Dtm::getLexTok(CSVLex& lex, String& s) {
CSVtokCode code  = lex.get_token();    if (code == EOFToken) return false;
CSVtokCode code1 = lex.token1.code;

  if (code == StringToken && (code1 == CommaToken || code1 == EolToken)) {
    s = lex.token.name;  lex.accept_two_tokens(); return true;
    }

  if (code == CommaToken || code == EolToken) {s.clear();  lex.accept_token(); return true;}

  return false;
  }


// Iteratorate over the entire vector, saving each node

void StoreP::save(Archive& ar) {
CSVOut     csv(ar);
StorePIter iter(*this);
Dtm*       dtm;

  for (dtm = iter(); dtm; dtm = iter++) dtm->save(csv);
  }


// CSVOut makes sure that the comma is not confused with a comma in each string, other than that it
// just outputs each string followed by a comma.

void Dtm::save(CSVOut& csv) {
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

void StoreP::display() {
StorePIter iter(*this);
Dtm*       dtm;

  for (dtm = iter(), ttlLng = 0; dtm; dtm = iter++)
                                        {int lng = dtm->title.length();   if (lng > ttlLng) ttlLng = lng;}
  notePad.clear();

  for (dtm = iter(); dtm; dtm = iter++) {dtm->display(ttlLng);}
  }


// Proportional fonts use less space than fixed width fonts so the tab is reduced

void Dtm::display(int tab) {
int x = (tab * 25) / 32;

  notePad << nClrTabs << nSetTab(x) << nSetTab(x+12) << nSetTab(x+24) << nSetTab(x+30);
  notePad << title << nTab << channel;
  notePad << nTab  << date;
  notePad << nTab  << (bobPresent     ? _T("Bob")     : _T("  "));
  notePad << nTab  << (maureenPresent ? _T("Maureen") : _T(""));
  notePad << nCrlf;
  }


// Required for Binary Search, "==" also required for linear search
// Comparisons without regard to case

bool Dtm::operator== (const String& ttl)
                   {int lng = ((String&)ttl).length();   return _tcsicmp(title.substr(0, lng), ttl) == 0;}


bool Dtm::operator<  (const String& ttl)
                   {int lng = ((String&)ttl).length();   return _tcsicmp(title.substr(0, lng), ttl) <  0;}


bool Dtm::operator>  (const String& ttl)
                   {int lng = ((String&)ttl).length();   return _tcsicmp(title.substr(0, lng), ttl) >  0;}


void Dtm::copy(Dtm& d) {
  title          = d.title;
  channel        = d.channel;
  date           = d.date;
  comment        = d.comment;
  bobPresent     = d.bobPresent;
  maureenPresent = d.maureenPresent;
  }

