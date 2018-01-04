#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include "variable.h"

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getResult() =0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }
  
  string getResult() {
	  string result = "";
	  if (evaluate()) {
		  if (_left->symbol() == _right->symbol())
			result = "true";
		  else {
			  Variable * lvp = dynamic_cast<Variable *>(_left);
			  Variable * rvp = dynamic_cast<Variable *>(_right);
			  if (rvp && !lvp)
				result = _right->symbol() + " = " + _left->value();
			  else
			    result = _left->symbol() + " = " + _right->value();
		  }
	  }
	  else {
		  result = "false";
	  }
	  
	  return result;
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }
  
  string getResult() {
	  string result = "";
	  if (evaluate()) {
		  string lResult = _left->getResult();
		  string rResult = _right->getResult();
		  if (lResult.find(rResult) != string::npos)
		      result = lResult;
		  else if (rResult.find(lResult) != string::npos)
		      result = rResult;
		  //else if (lResult == "false" || rResult == "false")
			//  result = "false";
		  else if (lResult == "true")
			  result = rResult;
		  else if (rResult == "true")
			  result = lResult;
		  else
			  result = lResult + ", " + rResult;
	  }
	  else {
		  result = "false";
	  }
	  return result;
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }
  
  string getResult() {
	  string result = "";
	  if (evaluate()) {
		  string lResult = _left->getResult();
		  string rResult = _right->getResult();
		  /*
		  if (lResult.find(rResult) != string::npos)
		      result = lResult;
		  else if (rResult.find(lResult) != string::npos)
		      result = rResult;*/
		  //else if (lResult == "false" || rResult == "false")
			//  result = "false";
		  if (lResult == "false")
			  result = rResult;
		  else if (rResult == "false")
			  result = lResult;
		  else
			  result = lResult + "; " + rResult;
	  }
	  else {
		  result = "false";
	  }
	  
	  return result;
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
