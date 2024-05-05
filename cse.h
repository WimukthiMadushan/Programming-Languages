#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "cse_structs.h"

int env_count = 0;

// Creating the control stack
void pre_order_traversal(Node *root, int environment); // Traverse  through the tree.
void add_func_to_control(Base *prev, int number);      // Add a funciton to the control stack.

// Evaluate the control stack
void rules(string); // Rules regarding the control stack

// Here we maintain several structures to keep track of the process
//? control_stk - Works as the control in the CSE process.
//? stack_stk - Works as the stack in the CSE process.
//? parsing_env - Stores the current environment in the CSE process as a stack of pointers.
//? control_structures - Keep all the functions in memory as an array.

// CSE function handles all other functions
void cse()
{
  // Create a blank array for the main function.
  control_structures.push_back(vector<Base *>());
  pre_order_traversal(ast_bu.top(), 0);

  // Initialising a parsing environment
  parsing_env.push(new Base("environment"));
  parsing_env.top()->prev = nullptr;
  // Adding in built identifiers
  add_in_built_to_env(parsing_env.top());
  add_func_to_control(parsing_env.top(), 0);

  // Evaluating the control stack
  // Iterating through the control stack and evaluating
  while (control_stk.size() > 1)
  // for (int i = 0; i < 7; i++)
  {
    string the_type = control_stk.top()->type;
    rules(the_type);
    // cout << i << endl;
    // cout << "PE " << parsing_env.size() << endl;
    // cout << control_stk.top()->type << endl;
    // cout << stack_stk.top()->type << endl;
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
    // cout << temp->type << endl;
    // cout << temp->arg_int << endl;
    // cout << temp->arg_str << endl;
  }
}

