#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include <stack>
#include <queue>
#include <iostream>

using std::queue;
using std::stack;

template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class NullIterator :public Iterator<T> {
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template <class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template <class T>
class ListIterator :public Iterator<T> {
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};

template <class T>
class BFSIterator :public Iterator<T> {
public:
	BFSIterator(T t): _it(t) {}
	
	void first() {
		while(!_tq.empty()) 
			_tq.pop();
			
		for ( int i = 0 ; i < _it->arity() ; i ++ ) {
			_tq.push(_it->args(i));
		} // for
		
	} 
	
	Term* currentItem() const {
		return _tq.front();
	}
	
	bool isDone() const {
		return _tq.empty();
	}
  
	void next() {
		T t = _tq.front();
		for ( int i = 0 ; i < t->arity() ; i ++ ) {
			_tq.push(t->args(i));
		} // for
		
		_tq.pop();
	}
private:
	T _it;
	queue<T> _tq;
};

template <class T>
class DFSIterator :public Iterator<T> {
public:
	DFSIterator(T t): _it(t) {}
	
	void first() {
		while(!_ts.empty()) 
			_ts.pop();
			
		for ( int i = _it->arity()-1 ; i >= 0 ; i -- ) {
			_ts.push(_it->args(i));
		} // for
		
	} 
	
	Term* currentItem() const {
		return _ts.top();
	}
	
	bool isDone() const {
		return _ts.empty();
	}
  
	void next() {
		T t = _ts.top();
		_ts.pop();
		for ( int i = t->arity()-1 ; i >= 0 ; i -- ) {
			_ts.push(t->args(i));	
		} // for
	}
private:
	T _it;
	stack<T> _ts;
};
#endif
