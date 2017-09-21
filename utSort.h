#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

vertex v1 = {1, 4};
vertex v2 = {2, 1};
vertex v3 = {4, 3};

typedef std::list<Shape *> listShapePtr;

Rectangle gRectangle( 2, 5, 8, 6 );
Circle gCircle( 3, 8, 6 );
Triangle gTriangle( v1, v2, v3 );


TEST (Sort, sortByIncreasingPerimeter) {
	ASSERT_EQ(6,6);
	
	/*
	std::vector<Shape *> v;
	v.push_back(&gRectangle);*/
	listShapePtr l;
	l.push_back(&gRectangle);
	l.push_back(&gCircle);
	l.push_back(&gTriangle);
    
    Sort sort;
    sort.sortByIncreasingPerimeter( &l );
    /*
    std::string * ansSet = new std::string[5];
    ansSet[0] = "9.15298";
    ansSet[1] = "28";
    ansSet[2] = "37.6991";
    */
    std::vector<Shape *> ans;
    ans.push_back(&gTriangle);
    ans.push_back(&gRectangle);
    ans.push_back(&gCircle);
    
    int i = 0 ;
    for ( listShapePtr::iterator curIt = l.begin() ; curIt != l.end() ; curIt++ ) {
	  // std::stringstream ss;
	  // ss << (*curIt)->perimeter();
	  ASSERT_EQ( ans[i], *curIt );
	  i ++ ;
    } // for
}

TEST (Sort, sortByDecreasingPerimeter) {
	listShapePtr l;
	l.push_back(&gRectangle);
	l.push_back(&gCircle);
	l.push_back(&gTriangle);
    
    Sort sort;
    sort.sortByDecreasingPerimeter( &l );
    
    std::vector<Shape *> ans;
    ans.push_back(&gCircle);
    ans.push_back(&gRectangle);
    ans.push_back(&gTriangle);
    
    int i = 0 ;
    for ( listShapePtr::iterator curIt = l.begin() ; curIt != l.end() ; curIt++ ) {
	  ASSERT_EQ( ans[i], *curIt );
	  i ++ ;
    } // for

}

TEST (Sort, sortByIncreasingArea) {
	listShapePtr l;
	l.push_back(&gRectangle);
	l.push_back(&gCircle);
	l.push_back(&gTriangle);
    
    Sort sort;
    sort.sortByIncreasingArea( &l );
    
    std::vector<Shape *> ans;
    ans.push_back(&gTriangle);
    ans.push_back(&gRectangle);
    ans.push_back(&gCircle);
    
    int i = 0 ;
    for ( listShapePtr::iterator curIt = l.begin() ; curIt != l.end() ; curIt++ ) {
	  ASSERT_EQ( ans[i], *curIt );
	  i ++ ;
    } // for

}

TEST (Sort, sortByDecreasingArea) {
	listShapePtr l;
	l.push_back(&gRectangle);
	l.push_back(&gCircle);
	l.push_back(&gTriangle);
    
    Sort sort;
    sort.sortByDecreasingArea( &l );
    
    std::vector<Shape *> ans;
    ans.push_back(&gCircle);
    ans.push_back(&gRectangle);
    ans.push_back(&gTriangle);
    
    int i = 0 ;
    for ( listShapePtr::iterator curIt = l.begin() ; curIt != l.end() ; curIt++ ) {
	  ASSERT_EQ( ans[i], *curIt );
	  i ++ ;
    } // for

}

TEST (Sort, sortByIncreasingCompactness) {
	
	listShapePtr l;
	l.push_back(&gRectangle);
	l.push_back(&gCircle);
	l.push_back(&gTriangle);
    
    Sort sort;
    sort.sortByIncreasingCompactness( &l );
    
    std::vector<Shape *> ans;
    ans.push_back(&gTriangle);
    ans.push_back(&gRectangle);
    ans.push_back(&gCircle);
    
    int i = 0 ;
    for ( listShapePtr::iterator curIt = l.begin() ; curIt != l.end() ; curIt++ ) {
	  ASSERT_EQ( ans[i], *curIt );
	  i ++ ;
    } // for

}

#endif
