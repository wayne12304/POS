#include "list.h"

#include <vector>
using std::vector;
using std::string;

string List::symbol() const {
	if ( _elements.empty() ) return "[]";
	string ret = "[";
    vector<Term *>::const_iterator it = _elements.begin();
    for (; it != _elements.end()-1; ++it)
      ret += (*it)->symbol()+", ";
    ret  += (*it)->symbol()+"]";
    return ret;
}

string List::value() const {
	if ( _elements.empty() ) return "[]";
	string ret = "[";
    vector<Term *>::const_iterator it = _elements.begin();
    for (; it != _elements.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+"]";
    return ret;
}

bool List::match(Term & term) {
	List * ps = dynamic_cast<List *>(&term);
	if ( ps ) {
		if ( _elements.size() != ps->size() )
			return false;
		if ( _elements.empty() )
			return true;
		if ( head()->match(*(ps->head())) )
			return tail()->match(*(ps->tail()));
		else 
			return false;
	} // if
	else {
		return term.match(*this);
	} // else
}

bool List::isEmpty() const {
	return _elements.empty();
}

int List::size() const {
	return _elements.size();
}

Term * List::head() const {
	if ( _elements.empty() )
		throw string( "Accessing head in an empty list" );
	return _elements.front();
}

List * List::tail() const {
	if ( _elements.empty() )
		throw string( "Accessing tail in an empty list" );
	vector<Term *> v;
	v.assign(++_elements.begin(), _elements.end());
	List *lptr = new List(v);
	return lptr;
}

bool List::inList(Term &term) const {
	vector<Term *>::const_iterator it = _elements.begin();
    for (; it != _elements.end()-1; ++it) {
		if ( (*it) == &term )
			return true;
	} // for
		
	return false;
}
