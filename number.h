#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"
#include "variable.h"


class Term;

using std::string;

class Number : public Term {
  public:
	Number( double value );
	
    string symbol() const;
	bool match(Variable & var) ;

	bool match(Term & term);
     
  private:
	double _value;
	string _symbol;
	
}; // class Number

#endif
