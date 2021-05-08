// github.com/A3st76/mysql_crypto. Source file under MIT license.

#pragma once

#include <functional>

class Delegate {
public:

	Delegate() {

	}

	template<class C>
	void bind(C* instance, void(C::*func)()) {
		m_callback = [instance, func]() -> void { (instance->*func)(); };
	}

	void call() {
		m_callback();
	}

private:

	std::function<void()> m_callback;
};