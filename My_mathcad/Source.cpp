#include <iostream>
#include "FirstParser.h"
#include "MainParser.h"
using namespace std;
using namespace fp;


int main() {
	FirstParser first_parser;
	MainParser main_parser;
	string str = "1.1+2.2156-3";
	auto tokens = first_parser.parse(str);
	auto tree = main_parser.parse(tokens);
	return 0;
}
