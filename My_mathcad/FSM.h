#pragma once
#include <functional>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <algorithm>

using void_f = std::function<void(void)>;
#define empty_action [](){}
template <class State, class Event>
class FSM {
public:

	struct jt_l {
		State cur_state;
		State next_state;
		Event ev;
		void_f act;
	};

	explicit FSM(std::initializer_list<jt_l> const& base_list)
	{
		for (auto const& l : base_list) {
			auto itf = std::find_if(jump_table.begin(), jump_table.end(),
				[l](jt_l_m line) {
					return line.cur_state == l.cur_state;
				});
			if (itf != jump_table.end()) {
				itf->events.push_back(l.ev);
				itf->actions.push_back(l.act);
			}
			else {
				jump_table.push_back(jt_l_m(l.cur_state, l.ev, l.act));
			}
		}
		for (auto const& l : base_list) {
			auto itf_s0 = std::find_if(jump_table.begin(), jump_table.end(),
				[l](jt_l_m line) {
					return line.cur_state == l.cur_state;
				});
			auto itf_s1 = std::find_if(jump_table.cbegin(), jump_table.cend(),
				[l](jt_l_m line) {
					return line.cur_state == l.next_state;
				});
			if (itf_s1 == jump_table.end()) {
				throw "Dead end found in jump table!";
			}
			itf_s0->next_states.push_back(itf_s1);
		}
		cur_line = jump_table.cbegin();
	}

	void process(Event e) {
		auto itf = std::find(cur_line->events.cbegin(), cur_line->events.cend(), e);
		if (itf != cur_line->events.cend()) {
			size_t i = itf - cur_line->events.begin();
			cur_line->actions.at(i)();
			cur_line = cur_line->next_states.at(i);
		}
	}
	
	inline State get_cur_state() const{
		return cur_line->cur_state;
	}

	inline void reset() {
		cur_line = jump_table.cbegin();
	}

private:

	struct jt_l_m {
		jt_l_m(State cur_state, Event ev, void_f act) : cur_state(cur_state)	{
			events.push_back(ev);
			actions.push_back(act);
		}
		State cur_state;
		std::vector<typename std::vector<jt_l_m>::const_iterator> next_states;
		std::vector<Event> events;
		std::vector<void_f> actions;
	};

	std::vector<jt_l_m> jump_table;
	typename std::vector<jt_l_m>::const_iterator cur_line;
};

