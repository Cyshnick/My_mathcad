#include <iostream>
#include "Parser.h"
using namespace std;



int main() {
	FirstParser parser;
	string str = "1.1+2.2156-3*log(x,y)";
	parser.parse(str);
	return 0;
}
