
// pic_window.h

#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "pic_window.h"
#include "picture.h"
#include "archive.h"

using namespace Graph_lib;

// constructor

Pic_window::Pic_window(Point xy,int w,int h,const string& title)
	:Window::Window{xy,w,h,title},
	quit_button{Point(x_max()-70,0),70,20,"Quit",cb_quit},
	back1_button{Point(0,0),70,20,"<-- Back",cb_back1},
	back2_button{Point(0,0),70,20,"<-- Back",cb_back2},
	
	gallery_button{Point(50,(y_max()/2)-100),200,200,"Gallery",cb_gallery},
	add_button{Point(x_max()-250,(y_max()/2)-100),200,200,"Add Picture",cb_add},
	
	left_button{Point(0,(y_max()/2)-10),50,20,"< Left",cb_left},	// View
	right_button{Point(x_max()-50,(y_max()/2)-10),50,20,"Right >",cb_right},
	
	download_button{Point(100,300),80,20,"Download",cb_download},	// Add
	addpic_button{Point(400,300),80,20,"Add Picture",cb_addpic},
	url(Point(80,200),200,20,"URL"),
	url_filename(Point(80,230),200,20,"File Name"),
	url_tags(Point(80,260),200,20,"Tags"),
	path(Point(380,200),200,20,"Full Path"),
	path_filename(Point(380,230),200,20,"File Name"),
	path_tags(Point(380,260),200,20,"Tags")
	{
		Window::attach(quit_button);
		Window::attach(gallery_button);
		Window::attach(add_button);
	}

// --- Navigation ---------------------------------------------------------- //
	
// Quit Button

void Pic_window::cb_quit(Address,Address pw)
{
	reference_to<Pic_window>(pw).quit();
}

void Pic_window::quit()
{
	Window::hide();
}

// Back1 Button

void Pic_window::cb_back1(Address,Address pw)
{
	reference_to<Pic_window>(pw).back1();
}

void Pic_window::back1()
{
	Window::detach(back1_button);
	Window::detach(right_button);
	Window::detach(left_button);
	
	Window::attach(gallery_button);
	Window::attach(add_button);
}

// Back2 Button

void Pic_window::cb_back2(Address,Address pw)
{
	reference_to<Pic_window>(pw).back2();
}

void Pic_window::back2()
{
	Window::detach(back2_button);
	Window::detach(download_button);
	Window::detach(addpic_button);
	
	Window::attach(gallery_button);
	Window::attach(add_button);
	
	Window::detach(url);
	Window::detach(url_filename);
	Window::detach(url_tags);
	Window::detach(path);
	Window::detach(path_filename);
	Window::detach(path_tags);
}

// --- Home Screen --------------------------------------------------------- //

// Gallery
void Pic_window::cb_gallery(Address,Address pw)
{
	reference_to<Pic_window>(pw).gallery();
}

void Pic_window::gallery()
{
	Window::detach(gallery_button);
	Window::detach(add_button);
	Window::attach(back1_button);
	Window::attach(left_button);
	Window::attach(right_button);
}

// Add
void Pic_window::cb_add(Address,Address pw)
{
	reference_to<Pic_window>(pw).add();
}

void Pic_window::add()
{
	Window::detach(gallery_button);
	Window::detach(add_button);
	
	Window::attach(download_button);
	Window::attach(addpic_button);
	Window::attach(back2_button);
	
	Window::attach(url);
	Window::attach(url_filename);
	Window::attach(url_tags);
	Window::attach(path);
	Window::attach(path_filename);
	Window::attach(path_tags);
	
}

// --- Gallery Screen ------------------------------------------------------ //

// Left
void Pic_window::cb_left(Address,Address pw)
{
	reference_to<Pic_window>(pw).left();
}

void Pic_window::left()
{
	// nothing yet
}

// Right
void Pic_window::cb_right(Address,Address pw)
{
	reference_to<Pic_window>(pw).right();
}

void Pic_window::right()
{
	// nothing yet
}

// --- Add Screen ---------------------------------------------------------- //

// Download
void Pic_window::cb_download(Address,Address pw)
{
	reference_to<Pic_window>(pw).download();
}

void Pic_window::download()
{
	string s_url = url.get_string();
	string s_url_filename = url_filename.get_string();
	string s_url_tags = url_tags.get_string();
}

// Add
void Pic_window::cb_addpic(Address,Address pw)
{
	reference_to<Pic_window>(pw).addpic();
}

void Pic_window::addpic()
{
	string s_path = path.get_string();
	string s_path_filename = path_filename.get_string();
	string s_path_tags = path_tags.get_string();
}








