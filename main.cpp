#include <iostream>
#include "parser.h"
#include "scanner.h"
#include <sstream>

using namespace std;

string& trim(string &s);

int main( int argc , char **argv ) {
	do {
		cout << "?-";
		string input;
		getline(cin, input);
		if (trim(input) == "halt.")
			break;
		if (trim(input) == "")
			continue;
		Scanner s(input);
		Parser p(s);
		try{
			p.buildExpression();
			string result = p.excuteExp();
			cout << result << endl;
		} catch (std::string & msg) {
			cout << msg << endl;
		}
	} while(true);
    return 0;
}

string& trim(string &s) {
    if (s.empty()) {
         return s;
    }
 
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}
