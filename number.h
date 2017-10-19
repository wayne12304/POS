#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"

class Term;

using std::string;

class Number : public Term {
  public:
	Number( double value );
	
	//string value() const;
    string symbol() const;
	
	//bool match( Number num );
	//bool match( Atom atom );
	//bool match( Variable &variable );
     
  private:
	double _value;
	string _symbol;
	
}; // class Number

#endif
