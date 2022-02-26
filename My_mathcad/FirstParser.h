#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <string>
#include <algorithm>
#include "FSM.h"
#include <any>
namespace fp {

	using tokens_t = std::vector<std::any>;
	using func_t = std::function<double(std::vector<double> const& args)>;

	struct NumConst{
		NumConst(double v) : val(v) {}
		NumConst(std::string const& v) : val(stod(v)) {}
		double val;
	};

	struct Variable{
		Variable(std::string const& name) : name(name) {}
		std::string name;
	};

	struct Function{
		Function(std::string const& name) : name(name) {}
		std::string name;
	};

	struct Sign{
		Sign(std::string const& name) : name(name) {}
		std::string name;
	};

	struct Separator{
		Separator(char symb) : symb(symb) {}
		char symb;
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
		void add_symb();
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

}