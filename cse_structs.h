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
  int value;

public:
  Integer(int value) : Base("integer"), value(value){};
};

class Operator : public Base
{
  string op;

public:
  Operator(string op) : Base("operator"), op(op){};
};

class Environment : public Base
{
  int env_number;

public:
  Environment(int env_number) : Base("environment"), env_number(env_number){};
};

class Identifier : public Base
{
  string name;

public:
  Identifier(string name) : Base("identifier"), name(name){};
};

class String : public Base
{
  string value;

public:
  String(string value) : Base("string"), value(value) {}
};

//! check these
class Lambda : public Base
{
  vector<string> bound;
  int base;
  int env;
};

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