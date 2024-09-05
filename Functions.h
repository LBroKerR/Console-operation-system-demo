#pragma once
class Functions
{
	void (*functions)(void*);

public:
	// storing a function location!
	Functions(void (*function)(void*)) : functions(function) {}
	Functions() :functions(nullptr) {}
	~Functions() {}

	// return the stored function!
	void (*getFunc())(void*) {
		return functions;
	}
	//save the function
	void setFunc(void (*function)(void*)) {
		functions = function;
	}
};

