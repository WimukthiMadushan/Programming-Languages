#include <iostream>
#include <stack>

using namespace std;

typedef struct Token // Scanned tokens
{
  string type;
  string value;

  Token(string type, string value) : type(type), value(value) {}
} Token;

typedef struct Node // Building block of abstract syntax tree
{
  string token;
  vector<Node *> children;

  Node(string token) : token(token), children() {}

  ~Node()
  {
    for (Node *child : children)
    {
      delete child;
    }
  }
} Node;

extern vector<Token> tokens; // Token list
extern vector<string> dt_bu; // Derivation Tree Bottom Up

extern stack<Node *> ast_bu; // Abstract Syntax Tree Bottom Up

// Add the given amount of children (arguments) from the top of the stack
// Then push this newly created token into that stack
void Build_tree(string token, int arguments)
{
  Node *new_node = new Node(token);
  for (int i = 0; i < arguments; i++)
  {
    if (!ast_bu.empty())
    {
      new_node->children.insert(new_node->children.begin(), ast_bu.top());
      ast_bu.pop();
    }
    else
    {
      cout << "Stack is empty!" << endl;
      throw "Error";
    }
  }
  ast_bu.push(new_node);
}

void AST(Node *root, int depth) // AST recursion funciton
{
  for (int i = 0; i < depth; i++)
  {
    cout << ".";
  }
  cout << root->token << endl;
  depth++;
  for (int i = 0; i < root->children.size(); i++)
  {
    AST(root->children[i], depth);
  }
}

void printAST() // Prints the AST
{
  AST(ast_bu.top(), 0);
}

void printTokens() // Token list for derivation purposes.
{
  cout << endl
       << "Tokens" << endl;
  for (const auto &i : tokens)
  {
    if (i.type == "EOF")
    {
      cout << i.type << " : " << i.value << endl;
      break;
    }
    else
    {
      cout << i.type << " : " << i.value << std::endl;
    }
  }
  cout << endl;
}

void printTree() // Defivation tree for debugging purposes
{
  cout << endl
       << "Derivation Tree Top Down" << endl;
  for (const auto &i : dt_bu)
  {
    cout << i << endl;
  }
  cout << endl;
}
