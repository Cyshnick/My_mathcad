#include "Parser.h"
#include "FSM.h"
#include <iostream>
using namespace std;

// Переписать все это с нормальным конечным автоматом


FirstParser::FirstParser() :
	fsm({ 
		{States::START, States::START, Events::ISSEP, [this]() {add_sep(); }},
		{States::START, States::START, Events::ISSIGN, [this]() {add_sign(); }},
		{States::START, States::SYMB, Events::ISALPHA, [this]() {start_symb(); }},
		{States::START, States::CONST, Events::ISDIGIT, [this]() {start_const(); }},
		{States::CONST, States::CONST, Events::ISNUM, [this]() {add_const(); }},
		{States::CONST, States::CONST, Events::ISDIGIT, [this]() {add_const(); }},
		{States::SYMB, States::SYMB, Events::ISDIGIT, [this]() {add_symb(); }},
		{States::SYMB, States::SYMB, Events::ISALPHA, [this]() {add_symb(); }},
		{States::CONST, States::START, Events::ISSEP, [this]() {end_const(); add_sep(); }},
		{States::CONST, States::START, Events::ISSIGN, [this]() {end_const(); add_sign(); }},
		{States::SYMB, States::START, Events::ISSEP, [this]() {end_symb(); add_sep(); }},
		{States::SYMB, States::START, Events::ISSIGN, [this]() {end_symb(); add_sign(); }},
		{States::START, States::ERROR, Events::ELSE, [this]() {err_handler(); }},
		{States::SYMB, States::ERROR, Events::ELSE, [this]() {err_handler(); }},
		{States::CONST, States::ERROR, Events::ELSE, [this]() {err_handler(); }},
		{States::ERROR, States::ERROR, Events::ELSE, [this]() {err_handler(); }}
		})
{

}

tokens_t FirstParser::parse(std::string const& inp) {
	for (auto c : inp) {
		cur_char = c;
		Events e;
		if (is_sep())
			e = Events::ISSEP;
		else if (is_sign())
			e = Events::ISSIGN;
		else if (is_digit())
			e = Events::ISDIGIT;
		else if (is_alpha())
			e = Events::ISALPHA;
		else if (is_num())
			e = Events::ISNUM;
		else
			e = Events::ELSE;
		fsm.process(e);
	}

	return ret;
}

void FirstParser::add_sep() {
	std::cout << "(SEP: " << cur_char << " )" << std::endl;
}

void FirstParser::add_sign() {
	std::cout << "(SIGN: " << cur_char << " )" << std::endl;
}

void FirstParser::start_symb() {
	temp = "";
	temp += cur_char;
}

void FirstParser::start_const() {
	temp = "";
	temp += cur_char;
}

void FirstParser::add_symb() {
	temp += cur_char;
}

void FirstParser::add_const() {
	temp += cur_char;
}

void FirstParser::end_symb() {
	if(cur_char == '(')
		std::cout << "(FUNC: " << temp << " )" << std::endl;
	else
		std::cout << "(VAR: " << temp << " )" << std::endl;
}

void FirstParser::end_const() {
	std::cout << "(CONST: " << stod(temp) << " )" << std::endl;
}

void FirstParser::err_handler() {
	std::cout << "(ERROR_SYM: " << cur_char << std::endl;
}

bool FirstParser::is_sep() {
	return (cur_char == ',') || (cur_char == '(') || (cur_char == ')');
}

bool FirstParser::is_sign() {
	return (cur_char == '+') || (cur_char == '-') || (cur_char == '*') || (cur_char == '/');
}

bool FirstParser::is_digit() {
	return isdigit(cur_char);
}

bool FirstParser::is_alpha() {
	return isalpha(cur_char);
}

bool FirstParser::is_num() {
	return (cur_char == '.');
}
