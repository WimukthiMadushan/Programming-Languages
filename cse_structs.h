#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

// In built functions
void add_in_built_to_env(Base *env)
{
  // Defining internal variables
  //? env->children.push_back(new Base("identifier", "hundred", new Base("integer", 100)));

  // Defining inbuilt functions
  env->children.push_back(new Base("identifier", "Print", new Base("lambda", -1)));
  env->children.push_back(new Base("identifier", "print", new Base("lambda", -1)));
  env->children.push_back(new Base("identifier", "Isinteger", new Base("lambda", -2)));
  env->children.push_back(new Base("identifier", "Isstring", new Base("lambda", -3)));
  env->children.push_back(new Base("identifier", "Istuple", new Base("lambda", -4)));
  env->children.push_back(new Base("identifier", "Isfunction", new Base("lambda", -5)));
  env->children.push_back(new Base("identifier", "Isdummy", new Base("lambda", -6)));
  env->children.push_back(new Base("identifier", "Stem", new Base("lambda", -7)));
  env->children.push_back(new Base("identifier", "Stern", new Base("lambda", -8)));
  env->children.push_back(new Base("identifier", "Conc", new Base("lambda", -9)));
  env->children.push_back(new Base("identifier", "Order", new Base("lambda", -10)));
  env->children.push_back(new Base("identifier", "Null", new Base("lambda", -11)));
}

void print_Base(Base *env)
{
  if (env->type == "tuple")
  {
    cout << "(";
    if (env->children.size() > 0)
    {
      print_Base(env->children[0]);
    }
    for (int i = 1; i < env->children.size(); i++)
    {
      cout << ", ";
      print_Base(env->children[i]);
    }
    cout << ")";
  }
  else if (env->type == "integer")
  {
    cout << env->arg_int;
  }
  else if (env->type == "boolean")
  {
    cout << env->arg_str;
  }
  else if (env->type == "string")
  {
    cout << "\"" << env->arg_str << "\"";
  }
}

void in_built_functions(Base *func, Base *func_args)
{
  int val = func->arg_int;
  if (val == -1)
  {
    print_Base(func_args);
    cout << endl;
    stack_stk.push(new Base("dummy"));
  }
  else if (val == -2)
  {
    if (func_args->type == "integer")
    {
      stack_stk.push(new Base("boolean", "true"));
    }
    else
    {
      stack_stk.push(new Base("boolean", "false"));
    }
  }
  else if (val == -3)
  {
    if (func_args->type == "string")
    {
      stack_stk.push(new Base("boolean", "true"));
    }
    else
    {
      stack_stk.push(new Base("boolean", "false"));
    }
  }
  else if (val == -4)
  {
    if (func_args->type == "tuple")
    {
      stack_stk.push(new Base("boolean", "true"));
    }
    else
    {
      stack_stk.push(new Base("boolean", "false"));
    }
  }
  else if (val == -5)
  {
    if (func_args->type == "lambda")
    {
      stack_stk.push(new Base("boolean", "true"));
    }
    else
    {
      stack_stk.push(new Base("boolean", "false"));
    }
  }
  else if (val == -6)
  {
    if (func_args->type == "dummy")
    {
      stack_stk.push(new Base("boolean", "true"));
    }
    else
    {
      stack_stk.push(new Base("boolean", "false"));
    }
  }
  else if (val == -7)
  {
    if (func_args->type != "string")
    {
      cout << "Expect a string with Stem" << endl;
      throw "Error";
    }
    if (func_args->arg_str.size() == 0)
    {
      cout << "Expect a string atleast of size 1 with Stem" << endl;
      throw "Error";
    }
    stack_stk.push(new Base("string", func_args->arg_str.substr(0, 1)));
  }
  else if (val == -8)
  {
    if (func_args->type != "string")
    {
      cout << "Expect a string with Stern" << endl;
      throw "Error";
    }
    if (func_args->arg_str.size() == 0)
    {
      cout << "Expect a string atleast of size 1 with Stern" << endl;
      throw "Error";
    }
    stack_stk.push(new Base("string", func_args->arg_str.substr(1)));
  }
  else if (val == -9)
  {
    if (func_args->type != "string" || stack_stk.top()->type != "string")
    {
      cout << "Expect two strings with Conc" << endl;
      throw "Error";
    }
    Base *temp = stack_stk.top();
    control_stk.pop();
    stack_stk.pop();
    string output = func_args->arg_str + temp->arg_str;
    stack_stk.push(new Base("string", output));
  }
  else if (val == -10)
  {
    if (func_args->type != "tuple")
    {
      cout << "Expect a tuple with Order" << endl;
      throw "Error";
    }
    stack_stk.push(new Base("integer", func_args->children.size()));
  }
  else if (val == -11)
  {
    if (func_args->type != "tuple")
    {
      cout << "Expect a tuple with Null" << endl;
      throw "Error";
    }
    if (func_args->children.size() == 0)
    {
      stack_stk.push(new Base("boolean", "true"));
    }
    else
    {
      stack_stk.push(new Base("boolean", "false"));
    }
  }
}