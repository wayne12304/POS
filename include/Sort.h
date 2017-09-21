#include <list>
#include "Shapes.h"

typedef std::list<Shape *> listShapePtr;

class Sort {

  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {
	  
	  for ( listShapePtr::iterator i = shapeList->begin() ; i != shapeList->end() ; i++ ) {
		  listShapePtr::iterator next = i;
		  next ++; // get next
		  for ( listShapePtr::iterator j = next ; j != shapeList->end() ; j++ ) {
			  if ( (*i)->perimeter() > (*j)->perimeter() ) {
				  std::swap((*i), (*j));
			  } // if
		  } // for
	  } // for
	  
  } // sortByIncreasingPerimeter()

  public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
	  sortByIncreasingPerimeter( shapeList ) ; 
	  shapeList->reverse();
  } // sortByDecreasingPerimeter()

  public :static void sortByIncreasingArea(std::list<Shape *> * shapeList) {
	  for ( listShapePtr::iterator i = shapeList->begin() ; i != shapeList->end() ; i++ ) {
		  listShapePtr::iterator next = i;
		  next ++; // get next
		  for ( listShapePtr::iterator j = next ; j != shapeList->end() ; j++ ) {
			  if ( (*i)->area() > (*j)->area() ) {
				  std::swap((*i), (*j));
			  } // if
		  } // for
	  } // for
  } // sortByIncreasingArea()

  public :static void sortByDecreasingArea(std::list<Shape *> * shapeList) {
	  sortByIncreasingPerimeter( shapeList ) ; 
	  shapeList->reverse();
  } // sortByDecreasingArea()
  
  public :static void sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
	  for ( listShapePtr::iterator i = shapeList->begin() ; i != shapeList->end() ; i++ ) {
		  listShapePtr::iterator next = i;
		  next ++; // get next
		  for ( listShapePtr::iterator j = next ; j != shapeList->end() ; j++ ) {
			  if ( (*i)->compactness() > (*j)->compactness() ) {
				  std::swap((*i), (*j));
			  } // if
		  } // for
	  } // for
  } // sortByIncreasingCompactness()
  
};
