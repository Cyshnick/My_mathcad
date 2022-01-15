#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <string>
#include <algorithm>
#include "FSM.h"

namespace fp {

	struct AToken {
	protected:
		AToken() {};
		~AToken() {};
	};

	using tokens_t = std::vector<std::shared_ptr<AToken>>;
	using func_t = std::function<double(std::vector<double> const& args)>;

	struct NumConst : public AToken {
		NumConst(double v) : val(v) {}
		double val;
	};

	struct Variable : public AToken {
		Variable(std::string const& name) : name(name) {}
		std::string name;
	};

	struct Function : public AToken {
		Function(std::string const& name) : name(name) {}
		std::string name;
	};

	struct Sign : public AToken {
		Sign(std::string const& name) : name(name) {}
		std::string name;
	};

	struct Separator : public AToken{
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

}