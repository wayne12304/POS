#ifndef NUMBER_H
#define NUMBER_H

#include <string>

class Atom;
class Variable;

using std::string;

class Number {
  public:
	Number( int value );
	//Number( int value, string symbol );
	
	string value();
    string symbol();
	
	bool match( Number num );
	bool match( Atom atom );
	bool match( Variable variable );
     
  private:
	int _value;
	string _symbol;
	
}; // class Number

#endif
