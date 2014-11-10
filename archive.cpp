
// archive.cpp

#include "std_lib_facilities_4.h"
#include "picture.h"
#include "archive.h"
//#include <windows.h>

// Credit for this block of code at the bottom of the file and report
#include <stdio.h>
#ifdef WINDOWS
	#include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif
// -------------------------------------------------------------------
// extern variables

string cwd = getcwd();
vector<string> extns = vector<string>();

void init_extns()
{
	extns.push_back(".jpg");
	extns.push_back(".JPG");
	extns.push_back(".jpeg");
	extns.push_back(".JPEG");
}

// ------------------------------------------------------------------------- //

vector<Picture> get_pictures(string infile)
{
	ifstream in; 
	string instring,loc;
	vector<string> tags;
	vector<Picture> pictures;
	
	try {in.open(infile);} 			// if the archive.txt doesn't exist
	catch (...) {return pictures;}	// then return empty vector
	
	while (!in.eof())
	{
		getline(in,instring);
		tags = parse_string(instring,delc);
		loc = tags[0];
		tags.erase(tags.begin());
		pictures.push_back(Picture(loc,tags));
	}
	
	in.close();	
	return pictures;
}

vector<Picture> get_pictures(string infile, string tag)
{
	vector<Picture> pictures_in = get_pictures(infile);
	vector<Picture> pictures_out;
	vector<string> tags = parse_string(tag,delc);
	for (Picture p : pictures_in)
	{
		for (string s : tags)
		{
			if (contains(p.get_tags(),s))
				pictures_out.push_back(p);
		}
	}	
	return pictures_out;
}

void output_archive(string outfile, vector<Picture> pics)
{	
	ofstream os;
	os.open(outfile);
	stringstream output;
	for (Picture p : pics)
	{
		os << p;
		if (p.get_location() != pics[pics.size()-1].get_location())
			os << '\n';
	}
	os.close();
}

// ------------------------------------------------------------------------- //
// System Functions

Picture download_picture(string url, string filename, string tags)
{
	if (!contains(extns,get_extension(url)))
	{
		cout << "\nInvalid file from internet. Must have one of the \n"
			<< "accepted extensions: \n";
		for (string s : extns)
		{ cout << s << "   "; }
		cout << endl;
		return Picture();
	}
	system((string("wget ") + url).c_str());				// download
	string rfn = get_raw_filename(url);						// get dl name	
	if (filename.size() < get_extension(url).size() || 
		get_extension(url) != get_extension(filename))
			filename += get_extension(url); 				// proper ext.
	system((string("mv ") + rfn + " gallery/" + filename).c_str()); // rename	
	return Picture(filename,tags);
}

void delete_picture(string p, vector<Picture>& a)
{
	system((string("rm gallery/") + p).c_str());	// Delete file
	
	for (unsigned int i = 0; i<a.size(); ++i)		// Delete from .txt
	{
		if (p == a[i].get_location())
			a.erase(a.begin()+i);
	}	
}

// ------------------------------------------------------------------------- //

string get_raw_filename(string url)
{
	string out;
	char c = url[url.size()-1];
	url.pop_back();
	while (c != '/')
	{
		out.insert(out.begin(),c);
		c = url[url.size()-1];
		url.pop_back();
	}
	return out;
}

string get_extension(string filename)
{
	string out = "";
	try
	{
		char c = filename[filename.size()-1];
		filename.pop_back();
		while (c != '.')
		{
			out.insert(out.begin(),c);
			c = filename[filename.size()-1];
			filename.pop_back();
		}
		return "."+out;
	}
	catch(...) {return out;}
}

// ------------------------------------------------------------------------- //
// This function is based largely on code on source forge authored by the    //
// user named "computerlife" and later edited by the user named "Polar".     //
// The proper reference citation is at the bottom of this file (archive.cpp) //
// as well as in the appendix of the final report as reference number 2.	 //

string getcwd()
{
	char cCurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		//return errno;
	}
	string str = cCurrentPath;
	return str;
}

// ------------------------------------------------------------------------- //

Picture add_from_file(string full_path,string new_name,string tags)
{
	if (!contains(extns,get_extension(full_path)))
	{
		cout << "\nInvalid file from internet. Must have one of the \n"
			<< "accepted extensions: \n";
		for (string s : extns)
		{ cout << s << "   "; }
		cout << endl;
		throw extns;
	}
	if (new_name.size() < get_extension(full_path).size() || 
		get_extension(full_path) != get_extension(new_name))
			new_name += get_extension(full_path); 				// proper ext.
	system(("cp " + get_proper(full_path) + " gallery/" + new_name).c_str());
	return Picture(new_name,tags);	
}

string get_proper(string s)
{
	string n = "/cygdrive/c";
	for (unsigned int i = 2; i<s.size(); ++i)
	{
		if (s[i] == ' ')
			n += "\\ ";
		else if (s[i] == '\\')
			n += "/";
		else
			n += s[i];
	}
	//cout << s;
	return n;
}

/* ------------------------------------------------------------------------- //

Cited References

2. Used in lines 133-150.

"drby" . 2009 Mar 4. Read filenames from a directory [Internet].
:Source Forge; [2009 Mar 4, cited 2014 Oct 30] . Available from: 
http://stackoverflow.com/questions/609203/
read-file-names-from-a-directory/609236#609236

// ------------------------------------------------------------------------- */