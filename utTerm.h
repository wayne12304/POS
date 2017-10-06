#ifndef UTTERM_H
#define UTTERM_H

#include "include/variable.h"
#include "include/atom.h"
#include "include/number.h"

//test Number.value()
TEST (Number, ctor) {
	Number num( 100 );
	ASSERT_EQ( "100", num.value() );
}
//test Number.symbol()
TEST (Number, symbol) {
	Number num( 100 );
	ASSERT_EQ( "100", num.symbol() );
}
//?- 25 = 25.
// true.
TEST (Number, matchSuccess) {
	Number num1( 25 );
	Number num2( 25 );
	ASSERT_TRUE( num1.match(num2) );
}
//?- 25 = 0.
// false.
TEST (Number, matchFailureDiffValue) {
	Number num1( 25 );
	Number num2( 0 );
	ASSERT_FALSE( num1.match(num2) );
}
//?- 25 = tom.
// false.
TEST (Number, matchFailureDiffConstant) {
	Number num( 25 );
    Atom tom( "tom" );
    ASSERT_FALSE( num.match(tom) );
}
//?- 25 = X.
// true.
TEST (Number, matchSuccessToVar) {
    Number num( 25 );
    Variable X( "X" );
    ASSERT_TRUE( num.match(X) );
}

//?- tom = 25.
// false.
TEST (Atom, matchFailureDiffConstant) {
	Number num( 25 );
    Atom tom( "tom" );
    ASSERT_FALSE( tom.match(num) );
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Variable X( "X" );
    Atom tom( "tom" );
    tom.match(X);
    ASSERT_EQ( X.value(), tom.symbol() );

}

// ?- X = tom, tom = X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Variable X( "X" );
    Atom tom( "tom" );
    tom.match(X);
    X.match(tom);
    ASSERT_EQ( "tom", X.value() );
    
}

// ?- X = jerry, tom = X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Variable X( "X" );
    Atom tom( "tom" );
    Atom jerry( "jerry" );
    X.match( jerry );
    ASSERT_FALSE( tom.match( X ) );
}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
	Variable X( "X" );
	Number num( 5 );
	X.match( num );
	ASSERT_EQ( "5", X.value() );
}

// ?- X = 25, X = 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
	Variable X( "X" );
	Number num25( 25 );
	Number num100( 100 );
	X.match( num25 );
	ASSERT_FALSE( X.match( num100 ) );
	
}

// ?- X = tom, X = 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
	Variable X( "X" );
	Number num25( 25 );
	Atom tom( "tom" );
	X.match( tom );
	ASSERT_FALSE( X.match( num25 ) );
}
//?- tom = X, 25 = X.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
	Variable X( "X" );
	Number num25( 25 );
	Atom tom( "tom" );
	tom.match( X );
	ASSERT_FALSE( num25.match( X ) );
}
//?- X = tom, X = tom.
// true.
TEST(Variable, reAssignTheSameAtom){
	Variable X( "X" );
	Atom tom( "tom" );
	X.match( tom );
	ASSERT_TRUE( X.match( tom ) );
}
#endif
