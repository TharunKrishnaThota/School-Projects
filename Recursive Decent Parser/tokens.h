/* Name = Tharun Krishna Thota
 Class = CS 280 - 003
 Student ID = 31256661
 UCID = tkt6@njit.edu
*/


#ifndef TOKENS_H_
#define TOKENS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

namespace Tokens {
enum Token {
	TEXT, LANGLE, RANGLE, SLASH, ID, EQ, QSTRING, OTHER, END,
};

extern Token getToken(istream*, string&);
extern string tokenName(Token);
extern int currLine;
}


#endif /* TOKENS_H_ */
