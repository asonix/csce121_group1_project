
#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"
#include "pic_window.h"

int main()
try {
	if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ",
		  	   H112);
	Pic_window win1(Point(100,100),1000,800,"AggieSnap");
	return gui_main();
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}