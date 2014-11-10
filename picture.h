
// picture.h

#include "std_lib_facilities_4.h"
#include "Graph.h"

#ifndef PICTURE
#define PICTURE

extern char delc; // delimiting character for parse_string function

// ------------------------------------------------------------------------- //
// Picture Class

class Picture
{
	public:
		Picture();
		Picture(string loc,string tag_string);
		Picture(string loc,vector<string> tag_vector);
		
		string get_location();
		vector<string> get_tags();
		
		void set_location(string loc);
		void set_tags(string tag_string);
		void set_tags(vector<string> tag_list);
		void add_tag(string tag);
		void remove_tag(string loc);
		
	private:
		string location;
		vector<string> tags;
};

// ------------------------------------------------------------------------- //

vector<string> parse_string(string in, char del);
bool contains(vector<string> v, string s);
void remove_whitespace(string& s);

ostream& operator<<(ostream& os, Picture p);

// ------------------------------------------------------------------------- //

#endif