void pre_order_traversal(Node *root, int environment)
// Traverse through the tree and create arrays of control structures
{
  if (root->token == "lambda")
  {
    Base *lambda = new Base("lambda", ++env_count);
    control_structures.push_back(vector<Base *>());

    // Create the function in a seperate arrays.
    pre_order_traversal(root->children[1], env_count);

    // Arguments : can be a single identifier or a list of identifiers
    if (root->children[0]->token != ",")
    {
      string sliced = root->children[0]->token.substr(4, root->children[0]->token.length() - 5);
      lambda->children.push_back(new Base("identifier", sliced));
    }
    else
    {
      for (int i = 0; i < root->children[0]->children.size(); i++)
      {
        string sliced = root->children[0]->children[i]->token.substr(4, root->children[0]->children[i]->token.length() - 5);
        lambda->children.push_back(new Base("identifier", sliced));
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
        string sliced = root->token.substr(7, root->token.length() - 10);
        control_structures[environment].push_back(new Base("string", sliced));
      }
    }
    else if (isBOp(root->token) || isUOp(root->token)) // Complete
    {
      control_structures[environment].push_back(new Base("operator", root->token));
    }
    else if (root->token == "true" || root->token == "false") // Complete
    {
      control_structures[environment].push_back(new Base("boolean", root->token));
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
    //! Check the suitable tokens
    else if (root->token == "dummy")
    {
      control_structures[environment].push_back(new Base("dummy"));
    }
    else if (root->token == "nil")
    {
      control_structures[environment].push_back(new Base("tuple"));
    }

    // Iterating through the children
    for (int i = 0; i < root->children.size(); i++)
    {
      pre_order_traversal(root->children[i], environment);
    }
  }
}

void add_func_to_control(Base *prev, int number) // This adds a saved function to the control stack
{
  Base *temp_env = new Base("environment", prev);
  control_stk.push(temp_env);
  stack_stk.push(temp_env);
  parsing_env.push(temp_env);

  // Adding the saved function to the control stack
  for (int i = 0; i < control_structures[number].size(); i++)
  {
    control_stk.push(control_structures[number][i]);
  }
}

void rules(string type)
{
  if (type == "integer") // Complete
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "boolean") // Complete
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "operator") // Complete
  {
    string op = control_stk.top()->arg_str;
    control_stk.pop();
    if (op == "ne" || op == "eq")
    {
      if (stack_stk.top()->type != "integer" && stack_stk.top()->type != "boolean")
      {
        cout << "Expect an integer or boolean with " << op << endl;
        throw "Error";
      };
      int a = stack_stk.top()->arg_int;
      stack_stk.pop();
      if (stack_stk.top()->type != "integer" && stack_stk.top()->type != "boolean")
      {
        cout << "Expect an integer or boolean with " << op << endl;
        throw "Error";
      };
      int b = stack_stk.top()->arg_int;
      stack_stk.pop();
      if (op == "eq")
      {
        if (a == b)
        {
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
        }
      }
      else
      //(op == "ne")
      {
        if (a != b)
        {
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
        }
      }
    }
    else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "**" || op == "gr" || op == "ge" || op == "ls" || op == "le")
    {
      if (stack_stk.top()->type != "integer")
      {
        cout << "Expect an integer with " << op << endl;
        throw "Error";
      };
      int a = stack_stk.top()->arg_int;
      stack_stk.pop();
      if (stack_stk.top()->type != "integer")
      {
        cout << "Expect an integer with " << op << endl;
        throw "Error";
      };
      int b = stack_stk.top()->arg_int;
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
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
        }
      }
      else if (op == "ge")
      {
        if (a >= b)
        {
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
        }
      }
      else if (op == "ls")
      {
        if (a < b)
        {
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
        }
      }
      else // op == "le"
      {
        if (a <= b)
        {
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
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
      int a = stack_stk.top()->arg_int;
      stack_stk.pop();
      stack_stk.push(new Base("integer", -a));
    }
    else if (op == "not")
    {
      if (stack_stk.top()->type != "boolean")
      {
        cout << "Expect a boolean with " << op << endl;
        throw "Error";
      };
      string a = stack_stk.top()->arg_str;
      stack_stk.pop();
      if (a == "true")
      {
        stack_stk.push(new Base("boolean", "false"));
      }
      else
      {
        stack_stk.push(new Base("boolean", "true"));
      }
    }
    else if (op == "or" || op == "&")
    {
      if (stack_stk.top()->type != "boolean")
      {
        cout << "Expect a boolean with " << op << endl;
        throw "Error";
      };
      string a = stack_stk.top()->arg_str;
      stack_stk.pop();
      if (stack_stk.top()->type != "boolean")
      {
        cout << "Expect a boolean with " << op << endl;
        throw "Error";
      };
      string b = stack_stk.top()->arg_str;
      stack_stk.pop();

      if (op == "or")
      {
        if (a == "true" || b == "true")
        {
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
        }
      }
      else // (op == "&")
      {
        if (a == "true" && b == "true")
        {
          stack_stk.push(new Base("boolean", "true"));
        }
        else
        {
          stack_stk.push(new Base("boolean", "false"));
        }
      }
    }
    else if (op == "aug") // Complete for other operations if there are any including aug
    {
      if (stack_stk.top()->type != "tuple")
      {
        cout << "Cannot append to " << stack_stk.top()->type << endl;
        throw "Error";
      }
      Base *list = stack_stk.top();
      stack_stk.pop();
      list->children.push_back(stack_stk.top());
      stack_stk.pop();
      stack_stk.push(list);
    }
  }
  else if (type == "lambda") // Complete
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
    stack_stk.top()->prev = parsing_env.top();
  }
  else if (type == "gamma")
  {
    if (stack_stk.top()->type == "lambda") //! Look again if needed
    //! Change this to accept strings and stuff.
    {
      Base *func = stack_stk.top();
      control_stk.pop();
      stack_stk.pop();

      Base *func_args = stack_stk.top();
      stack_stk.pop();

      if (func->arg_int >= 0)
      {
        add_func_to_control(func->prev, func->arg_int);

        // cout << "children size : " << func->children.size() << endl;

        if (func->children.size() > 1) // Argument dissassembles the list
        {
          if (func_args->children.size() != func->children.size())
          {
            cout << "Insufficient arguments" << endl;
            throw "Error";
          }
          else
          {
            for (int i = 0; i < func_args->children.size(); i++)
            {
              Base *temp = new Base("identifier", func->children[i]->arg_str);
              temp->prev = func_args->children[i];
              parsing_env.top()->children.push_back(temp);
            }
          }
        }
        // else there is only one argument
        else
        {
          // cout << "type : " << func_args->type << endl;
          // cout << "value : " << func_args->arg_int << endl;
          parsing_env.top()->children.push_back(new Base("identifier", func->children[0]->arg_str, func_args));
        }
      }
      else
      {
        in_built_functions(func, func_args);
      }
    }
    else if (stack_stk.top()->type == "tuple")
    {
      control_stk.pop();
      Base *list = stack_stk.top();
      stack_stk.pop();
      int index = stack_stk.top()->arg_int;
      stack_stk.pop();
      stack_stk.push(list->children[index]);
    }
    else if (stack_stk.top()->type == "ystar") // Think okay if not for pointers
    {
      control_stk.pop();
      stack_stk.pop();
      Base *lambda = stack_stk.top();
      stack_stk.pop();

      Base *eta = new Base("eta");
      eta->prev = lambda->prev;
      eta->children = lambda->children;
      eta->arg_int = lambda->arg_int;
      // eta->arg_str = lambda->arg_str;

      stack_stk.push(eta);
    }
    else if (stack_stk.top()->type == "eta") // This okay if not for pointers
    {
      control_stk.push(new Base("gamma"));
      Base *lambda = new Base("lambda");
      lambda->prev = stack_stk.top()->prev;
      lambda->children = stack_stk.top()->children;
      lambda->arg_int = stack_stk.top()->arg_int;
      // lambda->arg_str = stack_stk.top()->arg_str;
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
      cout << "Error with environment Base" << endl;
      throw "Error";
    }
  }
  else if (type == "identifier")
  {
    Base *env = parsing_env.top();
    Base *value;
    bool found = false;
    // return;
    while (true)
    {
      for (int i = 0; i < env->children.size(); i++)
      {
        if (env->children[i]->arg_str == control_stk.top()->arg_str)
        {
          found = true;
          value = env->children[i]->prev;
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
      cout << "Identifier " << control_stk.top()->arg_str << " not found" << endl;
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

    for (int i = 0; i < control_structures[temp->arg_int].size(); i++)
    {
      control_stk.push(control_structures[temp->arg_int][i]);
    }
  }
  else if (type == "tau")
  {
    Base *list = new Base("tuple");
    for (int i = 0; i < control_stk.top()->arg_int; i++)
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
    if (stack_stk.top()->arg_str == "true")
    {
      control_stk.pop();
      control_stk.pop();
      stack_stk.pop();
    }
    else if (stack_stk.top()->arg_str == "false")
    {
      control_stk.pop();
      Base *temp = control_stk.top();
      control_stk.pop();
      control_stk.pop();
      control_stk.push(temp);
      stack_stk.pop();
    }
    else
    {
      cout << "Expect a boolean" << endl;
      throw "Error";
    }
  }
  else if (type == "tuple")
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else if (type == "string")
  {
    stack_stk.push(control_stk.top());
    control_stk.pop();
  }
  else // Fill for other rules
  {
    cout << "Error with Base" << endl;
    throw "Error";
  }
}
