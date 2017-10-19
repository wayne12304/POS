#include "struct.h"
#include "term.h"
#include "variable.h"
#include <string>
#include <iostream>
using std::string;
using namespace std;

Struct::Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) {
	_value = new string;
}

Term * Struct::args(int index) {
  return _args[index];
} // args()

Atom const & Struct::name() {
  return _name;
}
/*
string Struct::symbol() const {
  string ret =_name.symbol() + "(";
  for(int i = 0; i < _args.size()-1 ; i++) {
	Variable * ps = dynamic_cast<Variable *> (_args[i]);
	if ( ps && !ps->assignable() ) {
	  ret += _args[i]-> value() + ", ";
	} // if
	else {
      ret += _args[i]-> symbol() + ", ";
	} // else
  } // for
  
  Variable * ps = dynamic_cast<Variable *> (_args[_args.size()-1]);
  if ( ps && !ps->assignable()) {
    ret += _args[_args.size()-1]-> value() + ")";
  } // if
  else {
    ret += _args[_args.size()-1]-> symbol() + ")";
  } // else
    
  *_value = ret;
  return  ret;
} // symbol()


string * Struct::getValue() {
	*_value = symbol();
	return _value;
}
*/

string Struct::value() const {
	
  string ret =_name.symbol() + "(";
  for(int i = 0; i < _args.size()-1 ; i++) {
	Variable * ps = dynamic_cast<Variable *> (_args[i]);
	if ( ps && ps->assignable() ) {
	  //var no value
	  ret += ps-> symbol() + ", ";
	}
	else {
	  ret += _args[i]-> value() + ", ";
	} // else
  } // for
  
  Variable * ps = dynamic_cast<Variable *> (_args[_args.size()-1]);
  if ( ps && ps->assignable() ) {
	  ret += ps-> symbol() + ")";
  } // if
  else {
	  ret += _args[_args.size()-1]-> value() + ")";
  } // else
  
  
  return  ret;
  
} // symbol()

string Struct::symbol() const {
	
  string ret =_name.symbol() + "(";
  for(int i = 0; i < _args.size()-1 ; i++) {
    ret += _args[i]-> symbol() + ", ";
  } // for
  
  ret += _args[_args.size()-1]-> symbol() + ")";
  *_value = ret;
  return  ret;
  
} // symbol()

bool Struct::match(Term &term) {
  Struct * ps = dynamic_cast<Struct *> (&term);
  if (ps){
    if (!_name.match(ps->_name))
      return false;
    if(_args.size()!= ps->_args.size())
      return false;
    for(int i=0;i<_args.size();i++){
      if(_args[i]->symbol() != ps->_args[i]->symbol())
        return false;
    } // for
     
    return true;
  } // if
    
  return false;
} // match()
