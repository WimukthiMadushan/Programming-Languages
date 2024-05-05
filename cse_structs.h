#include <iostream>
#include <vector>
#include <string>

// lambda: arg_str2 = arguments, arg_int = environment, arg_int2 = body
// delta: arg_int = function_index
// gamma: none
// operator: arg_str = operator
// identifier: arg_str = arg_name
// integer: arg_int = value
// list: arg_int3 = values
// environment: arg_int = environment_value
// beta: none
// tau: arg_int = size
// eta: 2 int and one string
// ystar: 0
// bool: arg_str = "True" or "False"

// string:
// tuple:
// integer:
// boolean:
// function:
// dummy: Eg. actual value of each print() output

class Base // Each node in the control stack and the stack stack
{
public:
  string type = "none";

  string arg_str = "";
  int arg_int;

  Base *prev = nullptr;
  vector<Base *> children = {};

  // Constructors
  Base(string type) : type(type){};
  Base(string type, int arg_int) : type(type), arg_int(arg_int){};    // Eg: integer
  Base(string type, string arg_str) : type(type), arg_str(arg_str){}; // Eg: identifier
  Base(string type, string arg_str, int arg_int) : type(type), arg_str(arg_str), arg_int(arg_int){};
  Base(string type, string arg_str, Base *prev) : type(type), arg_str(arg_str), prev(prev){};
  Base(string type, Base *prev) : type(type), prev(prev){};
};

stack<Base *> control_stk; // Working control stack
stack<Base *> stack_stk;   // Working stack stack
stack<Base *> parsing_env; // Stored environments

vector<vector<Base *>> control_structures; // Stores each function present in the syntax tree
