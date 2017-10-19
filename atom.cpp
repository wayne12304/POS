
#include "atom.h"
#include "term.h"
#include "variable.h"
#include <string>

using std::string;

Atom::Atom (string s):_symbol(s) {};

string Atom::symbol() const{
	return _symbol;
} // symbol()

bool Atom::match(Term & term) {
  Variable * ps = dynamic_cast<Variable *> (&term);
  if ( ps ) return true;
  return value() == term.value();
}

