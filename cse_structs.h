#include <iostream>
#include <vector>
#include <string>

class Base // Each node in the control stack and the stack stack
{
public:
  string type;

public:
  Base(string t) : type(t){};
};

class Env_node // Each node in the env storage
{
  vector<string> name;
  vector<Base> value;
  Env_node *prev;
};

stack<Base *> control_stk; // Working control stack
stack<Base *> stack_stk;   // Working stack stack
vector<Env_node *> env;    // Stored environments

vector<vector<Base *>> control_structures; // Stores each function present in the syntax tree

//! Different Base types
class Integer : public Base
{
public:
  int value;
  Integer(int value) : Base("integer"), value(value){};
};

class Operator : public Base
{
public:
  string op;
  Operator(string op) : Base("operator"), op(op){};
};

class Environment : public Base
{
public:
  int env_number;
  Environment(int env_number) : Base("environment"), env_number(env_number){};
};

class Identifier : public Base
{
public:
  string name;
  Identifier(string name) : Base("identifier"), name(name){};
};

class String : public Base
{
public:
  string value;
  String(string value) : Base("string"), value(value) {}
};

class Lambda : public Base
{
public:
  vector<string> bound;
  int base = -1;
  int env = -1;
};

//! check these

class Boolean : public Base
{
};

class Delta : public Base
{
};

class Gamma : public Base
{
};

class Result : public Base
{
};

class Beta : public Base
{
};

class Tau : public Base
{
};

class eta : public Base
{
};