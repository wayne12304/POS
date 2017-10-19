#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
//class Variable;
//class Number;
class Term;

using std::string;

class Atom : public Term {
public:
  Atom (string s);
  
  string symbol()const;
  bool match(Term & term);

private:
  string _symbol;
};

#endif
