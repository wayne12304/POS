#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List list;
  ASSERT_EQ("[]", list.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
  Number num1(8128);
  Number num2(496);
  vector<Term*> v = {&num2, &num1};
  List list(v);
  ASSERT_EQ("[496, 8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom terence_tao("terence_tao");
	Atom alan_mathison_turing("alan_mathison_turing");
	vector<Term*> v = {&terence_tao, &alan_mathison_turing};
	List list(v);
	ASSERT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X");
	Variable Y("Y");
	vector<Term*> v = {&X, &Y};
	List list(v);
	ASSERT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Atom tom("tom");
	Variable X("X");
	Number num(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&num, &X, &terence_tao};
	List list(v);
	ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Number num1(8128);
	Variable X("X");
	Number num2(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&num2, &X, &terence_tao};
	List list(v);
	ASSERT_FALSE(num1.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Atom name("s");
	Variable X("X");
	Number num(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&X};
	Struct s(name, v);
	v.clear();
	v = {&num, &X, &terence_tao};
	List list(v);
	
	ASSERT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Variable Y("Y");
	Variable X("X");
	Number num(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&num, &X, &terence_tao};
	List list(v);
	ASSERT_TRUE(Y.match(list));
	ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Variable X("X");
	Number num(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&num, &X, &terence_tao};
	List list(v);
	ASSERT_FALSE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Variable X("X");
	Number num(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&num, &X, &terence_tao};
	List list1(v);
	List list2(v);
	
	ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Variable X("X");
	Variable Y("Y");
	Number num(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&num, &X, &terence_tao};
	List list1(v);
	v.clear();
	v = {&num, &Y, &terence_tao};
	List list2(v);
	
	ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Variable X("X");
	Number num1(496);
	Number num2(8128);
	Atom terence_tao("terence_tao");
	vector<Term*> v = {&num1, &X, &terence_tao};
	List list1(v);
	v.clear();
	v = {&num1, &num2, &terence_tao};
	List list2(v);

	ASSERT_TRUE(list1.match(list2));
	ASSERT_EQ("8128", X.value());
	ASSERT_EQ("X", X.symbol());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
	Variable X("X");
	Variable Y("Y");
	Number num1(496);
	Atom terence_tao("terence_tao");
	Atom alan_mathison_turing("alan_mathison_turing");
	vector<Term*> v = {&num1, &X, &terence_tao};
	List list1(v);
	
	ASSERT_TRUE(Y.match(list1));
	ASSERT_TRUE(X.match(alan_mathison_turing));

	ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
	ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", list1.value());
	ASSERT_EQ("alan_mathison_turing", X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f};
  List l1(args);
  args.clear();
  args = {&l1, &s, &t};
  List l2(args);
  
  EXPECT_EQ(string("[first]"), l2.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List l;
  try {
	  l.head();
  } catch( string err ) {
	  EXPECT_EQ(string("Accessing head in an empty list"), err);
  }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List l;
  try {
	  l.tail();
  } catch( string err ) {
	  EXPECT_EQ(string("Accessing tail in an empty list"), err);
  }
}

TEST (List, varyVar) {
	Variable X("X");
	Variable Y("Y");
	Variable Z("Z");
	
	Variable A("A");
	Variable B("B");
	Variable C("C");
	
	ASSERT_TRUE(X.match(Y));
	ASSERT_TRUE(X.match(Z));
	
	ASSERT_TRUE(A.match(C));
	ASSERT_TRUE(C.match(B));
	
	ASSERT_TRUE(A.match(B));
	ASSERT_TRUE(X.match(A));
	Atom name("s");
	ASSERT_TRUE(B.match(name));
	ASSERT_EQ("s", X.value());
	ASSERT_EQ("s", Y.value());
	ASSERT_EQ("s", Z.value());
	ASSERT_EQ("s", A.value());
	ASSERT_EQ("s", B.value());
	ASSERT_EQ("s", C.value());
	Atom name1("a");
	ASSERT_FALSE(A.match(name1));
}




#endif
