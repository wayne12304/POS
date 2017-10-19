#include "term.h"

#include <string>
#include <iostream>

using std::string;
using namespace std;

Term::Term () {};

string Term::value() const {
  return symbol();
};

bool Term::match(Term & term) {
  return value() == term.value();
}
