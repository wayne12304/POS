#ifndef ATOM_H
#define ATOM_H

#include <string>

class Variable;
class Number;

using std::string;

class Atom {
public:
  Atom (string s);
  
  string symbol();
  
  bool match( Atom atom );
  bool match( Number num );
  bool match( Variable &variable );
  
private:
  string _symbol;
};

#endif
