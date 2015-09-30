/* Name = Tharun Krishna, Thota
 Class = CS 280 - 003
 Student ID = 31256661
 UCID = tkt6@njit.edu
*/


#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <map>
#include "tokens.h"
#include <cstring>
#include <algorithm>

using namespace std;
vector<string>hold;
vector<string>tram;
vector<string>trip;
vector<string>htag;
vector<string>htag1;
vector<string>texter;
vector<string>textholder;


string temp = "";
string content10 = "";
string content11 = "";
string content12 = "";
string content13 = "";
int amount =1;
int fis = 0;
int fis1;
int begin = 0;
int h1 =0;
int h2=0;
int h3=0;
int h4=0;

void ReplaceStringInPlace1(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

void
usage(char *progname, string msg)
{
	cerr << msg << endl;
	cerr << "Usage is: " << progname << " [-v] [filename]" << endl;
	cerr << " specifying -v makes the program run in verbose mode" << endl;
	cerr << " specifying filename reads from that file; no filename reads standard input" << endl;
}

int
main( int argc, char *argv[] )
{

	istream *br;
	ifstream infile;

	bool verbose = false;
	br = &cin;

	for( int i=1; i<argc; i++ ) {

		if( strcmp(argv[i], "-v") == 0 )
			verbose = true;
		else {
			// make sure the user didn't already give a file name
			if( br != &cin ) {
				usage(argv[0], "More than one file name was given");
				return 1;
			}

			infile.open(argv[i]);
			if( infile.is_open() )
				br = &infile;
			else {
				usage(argv[0], "Cannot open " + string(argv[i]));
				return 1;
			}
		}
	}

	// pass br as the first argument to getToken()
	Tokens::Token tt;
	string lexmatch;

	while( (tt = Tokens::getToken(br, lexmatch)) != Tokens::END ) {
		hold.push_back(lexmatch);

		if( verbose )
		{
			//cout << Tokens::tokenName(tt) << ":" << lexmatch << ":" << endl;
		}
		if(Tokens::tokenName(tt) == "TEXT")
		{
			texter.push_back(lexmatch);
		}

	}
	for(int i =0; i < hold.size(); i++)
	{
		content10 += hold[i];
	}
	char l;
	for(int i=0; i < content10.size(); i++)
	{
		l = content10.at(i);
		if(l == '/')
		{
			fis1 = 100;
		}
		if(l == '<')
		{
			fis++;
		}
		if(l == '>')
		{
			fis--;
			fis1 = 0;
		}
		if(fis == 1 && fis1 == 0)
		{
			content11 += content10[i];
		}
		if(fis == 1 && fis1 == 100)
		{
			content12 += content10[i];
		}
		if(fis == 0 && fis1 == 0)
		{
			content13 += content10[i];
		}
	}
	texter.erase(std:: remove(texter.begin(),texter.end(),"\n"),texter.end());
	ReplaceStringInPlace1(content11,"<"," ");
	ReplaceStringInPlace1(content12,"/"," ");
	string content15;
	istringstream ss5(content11);
	vector <string> content16;
	vector<string> content20;
	while(ss5 >> content15)
	{
		content20.push_back(content15);
		content16.push_back(content15);

	}
	string content17;
	istringstream ss6(content12);
	vector <string> content18;
	while(ss6 >> content17)
	{
		content18.push_back(content17);

	}
	sort(content16.begin(),content16.end());
	sort(content18.begin(),content18.end());
	for(int i =0; i < content18.size();i++)
	{
		if(content18[i] != content16[i])
		{
			cout << "Start tag title does not match end tag author";
			exit(0);
		}
	}
	for (int i = 0; i < content16.size()-1; ++i)
	{
		if (content16[i] == content16[i+1])
		{
			amount++;
		}
		else
		{
			cout << content16[i] << ": " << amount << endl;
			htag1.push_back(content16[i]);
			amount = 1;
		}
	}
	cout << content16.back() << ": " << amount << endl;
	htag1.push_back(content16.back());

	for(int i=0; i < texter.size(); i++)
	{
		//cout << texter[i];
	}
	//cout << texter[1];

	for(int i = 0; i < content20.size();++i)
	{
		if((content20[i] == "h1") || (content20[i] == "h2") || (content20[i] == "h3") || (content20[i] == "h4"))
		{
			htag.push_back(content20[i]);
			textholder.push_back(texter[i]);
		}
	}
	//cout << endl;
	for(int i =0; i < htag.size(); i++)
	{
		//cout << htag[i] + " ";
		//cout << textholder[i] + " ";
	}
	cout << endl;
	for(int i=0; i < htag.size();i++)
	{
		if(htag[i] == "h1")
		{
			h1++;
			cout << h1 <<": ";
			cout << textholder[i];

			if(h1 > 1)
			{
				h2 = 0;
				h3 = 0;
				h4 = 0;
			}
		}
		if(htag[i] == "h2")
		{
			h2++;
			cout << h1 <<":";
			cout << h2 << ": ";
			cout << textholder[i];

			if(h2 > 1)
			{
				h3 = 0;
				h4 = 0;
			}
		}
		if(htag[i] == "h3")
		{
			h3++;
			cout << h1 <<":";
			cout << h2 << ":";
			cout << h3 << ": ";
			cout << textholder[i];


			if(h3 > 1)
			{
				h4 = 0;
			}
		}
		if(htag[i] == "h4")
		{
			h4++;
			cout << h1 <<":";
			cout << h2 << ":";
			cout << h3 << ":";
			cout << h4 << ": ";
			cout << textholder[i];
		}
		cout << endl;
	}




}

