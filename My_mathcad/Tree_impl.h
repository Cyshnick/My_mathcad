//#pragma once
//#include <iostream>
//#include <memory>
//#include <list>
//#include <functional>
//#include <cmath>
//#include <vector>
//#include <exception>
//#include <algorithm>
//
//namespace ct
//{
//	/*
//	Как работать с деревом?
//	Есть только два вида узлов - с операциями и с операндами.
//	Операция хранит функтор, его можно задать из класса std_lambda, можно написать самому
//	Операнд - хранит переменную типа T. 
//	Для добавления узлов есть следующие функции класса tree:
//	add_child: добавляет потомка к текущему узлу, и делает текущим узел с потомком
//	add_parent: добавляет предка к корневому узлу и делает добавленный узел текущим
//	set_node: задает текущий узел.
//	add_tree: добавляет новое дерево к текущему узлу. Положение текущего узла не меняет
//	Для навигации и перемещения есть следующие функции:
//	goto_parent: Переещается к первому потомку текущего узла
//	keep_current_loc: Сохраняет текущее положение, и возвращает ключ
//	goto_loc: Перемещает текущий узел в узел с указанным ключом
//	goto_loc_er: То же самое, только узел стирается из памяти, ключ перестает работать 
//	
//	Функция calc выполняет вычисление графа.
//	Пример кода:
//
//		ct::tree<T> tree;
//
//		tree.add_child(ct::std_lambda<T>::get(ct::std_lambda<T>::POW));
//		tree.add_child(3);
//		tree.goto_parrent();
//		tree.add_child(ct::std_lambda<T>::get(ct::std_lambda<T>::SUB));
//		tree.add_child(15);
//		tree.goto_parrent();
//		tree.add_child(11);
//		tree.add_parent(ct::std_lambda<T>::get(ct::std_lambda<T>::DIV));
//		tree.add_child(9);
//		cout << tree.calc() << endl;
//		
//	*/
//	using key_t = size_t;
//
//	template <class T>
//	class __T__tree_node
//	{
//	public:
//		__T__tree_node(std::shared_ptr<__T__tree_node <T> > parent) :
//			parent(parent)
//		{	}
//
//		void set_parent(std::shared_ptr<__T__tree_node <T> > parent)
//		{
//			this->parent = parent;
//		}
//
//		virtual T calc() = 0;
//
//		std::shared_ptr<__T__tree_node <T> > get_parent() const noexcept
//		{
//			return parent;
//		}
//
//		std::shared_ptr<__T__tree_node <T> > get_parent()
//		{
//			return parent;
//		}
//
//		virtual ~__T__tree_node() {}
//
//	protected:
//		std::shared_ptr<__T__tree_node <T> > parent;
//	};
//
//	template <class T>
//	using __T__TN_ptr = std::shared_ptr<__T__tree_node<T> >;
//
//	template <class T>
//	class __T__TN_data : public __T__tree_node<T>
//	{
//	public:
//
//		__T__TN_data(__T__TN_ptr<T> parent, T value) :
//			__T__tree_node<T>(parent), value(value)
//		{	}
//
//		virtual T calc() override
//		{
//			//std::cout << "calc data" << std::endl;
//			return value;
//		}
//
//		virtual ~__T__TN_data() {}
//	protected:
//		T value;
//	};
//
//	template <class T>
//	class __T__TN_oper : public __T__tree_node<T>
//	{
//	public:
//		__T__TN_oper(__T__TN_ptr<T> parent, std::function<T(std::vector<__T__TN_ptr<T> >const&)>  calc_func) :
//			__T__tree_node<T>(parent), calc_func(calc_func)
//		{	}
//
//		virtual T calc() override
//		{
//			//std::cout << "calc oper" << std::endl;
//			T res;
//			try
//			{
//				res = calc_func(childs);
//			}
//			catch (std::out_of_range const& e)
//			{
//				// Todo: out_of_range exception
//				std::cout << "Too few arguments!" << std::endl;
//				throw "Too few arguments";
//			}
//
//			return res;
//		}
//
//		void add_child(__T__TN_ptr<T> val)
//		{
//			childs.push_back(val);
//		}
//
//		virtual ~__T__TN_oper() {}
//	protected:
//		std::function<T(std::vector<__T__TN_ptr<T> >const&)> calc_func;
//		std::vector<__T__TN_ptr<T> > childs;
//	};
//
//	template <class T>
//	using __T__TN_list = std::vector<__T__TN_ptr<T> >;
//
//	template <class T>
//	using __T__TN_func = std::function<T(__T__TN_list<T> const&)>;
//
//	template <class T>
//	using list_t = std::vector<T>;
//
//	template <class T>
//	using func_t = std::function<T(list_t<T> const&)>;
//
//	template <class T>
//	class __T__tree_loc_keeper
//	{
//	public:
//
//		key_t push_loc(__T__TN_ptr<T> const& loc)
//		{
//			key_t k = locations.size();
//			locations.push_back(loc);
//			return k;
//		}
//
//		__T__TN_ptr<T> pop_loc(key_t key)
//		{
//			auto ret = locations.at(key);
//			locations.erase(locations.begin() + key);
//			return ret;
//		}
//
//		__T__TN_ptr<T> read_loc(key_t key) const
//		{
//			return locations.at(key);
//		}
//	private:
//		__T__TN_list<T> locations;
//	};
//
//	template <class T>
//	class tree
//	{
//	public:
//		tree()
//		{
//			root = current_node = nullptr;
//		}
//
//		void goto_parrent()
//		{
//			if (current_node == root)
//			{
//				throw "Unable to go to parent, current location - root";
//			}
//			current_node = current_node->get_parent();
//		}
//
//		// Создает потомка и передвигает курсор на него
//		void add_child(T val)
//		{
//			__T__TN_ptr<T> ptr = __T__TN_ptr<T>(new __T__TN_data<T>(current_node, val));
//			add_child(ptr);
//		}
//
//		// Создает потомка и передвигает курсор на него
//		void add_child(func_t<T> func)
//		{
//			auto F = [func](__T__TN_list<T> const& args) {
//				list_t<T> arg_t;
//				for (auto const& it : args)
//				{
//					arg_t.push_back(it->calc());
//				}
//				return func(arg_t);
//			};
//
//			__T__TN_ptr<T> ptr = __T__TN_ptr<T>(new __T__TN_oper<T>(current_node, F));
//			add_child(ptr);
//		}
//
//		// Задает значение текущего положения курсора. Курсор не передвигает
//		void set_node(T val)
//		{
//			__T__TN_ptr<T> parent = current_node ? current_node->get_parent() : nullptr;
//			__T__TN_ptr<T> ptr = __T__TN_ptr<T>(new __T__TN_data<T>(parent, val));
//			write(ptr);
//		}
//
//		// Задает значение текущего положения курсора. Курсор не передвигает
//		void set_node(func_t<T> func)
//		{
//			auto F = [func](__T__TN_list<T> const& args) {
//				list_t<T> arg_t;
//				for (auto const& it : args)
//				{
//					arg_t.push_back(it->calc());
//				}
//				return func(arg_t);
//			};
//			__T__TN_ptr<T> parent = current_node ? current_node->get_parent() : nullptr;
//			__T__TN_ptr<T> ptr = __T__TN_ptr<T>(new __T__TN_oper<T>(parent, F));
//			write(ptr);
//		}
//
//		T calc()
//		{
//			return root->calc();
//		}
//
//		// Добавляет родителя к корневому узлу 
//		// Корневой узел добавляется первым потомком
//		void add_parent(func_t<T> func)
//		{
//			auto F = [func](__T__TN_list<T> const& args) {
//				list_t<T> arg_t;
//				for (auto const& it : args)
//				{
//					arg_t.push_back(it->calc());
//				}
//				return func(arg_t);
//			};
//			__T__TN_oper<T>* ptr_oper = new __T__TN_oper<T>(nullptr, F);
//
//			// Это если еще нет узлов подключеных
//			if (!root)
//			{
//				write(__T__TN_ptr<T>(ptr_oper));
//				return;
//			}
//			ptr_oper->add_child(root);
//			__T__TN_ptr<T> ptr = __T__TN_ptr<T>(ptr_oper);
//			root->set_parent(ptr);
//			root = __T__TN_ptr<T>(ptr);
//			current_node = __T__TN_ptr<T>(root);
//		}
//
//		// Добавляет новое дерево в качестве потомка к текущему узлу
//		void add_tree(tree<T>const& tr)
//		{
//			if (tr.root)
//			{
//				auto temp = __T__TN_ptr<T>(current_node);
//				add_child(tr.root);
//				current_node = __T__TN_ptr<T>(temp);
//			}
//			else
//			{
//				// Todo: exception
//				throw "Tree is empty!";
//			}
//		}
//
//		// Сохранить текущее положение
//		key_t keep_current_loc()
//		{
//			return keeper.push_loc(current_node);
//		}
//
//		// Вернуться к сохраненному узлу, удалив ключ из памяти
//		void goto_loc_er(key_t key_loc)
//		{
//			current_node = keeper.pop_loc(key_loc);
//		}
//
//		// Вернуться к сохраненному узлу, не удаляя ключ
//		void goto_loc(key_t key_loc)
//		{
//			current_node = keeper.read_loc(key_loc);
//		}
//
//
//	private:
//		void add_child(__T__TN_ptr<T> val)
//		{
//			if (!root)
//			{
//				write(val);
//				return;
//			}
//
//			auto el = dynamic_cast<__T__TN_oper<T>*>(current_node.get());
//			if (el)
//			{
//				el->add_child(val);
//			}
//			else
//			{
//				// Todo: Exception system
//				throw "Do not add element to TN_value";
//			}
//			current_node = __T__TN_ptr<T>(val);
//		}
//
//		void write(__T__TN_ptr<T> el)
//		{
//			current_node = __T__TN_ptr<T>(el);
//			if (!root)
//				root = __T__TN_ptr<T>(current_node);
//		}
//
//	private:
//		__T__TN_ptr<T> root;
//		__T__TN_ptr<T> current_node;
//		__T__tree_loc_keeper<T> keeper;
//	};
//
//	template <class T>
//	class std_lambda
//	{
//	public:
//		enum Operations {
//			ADD,
//			SUB,
//			MUL,
//			DIV,
//			POW,
//			LOG,
//			LOG2,
//			LN,
//			LG,
//			EXP,
//			SIN,
//			COS,
//			TAN,
//			CTAN,
//			SH,
//			CH,
//			TH,
//			ASIN,
//			ACOS,
//			ATAN,
//			ACTAN,
//			H,
//			ABS,
//			FACT,
//			EMPTY
//		};
//
//		static func_t<T> get(Operations op)
//		{
//			switch (op)
//			{
//			case ADD:
//				return [](list_t<T> const& arg) {
//					return arg.at(0) + arg.at(1);
//				};
//				break;
//			case SUB:
//				return [](list_t<T> const& arg) {
//					return arg.at(0) - arg.at(1);
//				};
//				break;
//			case MUL:
//				return [](list_t<T> const& arg) {
//					return arg.at(0) * arg.at(1);
//				};
//				break;
//			case DIV:
//				return [](list_t<T> const& arg) {
//					return arg.at(0) / arg.at(1);
//				};
//				break;
//			case POW:
//				return [](list_t<T> const& arg) {
//					return (T)powl(arg.at(0), arg.at(1));
//				};
//				break;
//			case LOG:
//				return [](list_t<T> const& arg) {
//					return (T)(logl(arg.at(0)) / logl(arg.at(1)));
//				};
//				break;
//			case LOG2:
//				return [](list_t<T> const& arg) {
//					return (T)log2l(arg.at(0));
//				};
//				break;
//			case LN:
//				return [](list_t<T> const& arg) {
//					return (T)logl(arg.at(0));
//				};
//				break;
//			case LG:
//				return [](list_t<T> const& arg) {
//					return (T)log10l(arg.at(0));
//				};
//				break;
//			case EXP:
//				return [](list_t<T> const& arg) {
//					return (T)expl(arg.at(0));
//				};
//				break;
//			case SIN:
//				return [](list_t<T> const& arg) {
//					return (T)sinl(arg.at(0));
//				};
//				break;
//			case COS:
//				return [](list_t<T> const& arg) {
//					return (T)cosl(arg.at(0));
//				};
//				break;
//			case TAN:
//				return [](list_t<T> const& arg) {
//					return (T)tanl(arg.at(0));
//				};
//				break;
//			case CTAN:
//				return [](list_t<T> const& arg) {
//					return (T)((T)1. / tanl(arg.at(0)));
//						};
//				break;
//			case SH:
//				return [](list_t<T> const& arg) {
//					return (T)sinhl(arg.at(0));
//				};
//				break;
//			case CH:
//				return [](list_t<T> const& arg) {
//					return (T)coshl(arg.at(0));
//				};
//				break;
//			case TH:
//				return [](list_t<T> const& arg) {
//					return (T)tanhl(arg.at(0));
//				};
//				break;
//			case ASIN:
//				return [](list_t<T> const& arg) {
//					return (T)asinl(arg.at(0));
//				};
//				break;
//			case ACOS:
//				return [](list_t<T> const& arg) {
//					return (T)acosl(arg.at(0));
//				};
//				break;
//			case ATAN:
//				return [](list_t<T> const& arg) {
//					return (T)atanl(arg.at(0));
//				};
//				break;
//			case ACTAN:
//				return [](list_t<T> const& arg) {
//					return (T)(3.14159265358979323846 / 2 - atanl(arg.at(0)));
//				};
//				break;
//			case H:
//				return [](list_t<T> const& arg) {
//					return (T)(arg.at(0) < 0 ? 0 : 1);
//				};
//				break;
//			case ABS:
//				return [](list_t<T> const& arg) {
//					return (T)fabsl(arg.at(0));
//				};
//				break;
//			case FACT:
//				return [](list_t<T> const& arg) {
//					T res = 1;
//					for (size_t i = 1; i < arg.at(0) + 1; i++)
//						res *= i;
//					return  res;
//				};
//				break;
//			default:
//				//Todo: exception
//				throw "Wrong operation!";
//			}
//		}
//	};
//
//}