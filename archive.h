
// archive.h

#include "std_lib_facilities_4.h"
#include "picture.h"
//#include <windows.h>

#ifndef ARCHIVE
#define archive

extern string cwd; // holds the cwd when the program begins
extern vector<string> extns;
void init_extns();

vector<Picture> get_pictures(string infile);
vector<Picture> get_pictures(string infile, string tag);
void output_archive(string outfile, vector<Picture> pics);

Picture download_picture(string url, string filename, string tags);
Picture add_from_file(string full_path,string new_name,string tags);
void delete_picture(string p, vector<Picture>& a);

string get_raw_filename(string url);
string get_extension(string filename);

string get_proper(string s);

string getcwd();

#endif