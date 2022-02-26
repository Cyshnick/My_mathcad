#include "MainParser.h"

namespace fp {

	MainParser::MainParser() :
		fsm({
			{States::START, States::PUA, Events::PUA, [this]() {to_pua(); }},
			{States::START, States::OP, Events::OP, [this]() {to_op(); }},
			{States::START, States::OB, Events::OB, [this]() {to_ob(); }},
			{States::START, States::FN, Events::FN, [this]() {to_fn(); }},
			{States::PUA, States::PUA, Events::PUA, [this]() {to_pua_rep(); }},
			{States::PUA, States::OP, Events::OP, [this]() {to_op(); }},
			{States::PUA, States::OB, Events::OB, [this]() {to_ob(); }},
			{States::PUA, States::FN, Events::FN, [this]() {to_fn(); }},
			{States::OP, States::UAP, Events::UAP, [this]() {to_uap(); }},
			{States::OP, States::START, Events::BA, [this]() {to_start(); }},
			{States::OP, States::START, Events::PUA, [this]() {to_start(); }},
			{States::OB, States::UAP, Events::UAP, [this]() {to_uap(); }},
			{States::OB, States::START, Events::BA, [this]() {to_start(); }},
			{States::OB, States::START, Events::PUA, [this]() {to_start(); }},
			{States::FN, States::UAP, Events::UAP, [this]() {to_uap(); }},
			{States::FN, States::START, Events::BA, [this]() {to_start(); }},
			{States::FN, States::START, Events::PUA, [this]() {to_start(); }},
			{States::UAP, States::UAP, Events::UAP, [this]() {to_uap_rep(); }},
			{States::UAP, States::START, Events::BA, [this]() {to_start(); }},
			{States::UAP, States::START, Events::PUA, [this]() {to_start(); }}
			})
	{
		
	}

	Tree const& MainParser::parse(tokens_t const& toks) {
		for (i = 0; i < toks.size(); i++) {
			Events ev = Events::Empty;
			cur_token = toks[i];
			if (check_ba())
				ev = Events::BA;
			else if (check_fn())
				ev = Events::FN;
			else if (check_ob())
				ev = Events::OB;
			else if (check_op())
				ev = Events::OP;
			else if (check_pua())
				ev = Events::PUA;
			else if (check_uap())
				ev = Events::UAP;
			fsm.process(ev);
		}
		ret.goto_parent();
		return ret;
	}

	void MainParser::to_pua() {

	}

	void MainParser::to_pua_rep() {
	}

	void MainParser::to_op() {
		if (!first_op.has_value()) {
			first_op = cur_token;
		}
		else if (!second_op.has_value()) {
			second_op = cur_token;
		}
	}

	void MainParser::to_ob() {
	}

	void MainParser::to_fn() {
	}

	void MainParser::to_uap() {
	}

	void MainParser::to_uap_rep() {
	}

	void MainParser::to_start() {
		if (!last_sign.has_value()) {
			last_sign = cur_token;
			Sign ls = std::any_cast<Sign>(last_sign);
			ret.add_child(Sign_info::get_instance().get_func(ls.name));

			if (first_op.type() == typeid(Variable)) {
				Variable fo = std::any_cast<Variable>(first_op);
				ret.add_child(fo.name);
			}
			else {
				NumConst fo = std::any_cast<NumConst>(first_op);
				ret.add_child(fo.val);
			}
			ret.goto_parent();
		}
		else {
			Sign s = std::any_cast<Sign>(cur_token);
			Sign ls = std::any_cast<Sign>(last_sign);
			if (Sign_info::get_instance().cmp_prior(s.name, ls.name)) {
				ret.add_child(s.name);
				if (second_op.type() == typeid(Variable)) {
					Variable so = std::any_cast<Variable>(second_op);
					ret.add_child(so.name);
				}
				else {
					NumConst so = std::any_cast<NumConst>(second_op);
					ret.add_child(so.val);
				}
				ret.goto_parent();
			}
			else {
				ret.add_parent(s.name);
				if (second_op.type() == typeid(Variable)) {
					Variable so = std::any_cast<Variable>(second_op);
					ret.add_child(so.name);
				}
				else {
					NumConst so = std::any_cast<NumConst>(second_op);
					ret.add_child(so.val);
				}
				ret.goto_parent();
			}
			last_sign = cur_token;
			second_op = std::any();
		}
	}

	bool MainParser::check_pua() {
		auto p = std::any_cast<Sign>(&cur_token);
		if (!p)
			return false;
		return (p->name == "+") || (p->name == "-");
	}

	bool MainParser::check_uap() {
		auto p = std::any_cast<Sign>(&cur_token);
		if (!p)
			return false;
		return p->name == "!";
	}

	bool MainParser::check_op() {
		if (!std::any_cast<Variable>(&cur_token))
			if (!std::any_cast<NumConst>(&cur_token))
				return false;
		return true;
	}

	bool MainParser::check_ob() {
		auto p = std::any_cast<Separator>(&cur_token);
		if (!p)
			return false;
		return p->symb == '(';
	}

	bool MainParser::check_ba() {
		auto p = std::any_cast<Sign>(&cur_token);
		if (!p)
			return false;
		auto name = p->name;
		return (name == "+") || (name == "-") || (name == "/") ||
			(name == "*") || (name == "^");
	}

	bool MainParser::check_fn() {
		return std::any_cast<Function>(&cur_token) != nullptr;
	}

}