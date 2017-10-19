
#include "atom.h"
#include "term.h"
#include <string>

using std::string;

Atom::Atom (string s):_symbol(s) {};

string Atom::symbol() const{
	return _symbol;
} // symbol()

/*  
bool Atom::match( Atom atom ) {
	return atom.symbol() == symbol();
} // match() 
  
bool Atom::match( Number num ) {
    return false;
} // match() 
  
bool Atom::match( Variable &variable ) {
	if ( variable.value() == symbol() )
		return true;
	bool ret = variable.assignable();
	if ( variable.assignable() ) {
        variable.setValue( symbol() );
    } // if
        
    return ret;
} // match() 
*/
