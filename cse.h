#include <iostream>
#include <vector>
#include <string>

#include "cse_structs.h"

int env_count = 0;

void pre_order_traversal(Node *root, int environment)
{
  // Creating the control structures
  if (isOp(root->token))
  {
    Operator *op = new Operator(root->token);
    control_structures[environment].push_back(op);
  }
  else if (root->token[0] == '<')
  {
    string typ = root->token.substr(0, 3);
    if (typ == "<ID")
    {
      string str = root->token.substr(4, root->token.length() - 5);
      control_structures[environment].push_back(new Identifier(str));
    }
    else if (typ == "<IN")
    {
      string str = root->token.substr(5, root->token.length() - 6);
      control_structures[environment].push_back(new Integer(stoi(str)));
    }
    else if (typ == "<ST")
    {
      string str = root->token.substr(5, root->token.length() - 6);
      control_structures[environment].push_back(new String(str));
    }
  }

  // Traversing through the tree, with environment values
  if (root->token == "lambda")
  {
    pre_order_traversal(root->children[0], environment);
    control_structures.push_back(vector<Base *>());
    pre_order_traversal(root->children[1], ++env_count);
  }
  else
  {
    for (int i = 0; i < root->children.size(); i++)
    {
      pre_order_traversal(root->children[i], environment);
    }
  }
}

void add_env_to_control(int number)
{
  Environment *temp_env = new Environment(number);
  control_stk.push(temp_env);
  stack_stk.push(temp_env);
  for (int i = 0; i < control_structures[number].size(); i++)
  {
    control_stk.push(control_structures[number][i]);
  }
}

void evaluate()
{
  add_env_to_control(0);
  while (control_stk.size() != 1)
  {
    string the_type = control_stk.top()->type;
    if (the_type == "integer")
    {
      stack_stk.push(control_stk.top());
      control_stk.pop();
    }
    if (the_type == "operator")
    {
      int a = dynamic_cast<Integer *>(stack_stk.top())->value;
      stack_stk.pop();
      int b = dynamic_cast<Integer *>(stack_stk.top())->value;
      stack_stk.pop();
      string op = control_stk.top()->op;
      control_stk.pop();
      if (op == "+")
      {
        stack_stk.push(new Integer(a + b));
      }
      else if (op == "-")
      {
        stack_stk.push(new Integer(a - b));
      }
      else if (op == "*")
      {
        stack_stk.push(new Integer(a * b));
      }
      else if (op == "/")
      {
        stack_stk.push(new Integer(a / b));
      }
      else if (op == "**")
      {
        stack_stk.push(new Integer(pow(a, b)));
      }
      else
      {
        cout << "operator " << op << " not found" << endl;
        throw "Error";
      }
    }
  }
  // while (stack_stk.size() != 1)
  // {
  //   stack_stk.pop();
  //   // cout << stack_stk.top()->type << endl; // Output something
  // }
  cout << "Exited" << endl;
  cout << stack_stk.pop()->value << endl;
  if (stack_stk.top() == control_stk.top())
  {
    cout << "Code Successful" << endl;
    return;
  }
  else
  {
    throw "Error";
  }
}

void cse()
{
  cout << "Hello, I'm CSE!" << endl;
  control_structures.push_back(vector<Base *>());
  pre_order_traversal(ast_bu.top(), 0);
  cout << control_structures[0].size() << endl;
  evaluate();
}
