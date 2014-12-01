
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

	heading(Point(260,150),"AggieSnap"),
	names(Point(240,775),
			"Team 1 Ryan Schreiber, Joshua Churning, Riley Truatman"),

	gallery_button{Point(50,(y_max()/2)-100),400,400,"Gallery",cb_gallery},
	add_button{Point(550,(y_max()/2)-100),400,400,"Add Picture",cb_add},

	left_button{Point(0,(y_max()/2)-10),50,20,"< Left",cb_left},	// View
	right_button{Point(x_max()-50,(y_max()/2)-10),50,20,"Right >",cb_right},
	del_button{Point(x_max()/2,(y_max()-100)-10),50,20,"Delete",cb_del},
	search_button{Point((x_max()/2)-150+275,50),30,20,"GO",cb_search},

	gallery_filename(Point(100,y_max()-100),200,20,"File Name:"),
	gallery_tags(Point(100,y_max()-60),200,20,"File Tags :"),
	search_box(Point((x_max()/2)-150,50),250,20,"Search:"),

	download_button{Point(300,300),80,20,"Download",cb_download},	// Add
	addpic_button{Point(600,300),80,20,"Add Picture",cb_addpic},

	url(Point(280,200),200,20,"URL"),
	url_filename(Point(280,230),200,20,"File Name"),
	url_tags(Point(280,260),200,20,"Tags"),
	path(Point(580,200),200,20,"Full Path"),
	path_filename(Point(580,230),200,20,"File Name"),
	path_tags(Point(580,260),200,20,"Tags"),
	error_message(Point(280,350),500,20,"Result:"),

	background_home{Point(0,0),"background_home.gif"},
	background_add_1{Point(0,0),"background_add_1.gif"},
	background_add_2a{Point(0,150),"background_add_2.gif"},
	background_add_2b{Point(800,150),"background_add_2.gif"},
	background_add_3{Point(200,400),"background_add_3.gif"},

	file_text(Point(580,170),"Download from File"),
	web_text(Point(280,170),"Download from Web"),

	pics(get_pictures("archive.txt"))
	{
		init_extns();
		for (Picture p : pics)
		{	images.push_back(get_image_pointer(p.get_location()));	}
		tagged_images = images;

		// Attach and hide everything
		attach_all_widgets();
		attach_all_text();

		// Set up screen
		massshow_home_screen();
	}

// --- GoodButton Interactions --------------------------------------------- //

void Pic_window::rm_button(GoodButton& g)
{
  Base::detach(g.r);
  Base::detach(g.t);
  Base::detach(g);
}

void Pic_window::show_button(GoodButton& g)
{
  g.show();
  Base::attach(g.r);
  Base::attach(g.t);
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
	output_archive("archive.txt",pics);
}

// Back1 Button (gallery)

void Pic_window::cb_back1(Address,Address pw)
{
	reference_to<Pic_window>(pw).back1();
}

void Pic_window::back1()
{
	masshide_gallery_screen();
	Window::detach(*tagged_images[current]);
	massshow_home_screen();
}

// Back2 Button (add)

void Pic_window::cb_back2(Address,Address pw)
{
	reference_to<Pic_window>(pw).back2();
}

void Pic_window::back2()
{
	masshide_add_screen();
	massshow_home_screen();
}

// --- Home Screen --------------------------------------------------------- //

// Gallery
void Pic_window::cb_gallery(Address,Address pw)
{
	reference_to<Pic_window>(pw).gallery();
}

void Pic_window::gallery()									// 22 Lines
{
	if (tag == ""){
		tagged_images = images;
		tagged_pics = pics; }
	masshide_home_screen();
	massshow_gallery_screen();

	if (tagged_images.size() == 0)
		tagged_images.push_back(images[0]);
	if (tagged_images.size() == 1)
		current = 0;
	else if (current == 0)
		current = 1;
	if (current == 0)
		rm_button(del_button);
	if (tagged_images.size() < 2)
	{	rm_button(right_button);
		rm_button(left_button); }

	gallery_filename.put(tagged_pics[current].get_location());
	gallery_tags.put(tagged_pics[current].get_string_of_tags());
	Window::attach(*tagged_images[current]);
	Window::redraw();
}

// Add
void Pic_window::cb_add(Address,Address pw)
{
	reference_to<Pic_window>(pw).add();
}

