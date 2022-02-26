#pragma once
#include "FSM.h"
#include "FirstParser.h"
#include "Tree.h"
#include <iostream>
#include <functional> 

namespace fp {

	using func_t = std::function<double(std::vector<double> const& args)>;

	class Sign_info {
	public:
		Sign_info() :
			sign_list({ "+", "-", "*", "/", "^", "u-", "u+" }),
			func_list({ 
				[](std::vector<double> const& args) {return args.at(0) + args.at(1); },
				[](std::vector<double> const& args) {return args.at(0) - args.at(1); },
				[](std::vector<double> const& args) {return args.at(0) * args.at(1); },
				[](std::vector<double> const& args) {return args.at(0) / args.at(1); },
				[](std::vector<double> const& args) {return pow(args.at(0), args.at(1)); },
				[](std::vector<double> const& args) {return -args.at(0); },
				[](std::vector<double> const& args) {return args.at(0); }
				}) {	}

		static Sign_info const& get_instance() {
			static Sign_info si;
			return si;
		}

		func_t get_func(std::string const& sign) const {
			auto itf = find(sign_list.begin(), sign_list.end(), sign);
			if (itf == sign_list.end()) {
				throw "No such sign!";
			}
			return func_list.at(itf - sign_list.begin());
		}

		size_t get_prior(std::string const& sign) const{
			if ((sign == "+") || (sign == "-"))
				return 1;
			if ((sign == "*") || (sign == "/"))
				return 2;
			if ((sign == "^") || (sign == "u-") || (sign == "u+"))
				return 3;
			return 0;
		}

		bool cmp_prior(std::string const& sign1, std::string const& sign2) const {
			return get_prior(sign1) > get_prior(sign2);
		}

	private:
		std::vector<std::string> sign_list;
		std::vector<func_t> func_list;
	};

	class MainParser {
	public:
		MainParser();

		Tree const& parse(tokens_t const&);

	private:
		enum class States {
			START,
			PUA,
			UAP,
			OP,
			OB,
			FN
		};
		enum class Events {
			PUA,
			UAP,
			OP,
			OB,
			BA,
			FN,
			Empty
		};

		void to_pua();
		void to_pua_rep();
		void to_op();
		void to_ob();
		void to_fn();
		void to_uap();
		void to_uap_rep();
		void to_start();

		bool check_pua();
		bool check_uap();
		bool check_op();
		bool check_ob();
		bool check_ba();
		bool check_fn();

		FSM<States, Events> fsm;
		std::any cur_token;
		std::any last_sign;
		std::any first_op;
		std::any second_op;

		Tree ret;
		Tree subtree;
		size_t i;
	};

}

