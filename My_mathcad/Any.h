//#pragma once
//#include <memory>
//#include <typeinfo>
//#include <iostream>
//
//
//class __A__IValue {
//public:
//	virtual ~__A__IValue() {}
//
//	virtual size_t get_size() = 0;
//};
//
//template <class T>
//struct Keeper {
//	using KT = T;
//};
//
//template <class T>
//class __A__Value  : public __A__IValue{
//	T _value;
//public:
//	explicit __A__Value(T const& value) : _value(value) {}
//
//	size_t get_size() override {
//		return sizeof(T);
//	}
//
//	inline T const& get() const {
//		return _value;
//	}
//};
//
//class Any {
//	__A__IValue* _val;
//
//public:
//	template <class T>
//	Any(T const& value) {
//		_val = new __A__Value<T>(value);
//	}
//	
//	~Any() {
//		delete _val;
//	}
//
//	Any(Any const& obj)	{
//		size_t val_size = obj._val->get_size();
//		_val = reinterpret_cast<__A__IValue*>(malloc(val_size));
//		std::cout << (int)*((unsigned long*)obj._val) << std::endl;
//		std::cout << (int)*((unsigned long*)_val) << std::endl;
//		memcpy_s(_val, val_size, obj._val, val_size);
//		std::cout << (int)*((unsigned long*)obj._val) << std::endl;
//		std::cout << (int)*((unsigned long*)_val) << std::endl;
//	}
//
//	template <class T>
//	T get() const {
//		__A__Value<T>* val = dynamic_cast<__A__Value<T>*>(_val.get());
//		if (val) {
//			return val;
//		}
//
//		return T();
//	}
//};
//
