#include "number.h"
#include "variable.h"
#include "atom.h"
#include <string>

using std::string;

Variable::Variable(string s):_symbol(s){};

string Variable::value() { 
	return _value; 
} // value()

void Variable::setValue( string v ) {
	_value = v;
	_assignable = false;
} // setValue()

bool Variable::assignable() {
	return _assignable;
} // assignable()
  
bool Variable::match( Atom atom ) {
	if ( value() == atom.symbol() )
		return true;
	bool ret = _assignable;
		if(_assignable){
			_value = atom.symbol() ;
			_assignable = false;
		} // if
    
    return ret;
} // match()

bool Variable::match( Number num ) {
	if ( value() == num.value() )
		return true;
	bool ret = _assignable;
	if(_assignable){
		_value = num.value() ;
		_assignable = false;
	} // if
    
    return ret;
} // match()

