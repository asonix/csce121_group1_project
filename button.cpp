#include "button.h"

GoodButton::GoodButton(Point xy, int w, int h, const string& label, Callback cb) : Button(xy, w, h, label, cb) {
  r.move(xy.x, xy.y);
  r.set_width(w);
  r.set_height(h);
}

void GoodButton::attach(Graph_lib::Window& win) {
  Base::attach(win);
  win.attach(r);
}

