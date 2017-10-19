#include "variable.h"
#include "term.h"
#include <string>

using std::string;

Variable::Variable( string s ): _symbol(s) {
    *_value = s;
}

string Variable::symbol() const { 
	return _symbol; 
} // symbol()

string Variable::value() const { 
	return *_value; 
} // value()

bool Variable::assignable() {
	return _assignable;
} // assignable()

bool Variable::match( Term &term ) {
    bool ret = _assignable;
    if ( _assignable ) {
        Variable *ps = dynamic_cast<Variable *> (&term);
        if ( ps ) {
            if ( ps->_assignable )
                ps->_value = _value;
            else
                _value = ps->_value;
        } // if
        else {
            *_value = term.symbol();
            _assignable = false;
        }  // else      
    } // if
    else {
        return *_value == term.value();
    } // else
} // match()
