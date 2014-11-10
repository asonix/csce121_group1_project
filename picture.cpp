
// picture.cpp

#include "std_lib_facilities_4.h"
#include "picture.h"

char delc = ',';

// ----------------------------------------------------------------------------
// Constructors

Picture::Picture()
{
	location = "";
}

Picture::Picture(string loc,string tag_string)
{
	location = loc;
	tags = (parse_string(tag_string,delc));
}

Picture::Picture(string loc,vector<string> tag_vector)
{
	location = loc;
	tags = tag_vector;
}

// ----------------------------------------------------------------------------
// Accessors 

string Picture::get_location() {return location;}
vector<string> Picture::get_tags() {return tags;}

// ----------------------------------------------------------------------------
// Modifiers 

void Picture::set_location(string loc) {location = loc;}
void Picture::set_tags(vector<string> tag_list) {tags = tag_list;}
void Picture::set_tags(string tag_string) {tags = parse_string(tag_string,delc);}

void Picture::add_tag(string tag)
{
	if (contains(tags,tag))
		return;
	for (string i : parse_string(tag,delc))
	{
		tags.push_back(i);
	}
}

void Picture::remove_tag(string tag)
{
	for (unsigned int i = 0; i<tags.size(); ++i)
	{
		if (tags[i] == tag)
			tag.erase(tag.begin()+i);
	}
}

// ----------------------------------------------------------------------------
// Helper Functions

vector<string> parse_string(string in, char del)
{
	vector<string> out;
	string temp = "";
	
	if (in == "")
	{
		out.push_back("none");
		return out;
	}
	
	for (unsigned int i = 0; i<in.size(); ++i)
	{
		if (in[i] == del)
		{
			out.push_back(temp);
			temp = "";
		}
		else
		{
			temp += in[i];
		}
	}
	out.push_back(temp);
	
	return out;
}

bool contains(vector<string> v, string s)
{
	for (string i : v)
	{
		if (i == s)
			return true;
	}
	return false;
}

void remove_whitespace(string& s)
{
	while (s[0] == ' ')
	{ s.erase(s.begin()); }
	while (s[s.size()-1] == ' ')
	{ s.pop_back(); }
}

// ----------------------------------------------------------------------------
// Operator Overloads

ostream& operator<<(ostream& os, Picture p)
{
	string out = p.get_location();
	for (string s : p.get_tags())
	{
		out += ","+s;
	}
	return os << out;
}

// ----------------------------------------------------------------------------
