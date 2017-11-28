#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC) {
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '[') {
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
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }
  
  void matchings() {
	  _tree = createTree();
	  _varTable.clear();
	  /*
	  Node* root = nullptr;
	  Node* temp = createEQTree();
	  root = temp;
	  
	  do {
		  
		  if ( _scanner.currentChar() == '.' )
			break;
		  else if ( _scanner.currentChar() == ',') {
			  
			  
			  createTerm();
			  temp = new Node(COMMA);
			  temp->left = root;
			  root = temp;
			  temp = createEQTree();
			  root->right = temp;
		  } // if
	  } while( true ) ;
	  
	  _tree = root;
	  */
  }
  
  Node * createTree() {
	  Node* n = createEQTree();
	  Node* r = nullptr;

	  if ( _scanner.currentChar() == '.' ) {
		  r = n ;
		return r;
	  } // if
	  else if ( _scanner.currentChar() == ',') {
		  createTerm();
		  r = new Node(COMMA);
		  r->left = n;
		  Node * temp = createTree();
		  if ( temp->payload == SEMICOLON ) {
			r->right = temp->left;
			temp->left = r;
			r = temp;
		  } // if
		  else 
		    r->right = temp;
		  return r;
	  } // if
	  else if ( _scanner.currentChar() == ';') {
		  createTerm();
		  _varTable.clear();
		  r = new Node(SEMICOLON);
		  r->left = n;
		  Node * temp = createTree();
		  r->right = temp;
		  return r;
	  } // if
	  else {
		  throw string("unexpected token");
	  }
  } 
  
  Node* createEQTree() {
	  Term * term = createTerm();
	  Term * t = findTerm( term );
	  if ( t != nullptr ) 
		term = t;
	  _terms.push_back(term);
	  Node * l = new Node(TERM, term, nullptr, nullptr);
	  
	  Term * eq = createTerm();
	  if ( eq->symbol() != "=" )
	    throw string("unexpected token");
	  Node * root = new Node(EQUALITY);
	  
	  term = createTerm();
	  t = findTerm( term );
	  if ( t != nullptr ) 
		term = t;
	  _terms.push_back(term);
	  Node * r = new Node(TERM, term, nullptr, nullptr);
	  
	  root->left = l;
	  root->right = r;
	  return root;
  } 
  
  Node * expressionTree() {
	  return _tree;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    
    if(term!=nullptr)
    {
	  Term * t = findTerm( term );
	  if ( t != nullptr ) 
		  term = t;
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        //_terms.push_back(createTerm());
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
  Node * _tree;
};
#endif
