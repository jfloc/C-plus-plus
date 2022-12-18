#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

//Modified CallProcedure to include string input

void CallProcedureParamIn(string pName, string pIn)
{
	PyObject* pValue, * presult;

	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	char* paramIn = new char[pIn.length() + 1];
	std::strcpy(paramIn, pIn.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);

	if (PyCallable_Check(my_function))
	{
		pValue = Py_BuildValue("(z)", paramIn);
		PyErr_Print();
		presult = PyObject_CallObject(my_function, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}

	Py_Finalize();

	delete[] procname;
	delete[] paramIn;

}

//gets a boolean returned from either 1 or not 1
bool ValidStringInput(string t_func_name, string t_input) {
	int answer;
	bool isValid;
	answer = callIntFunc(t_func_name, t_input); // Value returned from python is 1 if True is returned else if False is return 0 is the value
	answer == 1 ? isValid = true: isValid = false; 
	// cout << (answer); used cout to test the return value of answer

	return isValid;

}

// Valid input helper function
bool ValidInput(string t_input) {
	try {
		int x = stoi(t_input);
		return true;
	}
	catch (...) {
		cin.clear();
		cin.ignore();
		cout << "Not an integer. Try again!" << endl;
		return false;
	}

}

// Validate the options 1-4 are chosen

int ValidateInput() {
	int optionInput = -1;
	string optionNum = "-";
	while (optionInput > 4 || optionInput < 1) {

		cin >> optionNum;

		while (!ValidInput(optionNum)) {
			cin >> optionNum;
		}

		optionInput = stoi(optionNum);

		if (optionInput > 4 || optionInput < 1) {
			cout << " Enter 1, 2, 3 or 4." << endl;
		}

	}
	return optionInput;
}

void DisplayMenu() {
	cout << "Choose from the menu\n" << endl;
	cout << "1. Display all produce sales\n" <<
		"2. Check a produce sell count\n" <<
		"3. View produce total sales graph\n" <<
		"4. Exit\n" << endl;
}

void PythonCodeConnect(string procName) {
	string itemIn;
	int a;

	if (procName == "print_menu_count") {
		cout << endl;
		CallProcedure("print_menu_count");
		cout << endl;
	}
	else if(procName =="print_item_count") {

		cout << "Enter a item to get the count" << endl;
		cin >> itemIn;

		/*
		* Ensures the user inputs a valid product from the list through ValidStringInput helper function clearing the buffer each time
		*/
		while (!ValidStringInput("get_is_valid", itemIn)) {
			cout << "Not valid item try again!" << endl;
			cin.clear();
			cin.ignore();
			cin >> itemIn;
		}
		// The value of returned is the amount from the itemIn which is assured to have a product as it is checked before passing in to the function
		a = callIntFunc("get_item_count", itemIn);
		cout << "Count of item is " << a << "\n" << endl;
	}
	else if (procName == "print_graph") {
		CallProcedure(procName);
	}

}

/*
* Code to perform menu switch options passing the name of function in python to parameter in PythonCodeConnect function
*/
void PerformMenuAction(int t_optionIn) {

	switch (t_optionIn) {
	case 1:
		PythonCodeConnect("print_menu_count");
		break;
	case 2:
		PythonCodeConnect("print_item_count");
		break;
	case 3:
		PythonCodeConnect("print_graph");
		break;
	}

}

/*
* Updated the call procedure method to include four cases each for the requirements
*/
void main()
{
	CallProcedure("create_grocery_list");
	//CallProcedure("print_menu_count");
	int inputOption = -1;
	while (inputOption != 4) {
		DisplayMenu();
		inputOption = ValidateInput();
		switch (inputOption) {
		case 1: case 2: case 3:
			PerformMenuAction(inputOption);
			break;
		case 4:
			cout << "Goodbye!" << endl;
			break;
		}
	}
}