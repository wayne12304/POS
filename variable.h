#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"

class Term;

using std::string;

class Variable : public Term {
public:
  Variable(string s);
  string const _symbol;
  
  string symbol() const;
  string value() const;
  bool assignable();
  
  string gvalue();
  //void setValue( string v );
  
  bool match( Term &term ) override;
  //bool match( Term &term, int a) ;
  // match( Number &num );

private:
  struct Value {
	  string value;
	  bool isEmpty;
  };
  
  string *_value =  NULL;
  bool _assignable = true;
  Term *_term = NULL;
};

#endif
