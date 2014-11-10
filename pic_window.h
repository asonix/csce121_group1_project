
// pic_window.h

#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "picture.h"
#include "archive.h"

using namespace Graph_lib;

#ifndef PIC_WINDOW
#define PIC_WINDOW

class Pic_window : Graph_lib :: Window
{
	public:
		vector<Picture> pics;
			
		Pic_window(Point xy,int w,int h,const string& title);
		
		// --- Navigation -------------------------------------------------- //
		
		Button quit_button;
		static void cb_quit(Address,Address);
		void quit();
		
		Button back1_button;
		static void cb_back1(Address,Address);
		void back1();
		
		Button back2_button;
		static void cb_back2(Address,Address);
		void back2();
		
		// --- Home Screen ------------------------------------------------- //
		
		
		
		Button gallery_button;
		static void cb_gallery(Address,Address);
		void gallery();	
		
		Button add_button;
		static void cb_add(Address,Address);
		void add();	
		
		// --- Gallery Screen ---------------------------------------------- //
		
		Button right_button;
		static void cb_right(Address,Address);
		void right();
		
		Button left_button;
		static void cb_left(Address,Address);
		void left();
		
		// --- Add Screen -------------------------------------------------- //
		
		Button download_button;
		static void cb_download(Address, Address);
		void download();
		
		Button addpic_button;
		static void cb_addpic(Address, Address);
		void addpic();
		
		In_box url,url_filename,url_tags,path,path_filename,path_tags;
		
};

#endif