void Pic_window::add()
{
	masshide_home_screen();
	massshow_add_screen();
}

// --- Gallery Screen ------------------------------------------------------ //

// Left
void Pic_window::cb_left(Address,Address pw)
{
	reference_to<Pic_window>(pw).left();
}

void Pic_window::left()
{
	Window::detach(*tagged_images[current]);
	current -= 1;
	if (current < 1) current = tagged_images.size()-1;
	gallery();
}

// Right
void Pic_window::cb_right(Address,Address pw)
{
	reference_to<Pic_window>(pw).right();
}

void Pic_window::right()
{
	Window::detach(*tagged_images[current]);
	current += 1;
	if (current > tagged_images.size()-1) current = 1;
	gallery();
}

// Delete
void Pic_window::cb_del(Address,Address pw)
{
	reference_to<Pic_window>(pw).del();
}

void Pic_window::del()
{
	delete_picture(tagged_pics[current].get_location(),pics,tagged_pics);
	Window::detach(*tagged_images[current]);
	for (unsigned int i = 0; i < images.size(); ++i)
	{
		if (tagged_images[current] == images[i])
		{
			images.erase(images.begin()+i);
			break;
		}
	}
	tagged_images.erase(tagged_images.begin()+current);
	while (current > images.size()-1) { current -= 1; }
	gallery();
	output_archive("archive.txt",pics);
	Window::redraw();
}

// Search
void Pic_window::cb_search(Address,Address pw)
{
	reference_to<Pic_window>(pw).search();
}

void Pic_window::search()
{
	Window::detach(*tagged_images[current]);
	tag = search_box.get_string();
	if (tag != "")
	{
		vector<string> tag_vector = parse_string(tag,delc);
		get_images_with_tag(pics,tagged_pics,images,tagged_images,tag_vector);
	}
	else
	{
		tagged_images = images;
		tagged_pics = pics;
	}
	current = 0;
	gallery();
}

// --- Add Screen ---------------------------------------------------------- //

// Download
void Pic_window::cb_download(Address,Address pw)
{
	reference_to<Pic_window>(pw).download();
}

void Pic_window::download()				// 20 Lines (whitespace included)
{
	string s_url = url.get_string();
	string s_url_filename = url_filename.get_string();
	string s_url_tags = url_tags.get_string();
	string e;

	try{
		check_valid_input(s_url,s_url_filename,pics,e);

		try{
		pics.push_back(download_picture(s_url,s_url_filename,s_url_tags));}
		catch (...) {
		e = "Unsuccessful Download";
		throw 1; }

		output_archive("archive.txt",pics);
    images.push_back(get_image_pointer(pics[pics.size()-1].get_location()));
		e = "Success!";
		error_message.put(e);

	} catch (...) {error_message.put(e);}
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
  string e;

	try{
		check_valid_input(s_path,s_path_filename,pics,e);

		pics.push_back(add_from_file(s_path,s_path_filename,s_path_tags));
		output_archive("archive.txt",pics);
    images.push_back(get_image_pointer(pics[pics.size()-1].get_location()));
		e = "Success!";
		error_message.put(e);

	} catch (...) {error_message.put(e);}
}

// --- Mass Attach/Hide/Show Functions (to keep functions lines<24) -------- //
// ATTACH

void Pic_window::attach_all_widgets()				// 24 lines w/ comments
{													// 21 lines w/o comments
	// Buttons
	Window::attach(quit_button); rm_button(quit_button);
	Window::attach(back1_button); rm_button(back1_button);
	Window::attach(back2_button); rm_button(back2_button);
	Window::attach(gallery_button); rm_button(gallery_button);
	Window::attach(add_button); rm_button(add_button);
	Window::attach(left_button); rm_button(left_button);
	Window::attach(right_button); rm_button(right_button);
	Window::attach(del_button); rm_button(del_button);
	Window::attach(search_button); rm_button(search_button);
	Window::attach(download_button); rm_button(download_button);
	Window::attach(addpic_button); rm_button(addpic_button);
	// In boxes
	Window::attach(url); Window::detach(url);
	Window::attach(url_filename); Window::detach(url_filename);
	Window::attach(url_tags); Window::detach(url_tags);
	Window::attach(path); Window::detach(path);
	Window::attach(path_filename); Window::detach(path_filename);
	Window::attach(path_tags); Window::detach(path_tags);
	Window::attach(gallery_filename); Window::detach(gallery_filename);
	Window::attach(gallery_tags); Window::detach(gallery_tags);
	Window::attach(search_box); Window::detach(search_box);
	// Out boxes
	Window::attach(error_message) ; Window::detach(error_message);
}

