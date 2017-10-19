#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct :public Term {
public:
string *_value;
  Struct(Atom const & name, std::vector<Term *> args);
  
  Term * args(int index);

  Atom const & name();
  
  string symbol() const;
  string value() const;
  
  string *getValue();
  
  bool match(Term &term) ;
  
private:
  Atom _name;
  std::vector<Term *> _args;
  //string *_value;
};

#endif
