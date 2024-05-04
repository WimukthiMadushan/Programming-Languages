#include <iostream>
#include <vector>
#include <string>

//! lambda: arg_str2 = arguments, arg_int1 = environment, arg_int2 = body
//! delta: arg_int1 = function_index
//! gamma: none
// operator: arg_str1 = operator
//! identifier: arg_str1 = arg_name
// integer: arg_int1 = value
//! list: arg_int3 = values
//! environment: arg_int1 = environment_value
//! beta: none
//! tau: arg_int1 = size
//! neta: 2 int and one string
// bool: arg_str1 = "True" or "False"

struct Env_node;

class Base // Each node in the control stack and the stack stack
{
public:
  string type = "None";

  string arg_str1 = "";
  vector<string> arg_str2 = {};

  int arg_int1 = -1;
  vector<int> arg_int2 = {};

  Env_node *env_node = nullptr;

  Base(string type) : type(type){};
  Base(string type, int arg_int1) : type(type), arg_int1(arg_int1){};    // Eg: integer
  Base(string type, string arg_str1) : type(type), arg_str1(arg_str1){}; // Eg: identifier
};

struct Env_node // Each node in the env storage
{
  vector<string> name = {};
  vector<Base *> value = {};
  Env_node *prev;

  Env_node(Env_node *prev) : prev(prev) {}
};

stack<Base *> control_stk;     // Working control stack
stack<Base *> stack_stk;       // Working stack stack
stack<Env_node *> parsing_env; // Stored environments

vector<vector<Base *>> control_structures; // Stores each function present in the syntax tree
