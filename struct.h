#include <iostream>
#include <stack>

using namespace std;

typedef struct Token
{
  string type;
  string value;

  Token(string type, string value) : type(type), value(value) {}
} Token;

typedef struct Node
{
  string token;
  vector<Node *> children;

  Node(string token) : token(token), children() {}

  void addChild(Node *child)
  {
    children.insert(children.begin(), child);
  }
} Node;

extern vector<Token> tokens; // Token list
extern vector<string> dt_bu; // Derivation Tree Bottom Up

extern stack<Node *> ast_bu; // Abstract Syntax Tree Bottom Up

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

void AST(Node *root, int depth)
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

void printAST()
{
  cout << endl;
  AST(ast_bu.top(), 0);
  cout << endl;
}

void printTokens()
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

void printTree()
{
  cout << endl
       << "Derivation Tree Top Down" << endl;
  for (const auto &i : dt_bu)
  {
    cout << i << endl;
  }
  cout << endl;
}