#include "GUI.h"
#include "std_lib_facilities_4.h"
#include "goodrectangle.h"

using namespace Graph_lib;

class GoodButton : public Button {
  typedef Button Base;
  private:
    GoodRectangle r{Point(0,0), 1, 1};
  public:
    GoodButton(Point xy, int w, int h, const string& label, Callback cb);
    void attach(Graph_lib::Window&);
};

