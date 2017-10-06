#include "include/number.h"
#include "include/variable.h"
#include "include/atom.h"
#include <string>

using std::string;


Number::Number( int value ):_value(value), _symbol( std::to_string( _value ) ){};
//Number::Number( int value, string symbol ): _value(value), _symbol(symbol) {};
	
string Number::value() {
	return std::to_string( _value );
} // value()
    
string Number::symbol() {
	return _symbol;
} // symbol()

bool Number::match( Number num ) {
	return num.value() == value();
} // match()
	
bool Number::match( Atom atom ) {
	return false;
} // match()

bool Number::match( Variable variable ) {
	if ( variable.value() == value() )
		return true;
	bool ret = variable.assignable();
    if ( variable.assignable() ) {
        variable.setValue( value() );
    } // if 
        
    return ret;
} // match()
	

