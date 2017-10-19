#include "number.h"
#include "variable.h"
#include "atom.h"
#include "struct.h"
#include <iostream>
#include <string>

using std::string;
using namespace std;

Variable::Variable(string s):_symbol(s){
	_value = new string;
};

string Variable::symbol() const {
	return _symbol;
} // symbol()

string Variable::gvalue() { 
	return *_value;
} // value()

bool Variable::assignable() {
	if ( _term == NULL ) return true;
	
	Variable * ps = dynamic_cast<Variable *> (_term);
	if ( ps ) {
		return ps->assignable();
	} // if
	
	return _assignable;
} // assignable()
/*
bool Variable::match( Term &term, int a ) {
	//cout << value() << " " << term.value() << endl;
	// bool ret = _assignable;
	if(_assignable){
		Variable * ps = dynamic_cast<Variable *> (&term);
		if ( ps ) {
			if ( ps->assignable() ) {
				ps->_value = _value;
			} // if
			else {
				_value = ps->_value;
			} // else
		} // if
		else {
			
			Struct * s = dynamic_cast<Struct *> (&term);
			if ( s ) {
				_value = s->getValue();
			} // if
			else {
				*_value = term.value();
			} // else
			
			// *_value = term.symbol();
			_assignable = false;
		} // else
	} // if
	else {
		value() == term.value();
	} // else
   
} // match()
*/

bool Variable::match( Term &term ) {

	if(_assignable){
		//_term = &term;
		Variable * ps = dynamic_cast<Variable *> (&term);
		if ( ps ) {
			if ( ps == this ) return true;
			if ( ps->assignable() ) {
				ps->_term = this;
			} // if
			else {
				_term = ps;
			} // else
		} // if
		
		else {
			_assignable = false;
			if ( _term != NULL ) {
				_term->match(term);
			} // if
			else 
				_term = &term;
		} // else
		
		return true;
	} // if
	else {
		value() == term.value();
	} // else
   
} // match()


string Variable::value() const { 
	if ( _term == NULL )
		return symbol();
	return _term->value();
} // value()
  

