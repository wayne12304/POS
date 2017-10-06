#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class Atom;
class Number;

using std::string;

class Variable {
public:
  Variable(string s);
  string const _symbol;
  
  string value();
  bool assignable();
  
  void setValue( string v );
  
  bool match( Atom atom );
  bool match( Number num );

private:
  string _value;
  bool _assignable = true;
};

#endif