void Pic_window::attach_all_text()
{
	//Text
	heading.set_font_size(100);
	Window::attach(heading);
	names.set_font_size(20);
	Window::attach(names);
	web_text.set_font_size(20);
	file_text.set_font_size(20);
}

// --- Mass Attach/Hide/Show Functions (to keep functions lines<24) -------- //
// MASS SHOW

void Pic_window::massshow_home_screen()
{
	Window::attach(background_home);
	// Buttons
	show_button(gallery_button);
	show_button(add_button);
	// Text
	Window::attach(heading);
	Window::attach(names);
	show_button(quit_button);
}

void Pic_window::massshow_gallery_screen()
{
	// Buttons
	show_button(back1_button);
	show_button(right_button);
	show_button(left_button);
	show_button(del_button);
	show_button(search_button);
	// Boxes
	gallery_filename.show();
	gallery_tags.show();
	search_box.show();
	show_button(quit_button);
}

void Pic_window::massshow_add_screen()
{
	// Images
	attach(background_add_1);
	attach(background_add_2a);
	attach(background_add_2b);
	attach(background_add_3);
	// Text
	Window::attach(web_text);
	Window::attach(file_text);
	// Buttons
	show_button(download_button);
	show_button(addpic_button);
	show_button(back2_button);
	// Boxes
	url.show();
	url_filename.show();
	url_tags.show();
	path.show();
	path_filename.show();
	path_tags.show();
	error_message.show();
	show_button(quit_button);
}

// --- Mass Attach/Hide/Show Functions (to keep functions lines<24) -------- //
// MASS HIDE

void Pic_window::masshide_home_screen()
{
	rm_button(gallery_button);
	rm_button(add_button);
	Window::detach(heading);
	Window::detach(names);
	Window::detach(background_home);
}

void Pic_window::masshide_gallery_screen()
{
	// Buttons
	rm_button(back1_button);
	rm_button(right_button);
	rm_button(left_button);
	rm_button(del_button);
	rm_button(search_button);
	// In_boxes
	gallery_filename.hide();
	gallery_tags.hide();
	search_box.hide();
}

void Pic_window::masshide_add_screen()
{
	// Buttons
	rm_button(back2_button);
	rm_button(download_button);
	rm_button(addpic_button);
	// Boxes
	url.hide();
	url_filename.hide();
	url_tags.hide();
	path.hide();
	path_filename.hide();
	path_tags.hide();
	error_message.hide();
	// Text
	Window::detach(web_text);
	Window::detach(file_text);
	detach(background_add_1);
	detach(background_add_2a);
	detach(background_add_2b);
	detach(background_add_3);
}

// --- Other Stuff --------------------------------------------------------- //

Image* get_image_pointer(string fn)
{
	return new Image{Point(100,100),"gallery/"+fn};
}

void get_images_with_tag(vector<Picture> ps, vector<Picture>& tps,
			vector<Image*> is, vector<Image*>& os, vector<string> tag)
{
	os.clear();
	tps.clear();
	os.push_back(is[0]);
	tps.push_back(ps[0]);
	bool b;
	for (unsigned int i = 0; i<ps.size(); ++i)
	{
		b = true;
		for (string s : tag)
		{
			if (!contains(ps[i].get_tags(),s))
				b = false;
		}
		if (b)
		{
			tps.push_back(ps[i]);
			os.push_back(is[i]);
		}
	}
}

void check_valid_input(string locin, string locout,
						vector<Picture> pics,string& e)
{
	if (!archive::contains(extns,get_extension(locin)))
		{
			e = "Invalid file. Supported files: ";
			for (string s : extns)
			{ e=e+ s+" , "; }
			throw 1;
		}
		for (unsigned int i = 0; i < locout.size(); ++i)
		{
			switch (locout[i]){
			case '\\': case '/': case '*': case ' ':
			e = "Invalid character : "+locout[i];
			throw 1;
			default: break;}
		}
		for (Picture p : pics)
		{
			if (locout == p.get_location()||
				locout+get_extension(locin) == p.get_location())
			{
				e = "File name already exists. Please choose another file name.";
				throw 1;
			}
		}
}
