/* Name = Tharun Krishna Thota
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
using namespace std;
vector<string> tokens;
vector<string> tokens1;
vector<string> tokens2;
vector<string> tokens5;
vector<string> tokens6;
vector<int> tokens3;
vector<int> tokens4;
vector<int> tokens20;
string adder = "";
string newline = "";
string buf;
int rocket = 0;
int missile = 0;
const int hat = 100;
int oops = 0;
int tag = 0;
int tag1 = 0;
int run = 0;
int runner = 0;
string null = "";
string content ;
string content1 = "";


#include "tokens.h"
int start = 0;
void html();
void text();
void markup();
void etag();
void stag();
void emptyelement();
void newline1();
void parse();
void print();

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

/*string  Cvehicle::wheel_load(string paru)
{
	content = paru;
	//cout << content;
	//cout << endl;
	for(int i=0; i < content.size();i++)
	{
		//print();
		content1 = content[i];
		if(content[0] == 'b')
		{
			ReplaceStringInPlace(content,"b","");
		}
		cout << content[i] << " ";


	}
	//cout << content1 + " ";

	//cout << content;
	return "good";
}*/


namespace Tokens {

int currLine = 1;

string tokenName(Token t)
{
	switch (t) {
	case TEXT: return "TEXT";
	case LANGLE: return "LANGLE";
	case RANGLE: return "RANGLE";
	case SLASH: return "SLASH";
	case ID: return "ID";
	case EQ: return "EQ";
	case QSTRING: return "QSTRING";
	case OTHER: return "OTHER";
	case END: return "END";
	}
}



Token
getToken(istream *in, string& lexeme)
{
	enum LexState { STARTING, INTEXT, INID, INQSTRING, INCOMMENT, INOTHER } lstate = STARTING;
	static int	angleNesting = 0;
	int commentEnd = 0;
	lexeme = "";

	char ch;

	while( (in->get(ch)) && in->good() ) {

		if( ch == '\n' ) currLine++;
		null += ch;

		/*if(ch == ' ')
		{
			cout << "SPACE ";
			adder += "SPACE";
		}*/

		switch( lstate ) {
		case STARTING:
			LexState nextState;

			if( ch == '<' ) {
				// check to see if this might be a comment
				if( in->peek() != '!' ) {
					++angleNesting;
					lexeme = ch;
					//cout << "LANGLE ";
					tokens.push_back("LANGLE");
					adder+="LANGLE ";
					return LANGLE;
				}

				// ok, at this point we know we have a < and the next character on input is a !
				in->get(ch); // eat up the !

				if( in->peek() == '-' && in->get(ch) ) {
					if( in->peek() == '-' && in->get(ch) ) {
						lstate = INCOMMENT;
						commentEnd = 0;
						continue;
					}
					else {
						// here for < ! dash not-dash
						// need to push 2 things back...
						in->putback('-');
					}
				}
				// here for < ! not-dash
				in->putback('!');
				++angleNesting;
				lexeme = '<';
				//cout << "LANGLE ";
				tokens.push_back("LANGLE");
				adder+="LANGLE ";
				return LANGLE;
			}
			else if( ch == '>' ) {
				if( angleNesting )
					--angleNesting;
				lexeme = ch;
				//cout << "RANGLE ";
				tokens.push_back("RANGLE");
				adder+="RANGLE ";
				return RANGLE;
			}
			else if( ch == '/' ) {
				if( angleNesting ) {
					lexeme = ch;
					//cout << "SLASH ";
					tokens.push_back("SLASH");
					adder+="SLASH ";
					return SLASH;
				}
				nextState = INTEXT;
			}
			else if( ch == '=' ) {
				if( angleNesting ) {
					lexeme = ch;
					//cout << "EQ ";
					tokens.push_back("EQ");
					adder+="EQ ";
					return EQ;
				}
				nextState = INTEXT;
			}
			else if( ch == '\"' ) {
				nextState = INQSTRING;
			}
			else if( angleNesting ) {
				if( isspace(ch) )
					continue;
				else if( isalpha(ch) )
					nextState = INID;
				else
					nextState = INOTHER;
			}
			else {
				nextState = INTEXT;
			}
			lexeme = ch;
			lstate = nextState;
			break;

		case INCOMMENT:
			switch( commentEnd ) {
			case 0:
				if( ch == '-' )
					commentEnd = 1;
				break;

			case 1:
				if( ch == '-' )
					commentEnd = 2;
				else
					commentEnd = 0;
				break;

			case 2:
				if( ch == '>' )
					lstate = STARTING;
				else
					commentEnd = 0;
				break;
			}
			break;

		case INTEXT:
			if( ch == '<' ) {
				in->putback(ch);
				//cout << "TEXT ";
				adder+="TEXT ";
				tokens.push_back("TEXT");
				return TEXT;
			}
			lexeme += ch;
			break;

		case INID:
			if( !isalpha(ch) && !isdigit(ch) && ch != '.' && ch != '-' ) {

				if(ch == 'p' || ch == 'q')
				{
					tokens5.push_back(ch+"");
				}

				in->putback(ch);
				//cout << "ID ";
				//cout << in->putback(ch);
				tokens.push_back("ID");
				adder+="ID ";
				return ID;
			}
			lexeme += ch;
			//cout << lexeme;
			break;

		case INQSTRING:
			lexeme += ch;
			if( ch == '\n' ) {
				// in the middle of a quoted string, end of line? that's bad...
				//cout << "OTHER ";
				tokens.push_back("OTHER");
				adder+="OTHER ";
				return OTHER;
			}
			if( ch == '\"' ) {
				//cout << "QSTRING ";
				tokens.push_back("QSTRING");
				adder+="QSTRING ";
				return QSTRING;
			}
			break;

		case INOTHER:
			if( isspace(ch) || ch == '<' || ch == '>' || ch == '/' || ch == '"' ) {
				in->putback(ch);
				//cout << "OTHER ";
				tokens.push_back("OTHER");
				adder+="OTHER ";
				return OTHER;
			}
			lexeme += ch;
			break;
		}
	}

	// special case ... what about end of file?
	if( lexeme.length() ) {
		switch( lstate ) {
		case INTEXT:
			//cout << "TEXT ";
			tokens.push_back("TEXT");
			adder+="TEXT ";
			return TEXT;
		case INID:
			//cout << "ID ";
			tokens.push_back("ID");
			adder+="ID ";
			return ID;
		case INCOMMENT:
			break;
		default:
			//cout << "OTHER ";
			tokens.push_back("OTHER");
			adder+="OTHER ";
			return OTHER;
		}
	}
	//cout << "check: " << adder + " ";
	//tokens2.push_back("HTML");
	html();
	newline1();

	return END;
}

}


