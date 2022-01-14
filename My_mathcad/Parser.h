#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <string>
#include <algorithm>
#include "FSM.h"

class AToken
{
protected:
	AToken() {};
	~AToken() {};
};

using tokens_t = std::vector<std::shared_ptr<AToken>>;
using func_t = std::function<double(std::vector<double> const& args)>;

class Operand : public AToken{
};


class Action : public AToken {
};

class FirstParser {
public:
	FirstParser();
	~FirstParser() {}

	tokens_t parse(std::string const& inp);

private:
	void add_sep();
	void add_sign();
	void start_symb();
	void start_const();
	void add_symb();
	void add_const();
	void end_symb();
	void end_const();
	void err_handler();

	bool is_sep();
	bool is_sign();
	bool is_digit();
	bool is_alpha();
	bool is_num();

private:
	enum class States {
		START,
		CONST,
		SYMB,
		ERROR
	};

	enum class Events {
		ISSEP,
		ISSIGN,
		ISDIGIT,
		ISALPHA,
		ISNUM,
		ELSE
	};

	std::string temp;
	char cur_char;
	FSM<States, Events> fsm;
	tokens_t ret;
};

class std_actions{
private:
	std_actions() {
		str_acts = {
			"+",
			"-",
			"*",
			"/",
			"^",
			"!"
		};
		str_funcs = {
			"sin",
			"cos",
			"tg",
			"ctg",
			"asin",
			"asin",
			"acos",
			"atg",
			"actg",
			"ln",
			"log",
			"lg",
			"exp"
		};
	}

	std_actions(std_actions const&) {}
	std_actions& operator=(std_actions&) {}
public:
	std_actions& getInst() {
		static std_actions instance;
		return instance;
	}

private:
	std::vector<std::string> str_acts;
	std::vector<std::string> str_funcs;
};