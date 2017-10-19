#include "number.h"
#include "variable.h"
#include "atom.h"
#include <string>

using std::string;


Number::Number( double value ):_value(value), _symbol( std::to_string( _value ) ){};
	
string Number::symbol() const {
	string s = std::to_string( _value );
	int last = s.find_last_not_of('0');
	if ( last == 0 || last == -1 ) ;
	else {
		if ( s.at( last ) == '.' )
			s = s.substr(0, last);
		else
			s = s.substr(0, last+1);
	} // else
	
	return s;
	
} // value()

bool Number::match(Variable & var) {
  return var.match(*this);
} // match()

bool Number::match(Term & term) {
  return value() == term.value();
} // match()

