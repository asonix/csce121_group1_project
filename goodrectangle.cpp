
//goodrectangle.cpp

#include "goodrectangle.h"

GoodRectangle::GoodRectangle(Point xy, int ww, int hh) : h(hh), w(ww) {
  add(xy);
  if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
}

GoodRectangle::GoodRectangle(Point x, Point y) : h(y.y-x.y), w(y.x-x.x) {
  add(x);
  if (h<=0 || w<=0) error("Bad rectangle: non-positive width or height");
}

void GoodRectangle::set_width(int ww) {
  w = ww;
}

void GoodRectangle::set_height(int hh) {
  h = hh;
}

void GoodRectangle::draw_lines() const {
  if (fill_color().visibility()) {    // fill
      fl_color(fill_color().as_int());
      fl_rectf(point(0).x,point(0).y,w,h);
      fl_color(color().as_int());    // reset color
  }

  if (color().visibility()) {    // lines on top of fill
      fl_color(color().as_int());
      fl_rect(point(0).x,point(0).y,w,h);
  }
}

/* ------------------------------------------------------------------------- //

Many lines copied from Rectangle definition in Graph.h

// ------------------------------------------------------------------------- */
