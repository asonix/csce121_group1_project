
//goodrectangle.h

#include "Graph.h"

#ifndef GOODRECTANGLE
#define goodrectangle

using namespace Graph_lib;

class GoodRectangle : public Shape {
  typedef Shape Base;
  private:
    int h;
    int w;
  public:
    GoodRectangle(Point xy, int ww, int hh);
    GoodRectangle(Point x, Point y);

    void set_width(int ww);
    void set_height(int hh);
    void draw_lines() const;

    int height() const { return h; }
    int width() const { return w; }
};

/* ------------------------------------------------------------------------- //

Structure mimicked from Rectangle definition in Graph.h Graph.h

// ------------------------------------------------------------------------- */
#endif