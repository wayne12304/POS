#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
TEST(iterator, first) {
	/*
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());*/
}

// TEST(iterator, nested_iterator) {
//   Number one(1);
//   Variable X("X");
//   Variable Y("Y");
//   Number two(2);
//   Struct t(Atom("t"), { &X, &two });
//   Struct s(Atom("s"), { &one, &t, &Y });
  // StructIterator it(&s);
  // it.first();
  // it.next();
  // Struct *s2 = dynamic_cast<Struct *>(it.currentItem());

  // StructIterator it2(s2);
  // it2.first();
  // ASSERT_EQ("X", it2.currentItem()->symbol());
  // ASSERT_FALSE(it2.isDone());
  // it2.next();
  // ASSERT_EQ("2", it2.currentItem()->symbol());
  // ASSERT_FALSE(it2.isDone());
  // it2.next();
  // ASSERT_TRUE(it2.isDone());
// }

TEST(iterator, firstList) {
	/*
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    ListIterator it(&l);
    Iterator* itList = &it;
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());*/
}

TEST(iterator, NullIterator){
/*
  Number one(1);
  NullIterator nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());*/
}

TEST(iterator, BFS_First) {
	Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two, &one, &Y });

    Iterator<Term *> *it = t.createBFSIterator();
    it->first();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, BFS_Second) {
	Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Atom tom("tom");
    Number three(3);
    Variable Z("Z");
    Struct t1(Atom("t1"), { &X, &two });
	Struct t2(Atom("t2"), { &Y, &one });
	List l1({ &X, &Y, &Z});
	List l2({ &one, &two, &three});
	List l3;
	List l4({ &l2, &t2, &l3 });
	Struct s(Atom("s"), { &t1, &tom, &l4, &l1 }); 
	
	Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("t1(X, 2)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("tom", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[[1, 2, 3], t2(Y, 1), []]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[X, Y, Z]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[1, 2, 3]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t2(Y, 1)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Z", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, DFS_First) {
	Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two, &one, &Y });

    Iterator<Term *> *it = t.createDFSIterator();
    it->first();
    
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, DFS_Second) {
	Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Atom tom("tom");
    Number three(3);
    Variable Z("Z");
    Struct t1(Atom("t1"), { &X, &two });
	Struct t2(Atom("t2"), { &Y, &one });
	List l1({ &X, &Y, &Z});
	List l2({ &one, &two, &three});
	List l3;
	List l4({ &l2, &t2, &l3 });
	Struct s(Atom("s"), { &t1, &tom, &l4, &l1 }); 
	
	Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("t1(X, 2)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    
    ASSERT_EQ("tom", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    
    ASSERT_EQ("[[1, 2, 3], t2(Y, 1), []]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[1, 2, 3]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    
    ASSERT_EQ("t2(Y, 1)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    
    ASSERT_EQ("[]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    
    ASSERT_EQ("[X, Y, Z]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Z", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();

    ASSERT_TRUE(it->isDone());
}


#endif
