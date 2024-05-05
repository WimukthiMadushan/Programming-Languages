#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "cse_structs.h"

int env_count = 0;

void pre_order_traversal(Node *root, int environment);  // Traverse  through the tree.
void add_env_to_control(Base *prev, int number);        // Add a funciton to the control stack.
void add_token_to_control(Node *root, int environment); // Add a nodes to control structures.
void evaluate();                                        // Evaluate the control stack.
void rules(string);

void cse()
{
  cout << "Hello, I'm CSE!" << endl;
  control_structures.push_back(vector<Base *>()); // Create a blank array for the main function.
  pre_order_traversal(ast_bu.top(), 0);
  evaluate();
}

void pre_order_traversal(Node *root, int environment)
// Traverse through the tree and create arrays of control structures
{
  if (root->token == "lambda")
  {
    Base *lambda = new Base("lambda", ++env_count);
    control_structures.push_back(vector<Base *>());
    pre_order_traversal(root->children[1], env_count);
    if (root->children[0]->token != ",")
    {
      string sliced = root->children[0]->token.substr(4, root->children[0]->token.length() - 5);
      lambda->arg_str1 = sliced;
    }
    else // Complete this for a list
    {
      // cout << "a" << endl;
      for (int i = 0; i < root->children[0]->children.size(); i++)
      {
        // cout << "b" << endl;
        string sliced = root->children[0]->children[i]->token.substr(4, root->children[0]->children[i]->token.length() - 5);
        lambda->children.push_back(new Base("identifier", sliced));
      }
    }
    control_structures[environment].push_back(lambda);
  }
  else if (root->token == "->") // Complete
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
  else // Complete
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
  if (root->token[0] == '<') // Complete
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
  else if (isBOp(root->token) || isUOp(root->token)) // Complete
  {
    control_structures[environment].push_back(new Base("operator", root->token));
  }
  else if (root->token == "true" || root->token == "false") // Complete
  {
    control_structures[environment].push_back(new Base("bool", root->token));
  }
  else if (root->token == "lambda")
  {
    cout << "Error. lambda is not supported here" << endl;
    throw "Error. lambda is not supported here";
  }
  else if (root->token == "Ystar")
  {
    control_structures[environment].push_back(new Base("ystar"));
  }
  else if (root->token == "tau")
  {
    control_structures[environment].push_back(new Base("tau", root->children.size()));
  }
  else if (root->token == "gamma") // Complete
  {
    control_structures[environment].push_back(new Base("gamma"));
  }
  else if (root->token == "->") // Complete
  {
    cout << "Error. -> is not supported here" << endl;
    throw "Error. -> is not supported here";
  }
}

void add_env_to_control(Base *prev, int number) // This adds a saved function to the control stack
{
  Base *temp_env = new Base("environment");
  control_stk.push(temp_env);
  stack_stk.push(temp_env);
  temp_env->prev = prev;
  parsing_env.push(temp_env);

  // Adding the saved function to the control stack
  for (int i = 0; i < control_structures[number].size(); i++)
  {
    control_stk.push(control_structures[number][i]);
  }
}

void evaluate()
{
  // Initialising a parsing environment
  parsing_env.push(new Base("environment"));
  parsing_env.top()->prev = nullptr;
  add_env_to_control(parsing_env.top(), 0);

  // Iterating through the control stack and evaluating
  while (control_stk.size() > 1)
  // for (int i = 0; i < 52; i++)
  {
    string the_type = control_stk.top()->type;
    rules(the_type);
    // cout << i << endl;
    cout << control_stk.top()->type << endl;
    cout << stack_stk.top()->type << endl;
  }
  //! these are completly working
  Base *temp = stack_stk.top();
  stack_stk.pop();
  if (stack_stk.top() != control_stk.top())
  {
    cout << "Run time Error";
    throw "Run time Error";
  }
  else
  {
    cout << temp->type << endl;
    cout << temp->arg_int1 << endl;
    cout << temp->arg_str1 << endl;
  }
}