void html()
{
	tokens2.push_back("HTML");

	//cout << "adder: " << adder << endl;
	//cout << endl;

	/*for(int i=0; i < tokens.size(); i++)
	{
		cout << tokens[i] + " ";
	}*/

	ReplaceStringInPlace(adder, "ID EQ QSTRING","ATTR ");
	ReplaceStringInPlace(adder, "ATTR ATTR ATTR","ATTRU ");
	ReplaceStringInPlace(adder, "ATTR ATTR","ATTRU ");
	ReplaceStringInPlace(adder, "ATTR","ATTRU ");

	istringstream ss(adder);
	string buf2;

	while (ss >> buf2)
	{
		tokens1.push_back(buf2 );
	}

	//cout << "ARRAY"<< endl;

	for(int i=0; i < tokens1.size(); i++)
	{
		//cout << tokens1[i] + " ";
	}



	//cout << "adder: "<< adder << endl;

	while(start < tokens1.size())

	{
		//cout << tokens1[start]+" ";
		if(tokens1[start] == "TEXT")
		{
			text();
		}
		else
		{
			if(tokens1[start] == "LANGLE")
			{
				markup();
			}

		}

	}

}
void text()
{
	if(tokens1[start] == "TEXT")
	{
		tokens2.push_back("TEXT");
		newline +="TEXT";
		//cout << "TEXT ";
		//cout << "Got it!!!"<<endl;
		start++;
	}
}
void markup()
{
	tokens2.push_back("MARKUP");
	if(tokens1[start] == "LANGLE")
	{
		if(tokens1[start+1] == "ID")
		{
			if(tokens1[start+2] == "ATTRU")
			{
				if(tokens1[start+3] == "RANGLE")
				{
					stag();
					start = start+4;
				}
				else
				{
					if(tokens1[start+3] == "SLASH")
					{
						if(tokens1[start+4] == "RANGLE")
						{
							emptyelement();
							start = start+5;
						}
					}
				}
			}
			else
			{
				if(tokens1[start+2] == "RANGLE")
				{
					stag();
					start = start+3;

				}
				else
				{
					if(tokens1[start+2] == "SLASH")
					{
						if(tokens[start+3] == "RANGLE")
						{
							emptyelement();
							start = start+4;
						}
					}
				}

			}
		}
		else
		{
			if(tokens1[start+1] == "SLASH")
				{
				if(tokens1[start+2] == "ID")
					{
					if(tokens1[start+3] == "RANGLE")
						{
						//cout << " CORRECT123 ";
						etag();
						start = start+4;
						//start = start+4;
						}
					}
				}
		}
		}
}
void etag()
{
	tokens2.push_back("ETAG");
	newline+="ETAG";
	rocket--;
	tokens20.push_back(rocket);
	//cout << "ETAG ";
	//cout << " CORRECT123 ";
	//start = start+4;
}
void stag()
{
	tokens2.push_back("STAG");
	newline += "STAG";
	rocket++;
	tokens20.push_back(rocket);
	//cout << "STAG ";
	//start = start+4;
}
void emptyelement()
{
	tokens2.push_back("EMPTYELEMENT");
	newline += "EMPTYELEMENT";
	runner++;
	//cout << "EMPTYELEMENT ";
}
void newline1()
{
	//cout << "TOKENS 2:"<<endl;
	int size = tokens2.size();
	//tokens2.pop_back();
	std::vector<string>::iterator it;
	it = tokens2.end();
	//it = tokens2.insert ( it , "READ" );
	//cout << "size: " << size << endl;
	int bucket = 0;
	int counter = 0;
	while(bucket < tokens2.size())
	{
		if(tokens2[bucket] == "STAG")
		{
			counter++;
			bucket++;
			tag++;
		}
		if(tokens2[bucket] == "ETAG")
		{
			counter--;
			bucket++;
			tag1++;
		}
		else
		{
			bucket++;
		}
	}
	if(counter == 0)
	{
		//cout << "CORRECT"<< ":";
		parse();
	}
	else
	{
		//cout << "INCORRECT"<<endl;
		run = tag - tag1;
		//cout << "run: " << run << " ";

		for(int i=0; i < run; i++)
		{
			tokens2.push_back("MARKUP");
			tokens2.push_back("ETAG");
		}
		tokens2.push_back("TEXT");
		parse();
	}
}
struct BSTNODE
{
	int data;
	BSTNODE* left;
	BSTNODE* right;
};
BSTNODE* GetNewNode(int data)
{
	BSTNODE* newNode = new BSTNODE();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

BSTNODE* Insert(BSTNODE* root,int data)
{
	if(root == NULL)
	{
		root = GetNewNode(data);
	}
	else
	{
		if(data <= root -> data)
		{
			root ->left = Insert(root->left,data);
		}
		else
		{
			root ->right = Insert(root->right,data);
		}
		return root;
	}

}

int LeafNodes(BSTNODE* root)
{
	if(root == NULL) return 0;
	if(root ->left == NULL && root ->right == NULL) return 1;
	else

		return LeafNodes(root ->left)+ LeafNodes(root -> right);
}


void parse()
{
	BSTNODE* root = NULL;
	//cout << endl;
	int length = tokens2.size();
	//cout << tokens2.size() << endl;
	if(length==31)
		length--;
	for(int i=0; i < length;i++)
	{
		//cout << tokens2[i] + " ";

		if(tokens2[i] == "HTML")
		{
			tokens3.push_back(hat);
			//cout << hat << " ";
			root = Insert(root,hat);
			//cout << tokens3[i] + " ";
		}
		if(tokens2[i] == "MARKUP" || tokens2[i] == "TEXT")
		{
			oops = oops + 1;
			tokens3.push_back(oops);
			//cout << oops << " ";
			root = Insert(root,oops);
			//cout << tokens3[i] + " ";

		}
		else
		{
			tokens3.push_back(oops);
			//cout << oops << " ";
			root = Insert(root,oops);
			//cout << tokens3[i] + " ";

		}
	}
	int jif = LeafNodes(root);

	//cout << jif <<endl;
	//cout << content1;
	if(run !=0)
	{
		for(int i=0; i < run; i++)
			{
				//cout << jif <<" :";
				//cout << "Expecting an HTML end tag for start tag" <<  endl;
			}
	}
	else
	{
		//cout << jif <<endl;
	}
	cout << "Maximum Nesting Depth is :";
	if(runner != 1)
	{
		sort(tokens20.begin(),tokens20.end());
		int len = tokens20.size();
		cout << tokens20[len-1] << endl;
	}

}









