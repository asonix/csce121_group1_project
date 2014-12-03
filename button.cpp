
//button.cpp

#include "button.h"

GoodButton::GoodButton(Point xy, int w, int h, const string& label, Callback cb) : Button(xy, w, h, label, cb) {
  r.move(xy.x, xy.y);
  r.set_width(w);
  r.set_height(h);
  r.set_fill_color(Color(0xe5e5e500));
  t.move(xy.x+w/2-4*label.size(), xy.y+6+h/2);
  t.set_label(label);
}

void GoodButton::attach(Graph_lib::Window& win) {
  Base::attach(win);
  win.attach(r);
  win.attach(t);
}

void GoodButton::show() {
  Base::show();

}