void rules(string type)
{
  if (type == "integer") // Complete
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "bool") // Complete
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "operator") // Complete
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
  else if (type == "lambda") // Assume complete
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
    stack_stk.top()->prev = parsing_env.top();
  }
  else if (type == "gamma")
  {
    if (stack_stk.top()->type == "lambda")
    {
      Base *func = stack_stk.top();
      control_stk.pop();
      stack_stk.pop();

      Base *func_args = stack_stk.top();
      stack_stk.pop();

      add_env_to_control(func->prev, func->arg_int1);

      if (func_args->type == "list")
      {
        if (func_args->children.size() != func->children.size())
        {
          cout << "Insufficient arguments" << endl;
          throw "Error";
        }
        else
        {
          // Complete this code.
          for (int i = 0; i < func_args->children.size(); i++)
          {
            parsing_env.top()->children.push_back(new Base("identifier", func->children[i]->arg_str1, func_args->children[i]->arg_int1));
          }
        }
      }
      else if (func_args->type == "eta")
      {
        parsing_env.top()->children.push_back(func_args);
      }
      else
      {
        // cout << "id value is " << func->arg_str1 << endl;
        parsing_env.top()->children.push_back(new Base("identifier", func->arg_str1, func_args->arg_int1));
        // parsing_env.top()->arg_int2.push_back(func_args->arg_int1);
        // parsing_env.top()->arg_str2.push_back(func->arg_str1);
      }
    }
    else if (stack_stk.top()->type == "list")
    {
      control_stk.pop();
      Base *list = stack_stk.top();
      stack_stk.pop();
      int index = stack_stk.top()->arg_int1;
      stack_stk.pop();
      stack_stk.push(list->children[index]);
    }
    else if (stack_stk.top()->type == "ystar")
    {
      control_stk.pop();
      stack_stk.pop();
      Base *lambda = stack_stk.top();
      stack_stk.pop();

      // Create a top "eta"
      Base *eta = new Base("eta");
      eta->prev = lambda->prev;
      eta->children = lambda->children;
      eta->arg_int1 = lambda->arg_int1;
      eta->arg_str1 = lambda->arg_str1;

      stack_stk.push(eta);
    }
    else if (stack_stk.top()->type == "eta")
    {
      control_stk.push(new Base("gamma"));
      Base *lambda = new Base("lambda");
      lambda->prev = stack_stk.top()->prev;
      lambda->children = stack_stk.top()->children;
      lambda->arg_int1 = stack_stk.top()->arg_int1;
      lambda->arg_str1 = stack_stk.top()->arg_str1;
      stack_stk.push(lambda);
    }
  }
  else if (type == "environment")
  {
    Base *returning = stack_stk.top();
    stack_stk.pop();
    if (stack_stk.top() == control_stk.top())
    {
      control_stk.pop();
      stack_stk.pop();
      parsing_env.pop();
      stack_stk.push(returning);
    }
    else
    {
      cout << "Error" << endl;
      throw "Error";
    }
  }
  else if (type == "identifier")
  {
    // cout << parsing_env.top()->children[1]->arg_str1 << endl;
    // cout << parsing_env.top()->children[1]->arg_int1 << endl;
    // cout << "reached here" << endl;
    Base *env = parsing_env.top();
    Base *value;
    bool found = false;
    while (true)
    {
      for (int i = 0; i < env->children.size(); i++)
      {
        if (env->children[i]->arg_str1 == control_stk.top()->arg_str1)
        {
          found = true;
          if (env->children[i]->type == "identifier")
          {
            value = new Base("integer", env->children[i]->arg_int1);
          }
          else if (env->children[i]->type == "eta")
          {
            value = env->children[i];
          }

          break;
        }
      }
      if (found)
      {
        break;
      }
      else
      {
        env = env->prev;
        if (env == nullptr)
        {
          break;
        }
      }
    }
    if (!found)
    {
      cout << "Identifier " << control_stk.top()->arg_str1 << " not found" << endl;
      throw "Error";
    }
    else
    {
      stack_stk.push(value);
      control_stk.pop();
    }
  }
  else if (type == "delta")
  {
    Base *temp = control_stk.top();
    control_stk.pop();
    for (int i = 0; i < control_structures[temp->arg_int1].size(); i++)
    {
      control_stk.push(control_structures[temp->arg_int1][i]);
    }
  }
  else if (type == "tau")
  {
    Base *list = new Base("list");
    for (int i = 0; i < control_stk.top()->arg_int1; i++)
    {
      list->children.push_back(stack_stk.top());
      stack_stk.pop();
    }
    stack_stk.push(list);
    control_stk.pop();
  }
  else if (type == "ystar")
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "beta") // Complete
  {
    if (stack_stk.top()->arg_str1 == "true")
    {
      // cout << "was here" << endl;
      control_stk.pop();
      control_stk.pop();
      stack_stk.pop();
    }
    else
    {
      control_stk.pop();
      Base *temp = control_stk.top();
      control_stk.pop();
      control_stk.pop();
      control_stk.push(temp);
      stack_stk.pop();
    }
  }
}
