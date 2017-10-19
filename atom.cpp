
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
  return value() == term.value();
}

bool Atom::match(Variable & var) {
  return var.match(*this);
}
