#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;
#include <gtest/gtest.h>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>
#include <iostream>

using std::stack;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();
    //std::cout << createTerm()->symbol() << std::endl;
    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
  }

  void restDisjunctionMatch() {
    if (_scanner.peekToken() == ';') {
      createTerm();
      _varTable.clear();
      if (_scanner.peekToken() < NUMBER) {
		string s = "Unexpected ';' before '";
		s += (char) _scanner.nextToken();
		s += "'";
		throw string(s);
	  }
	  
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.peekToken() == ',') {
      createTerm();
      if (_scanner.peekToken() < NUMBER) {
		string s = "Unexpected ',' before '";
		s += (char) _scanner.nextToken();
		s += "'";
		throw string(s);
	  }
	  
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    Term * left = createTerm();
    if (left == nullptr) {
		string s = "unexpected ";
		s += (char) _currentToken;
		throw string(s);
	}
		
    Term * t = findTerm( left );
	  if ( t != nullptr ) 
		  left = t;
    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      Term * t = findTerm( right );
	  if ( t != nullptr ) 
		  right = t;
      _expStack.push(new MatchExp(left, right));
    }
    else if (_currentToken == '.') {
		throw string(left->symbol() + " does never get assignment");
	}
	else if (_currentToken == ';') {
		string s = "Unexpected ';' before '";
		s += (char) _scanner.nextToken();
		s += "'";
		throw string(s);
	}
	else if (_currentToken == ',') {
		string s = "Unexpected ',' before '";
		s += (char) _scanner.nextToken();
		s += "'";
		throw string(s);
	}
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }
  
  string excuteExp() {
	  return getExpressionTree()->getResult() + ".";
  }

private:

  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  FRIEND_TEST(ParserTest, createTerms);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
	  Term * t = findTerm( term );
	  if ( t != nullptr ) 
		  term = t;
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
		term = createTerm();
	    t = findTerm( term );
	    if ( t != nullptr ) 
		  term = t;
        _terms.push_back(term);
      }
    }
  }
  
  Term* findTerm(Term* term) {
	Variable * vp = dynamic_cast<Variable *>(term);
	if ( !vp ) return nullptr;
	for ( int i = 0; i < _varTable.size(); i++ ) {
		if ( _varTable[i]->symbol() == term->symbol() )
			return _varTable[i];
	} // for
	
	_varTable.push_back(term);
	return term;
  } 

  vector<Term *> _terms;
  vector<Term *> _varTable;
  Scanner _scanner;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;
};
#endif
