#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "term.h"

using std::string;

class Variable : public Term {
  public:
    string const _symbol;
    Variable(string s);
    string symbol() const;
    string value() const;
    
    bool match(Term &term);
    bool assignable();

  private:
    string *_value = new string;
    bool _assignable = true;
    
};

#endif
