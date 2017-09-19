#include <iostream>
#include <regex>
#include <string.h>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	string s[3] = { "abc##","abcd#", "a##abcd" };


	//regex r("\\w(\\w+#)|(\\w#\\w*)*");
	regex r("(\\w+#?)+");
	//regex r("\\w((\\w*#)|\\w*(#\\w+)*)");

	//smatch m;

	////
	//regex_search(s, m, r);

	//for (auto x : m)
	//	cout << x << " ";

	/*if (regex_match(s, r)) {
		cout << "TRUE" << endl;
	}
	*/

	smatch sm;
	for (int j = 0; j <3; ++j) {
		regex_match(s[j], sm, r, regex_constants::match_default);
		std::cout << "the matches were: ";
		for (unsigned i = 0; i< 1 ;++i) {
			std::cout << "[" << sm[i] << "] ";
		}
		cout << endl;
	}
	return 0;
}
