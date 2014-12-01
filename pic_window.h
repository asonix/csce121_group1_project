
// pic_window.h

#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "picture.h"
#include "archive.h"
#include "button.h"

using namespace Graph_lib;

#ifndef PIC_WINDOW
#define PIC_WINDOW

class Pic_window : Graph_lib :: Window
{
  typedef Window Base;
  public:
    void rm_button(GoodButton& g);
    void show_button(GoodButton& g);
    vector<Picture> pics;
    vector<Picture> tagged_pics;
    Pic_window(Point xy,int w,int h,const string& title);
    int current = 0;
    vector<Image*> images;
    vector<Image*> tagged_images;
    string tag = "";
    
    Image background_home;
    Image background_add_1;
    Image background_add_2a;
    Image background_add_2b;
    Image background_add_3;
    
    // --- Navigation -------------------------------------------------- //
    
    GoodButton quit_button;
    static void cb_quit(Address,Address);
    void quit();
    
    GoodButton back1_button;
    static void cb_back1(Address,Address);
    void back1();
    
    GoodButton back2_button;
    static void cb_back2(Address,Address);
    void back2();
    
    // --- Home Screen ------------------------------------------------- //
    
    Text heading,names;
    
    GoodButton gallery_button;
    static void cb_gallery(Address,Address);
    void gallery();	
    
    GoodButton add_button;
    static void cb_add(Address,Address);
    void add();	
    
    // --- Gallery Screen ---------------------------------------------- //
    
    GoodButton right_button;
    static void cb_right(Address,Address);
    void right();
    
    GoodButton left_button;
    static void cb_left(Address,Address);
    void left();
    
    GoodButton del_button;
    static void cb_del(Address,Address);
    void del();
    
    Out_box gallery_filename;
    Out_box gallery_tags;
    In_box search_box;
    
    GoodButton search_button;
    static void cb_search(Address,Address);
    void search();
    
    
    // --- Add Screen -------------------------------------------------- //
    
    GoodButton download_button;
    static void cb_download(Address, Address);
    void download();
    
    GoodButton addpic_button;
    static void cb_addpic(Address, Address);
    void addpic();
    
    In_box url,url_filename,url_tags,path,path_filename,path_tags;
    Out_box error_message;
    Text file_text,web_text;
    
    // --- Mass Attach/Hide/Show functions ----------------------------- //
    
    void attach_all_widgets();
    void attach_all_text();
    
    void massshow_home_screen();
    void massshow_gallery_screen();
    void massshow_add_screen();
    
    void masshide_home_screen();
    void masshide_gallery_screen();
    void masshide_add_screen();
    
};



Image* get_image_pointer(string fn);
void get_images_with_tag(vector<Picture> ps, vector<Picture>& tps, 
    vector<Image*> is, vector<Image*>& os, vector<string> tag);
void check_valid_input(string locin, string locout,
            vector<Picture> pics,string& e);

#endif
