
// archive.h

#include "std_lib_facilities_4.h"
#include "picture.h"
//#include <windows.h>

#ifndef ARCHIVE
#define archive

extern string cwd; // holds the cwd when the program begins
extern vector<string> extns;
extern vector<char> invalid_chars;
void init_extns();

vector<Picture> get_pictures(string infile);
vector<Picture> get_pictures(string infile, string tag);
void output_archive(string outfile, vector<Picture> pics);

Picture download_picture(string url, string filename, string tags);
Picture add_from_file(string full_path,string new_name,string tags);
void delete_picture(string p, vector<Picture>& a, vector<Picture>& b);

string get_raw_filename(string url);
string get_extension(string filename);

string get_proper(string s);
string get_html_char(string s);
int string_to_int(string in);

string getcwd();

#endif