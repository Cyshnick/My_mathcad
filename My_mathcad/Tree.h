#pragma once
#include <memory>
#include <vector>
#include <any>
namespace fp {

	class Tree {
		struct Vertex {
			Vertex() : parent(nullptr) {}
			Vertex(Vertex* parent, std::any const& data) :
				parent(parent), data(data) {
			}
			Vertex* parent;
			std::vector<Vertex*> childrens;
			std::any data;
		};
	public:

		Tree() : root(nullptr), cursor(nullptr) {}

		void add_child(std::any const& data) {
			Vertex* child = new Vertex(cursor, data);
			if (cursor) {
				cursor->childrens.push_back(child);
				cursor = child;
			}
			else {
				root = cursor = child;
			}
			_data.push_back(child);
		}

		void add_parent(std::any const& data) {
			Vertex* par = new Vertex(nullptr, data);
			if (root) {
				par->childrens.push_back(root);
				root->parent = par;
			}
			root = par;
			cursor = par;
			_data.push_back(par);
		}

		void add_tree(Tree const& tree) {
			if (!tree.root) {
				return;
			}
			auto subtree = new Vertex[tree._data.size()];
			Vertex* st_it = subtree;
			for (auto it : tree._data) {
				*st_it = *it;
				_data.push_back(st_it++);
			}
			st_it->parent = cursor;
			if (!root) {
				cursor = root = st_it;
			}

		}

		//void add_tree(Tree&& tree){}

		inline void change_data(std::any const& data) {
			cursor->data = data;
		}

		inline void goto_parent() {
			if (cursor != root) {
				cursor = cursor->parent;
			}
		}

		inline void goto_child(size_t i) {
			cursor = cursor->childrens.at(i);
		}

		inline void goto_root() {
			cursor = root;
		}

		//void goto_back();

		inline bool is_end() const {
			return cursor->childrens.empty();
		}

		inline bool is_root() const {
			return cursor == root;
		}

		inline std::any get() const {
			return cursor->data;
		}

		void clear(){
			for (auto &it : _data) {
				delete it;
				it = nullptr;
			}
			_data.clear();
			root = cursor = nullptr;
		}

		~Tree() {
			clear();
		}

	private:
		std::vector<Vertex*> _data;
		Vertex* root, * cursor;
	};
}

