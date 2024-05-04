#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "cse_structs.h"

int env_count = 0;

void pre_order_traversal(Node *root, int environment);  // Traverse  through the tree.
void add_env_to_control(int number);                    // Add a funciton to the control stack.
void add_token_to_control(Node *root, int environment); // Add a nodes to control structures.
void evaluate();                                        // Evaluate the control stack.
void rules(string);

void cse()
{
  cout << "Hello, I'm CSE!" << endl;
  control_structures.push_back(vector<Base *>());
  pre_order_traversal(ast_bu.top(), 0);
  // evaluate();
}

void pre_order_traversal(Node *root, int environment)
// Traverse through the tree and create arrays of control structures
{
  if (root->token == "lambda")
  {
    Base *lambda = new Base("lambda", ++env_count);
    control_structures.push_back(vector<Base *>());
    pre_order_traversal(root->children[1], env_count);
    if (root->children[1]->token != ",")
    {
      lambda->arg_str2.push_back(root->children[1]->token);
    }
    else
    {
      for (int i = 0; i < root->children[1]->children.size(); i++)
      {
        lambda->arg_str2.push_back(root->children[1]->children[i]->token);
      }
    }
    control_structures[environment].push_back(lambda);
  }
  else if (root->token == "->")
  {
    control_structures[environment].push_back(new Base("delta", ++env_count));
    control_structures.push_back(vector<Base *>());
    pre_order_traversal(root->children[1], env_count);

    control_structures[environment].push_back(new Base("delta", ++env_count));
    control_structures.push_back(vector<Base *>());
    pre_order_traversal(root->children[2], env_count);

    control_structures[environment].push_back(new Base("beta"));

    pre_order_traversal(root->children[0], environment);
  }
  else
  {
    add_token_to_control(root, environment);
    for (int i = 0; i < root->children.size(); i++)
    {
      pre_order_traversal(root->children[i], environment);
    }
  }
}

void add_token_to_control(Node *root, int environment)
{
  cout << root->token << " " << environment << endl;
  if (root->token[0] == '<')
  {
    if (root->token[1] == 'I')
    {
      if (root->token[2] == 'N')
      {
        // this is a number
        int num = stoi(root->token.substr(5, root->token.length() - 6));
        control_structures[environment].push_back(new Base("integer", num));
      }
      else
      {
        // this is an id
        string sliced = root->token.substr(4, root->token.length() - 5);
        control_structures[environment].push_back(new Base("identifier", sliced));
      }
    }
    else
    {
      // This is a string
      string sliced = root->token.substr(5, root->token.length() - 6);
      control_structures[environment].push_back(new Base("string", sliced));
    }
  }
  else if (isBOp(root->token) || isUOp(root->token))
  {
    control_structures[environment].push_back(new Base("operator", root->token));
  }
  else if (root->token == "true" || root->token == "false")
  {
    control_structures[environment].push_back(new Base("bool", root->token));
  }
  else if (root->token == "lambda")
  {
    cout << "Error. lambda is not supported here" << endl;
    throw "Error. lambda is not supported here";
  }
  else if (root->token == "delta")
  {
  }
  else if (root->token == "->")
  {
    cout << "Error. -> is not supported here" << endl;
    throw "Error. -> is not supported here";
  }
}

void add_env_to_control(int number) // This adds a saved function to the control stack
{
  Base *temp_env = new Base("environment", number);
  control_stk.push(temp_env);
  stack_stk.push(temp_env);
  for (int i = 0; i < control_structures[number].size(); i++)
  {
    control_stk.push(control_structures[number][i]);
  }
}

void evaluate()
{
  // Setting up the parsing environment
  add_env_to_control(0);
  parsing_env.push(new Env_node(nullptr));
  parsing_env.top()->prev = nullptr;
  // iterating through the control stack and evaluating
  while (control_stk.size() > 1)
  {
    string the_type = control_stk.top()->type;
    rules(the_type);
  }
}

void rules(string type)
{
  if (type == "integer")
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "bool")
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "operator")
  {
    string op = control_stk.top()->arg_str1;
    control_stk.pop();
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "**" || op == "gr" || op == "ge" || op == "ls" || op == "le" || op == "ne" || op == "eq")
    {
      if (stack_stk.top()->type != "integer")
      {
        cout << "Expect an integer with " << op << endl;
        throw "Error";
      };
      int a = stack_stk.top()->arg_int1;
      stack_stk.pop();
      if (stack_stk.top()->type != "integer")
      {
        cout << "Expect an integer with " << op << endl;
        throw "Error";
      };
      int b = stack_stk.top()->arg_int1;
      stack_stk.pop();

      if (op == "+")
      {
        stack_stk.push(new Base("integer", a + b));
      }
      else if (op == "-")
      {
        stack_stk.push(new Base("integer", a - b));
      }
      else if (op == "*")
      {
        stack_stk.push(new Base("integer", a * b));
      }
      else if (op == "/")
      {
        stack_stk.push(new Base("integer", a / b));
      }
      else if (op == "**")
      {
        stack_stk.push(new Base("integer", pow(a, b)));
      }
      else if (op == "gr")
      {
        if (a > b)
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
      else if (op == "ge")
      {
        if (a >= b)
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
      else if (op == "ls")
      {
        if (a < b)
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
      else if (op == "ge")
      {
        if (a <= b)
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
      else if (op == "eq")
      {
        if (a == b)
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
      else if (op == "ne")
      {
        if (a != b)
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
    }
    else if (op == "neg")
    {
      if (stack_stk.top()->type != "integer")
      {
        cout << "Expect an integer with " << op << endl;
        throw "Error";
      };
      int a = stack_stk.top()->arg_int1;
      stack_stk.pop();
      stack_stk.push(new Base("integer", -a));
    }
    else if (op == "not")
    {
      if (stack_stk.top()->type != "bool")
      {
        cout << "Expect an integer with " << op << endl;
        throw "Error";
      };
      string a = stack_stk.top()->arg_str1;
      stack_stk.pop();
      if (a == "True")
      {
        stack_stk.push(new Base("bool", "false"));
      }
      else
      {
        stack_stk.push(new Base("bool", "true"));
      }
    }
    else if (op == "or" || op == "&")
    {
      if (stack_stk.top()->type != "bool")
      {
        cout << "Expect an bool with " << op << endl;
        throw "Error";
      };
      string a = stack_stk.top()->arg_str1;
      stack_stk.pop();
      if (stack_stk.top()->type != "bool")
      {
        cout << "Expect an bool with " << op << endl;
        throw "Error";
      };
      string b = stack_stk.top()->arg_str1;
      stack_stk.pop();

      if (op == "or")
      {
        if (a == "true" || b == "true")
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
      else if (op == "&")
      {
        if (a == "true" && b == "true")
        {
          stack_stk.push(new Base("bool", "true"));
        }
        else
        {
          stack_stk.push(new Base("bool", "false"));
        }
      }
    }
    else if (op == "aug")
    {
      cout << "aug is incomplete" << endl;
      throw "Error";
    }
  }
  else if (type == "lambda")
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();

    stack_stk.top()->
  }
}
