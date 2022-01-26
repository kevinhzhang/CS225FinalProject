#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "PointTraversal.h"

#include "ImageTraversal.h"
using namespace std;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
   current = PointTraversal(0,0);
   t = NULL;
   start_ = PointTraversal(0,0);
   tolerance_ = 0;
}
ImageTraversal::Iterator::Iterator(PNG& png, ImageTraversal * trav, PointTraversal & start, double tolerance){
  current = start;
  start_ = start;
  t = trav;
  tolerance_ = tolerance;
  image = png;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!t->empty()){
    
    if(current.x + 1 < image.width()){
      t->add(PointTraversal(current.x + 1, current.y));
    }
    if(current.y + 1 <  image.height()){
      t->add(PointTraversal(current.x, current.y+1));

    }
    if((int) current.x - 1 >= 0){
      t->add(PointTraversal(current.x - 1, current.y));

    }
    if((int) current.y - 1 >= 0){
      t->add(PointTraversal(current.x, current.y - 1));

    }
    
    PointTraversal PointTraversal = current;
     while((t->isVisited(PointTraversal) || calculateDelta(t->convert(start_), t->convert(PointTraversal)) >= tolerance_) && !t->empty()){
      PointTraversal = t->pop();
    } 
    
    t->markVisited(PointTraversal);
    current = PointTraversal;
    
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current PointTraversal in the ImageTraversal.
 */
PointTraversal ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(t->empty());
}




