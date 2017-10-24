#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
using std::vector;
using std::string;

class List : public Term {
public:
  string symbol() const;
  string value() const;
  bool match(Term & term);
  
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const;
  List * tail() const;
  
  bool inList(Term &term) const;
  bool isEmpty() const;
  int size() const;

private:
  vector<Term *> _elements;

};

#endif
