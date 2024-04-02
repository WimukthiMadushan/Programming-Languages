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

extern vector<Token> tokens;
extern vector<string> dt_td; // Derivation Tree Top Down
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

//? Sample code
// Build_tree("First Child", 0);
// Build_tree("Son of second child", 0);
// Build_tree("Second Child", 1);
// Build_tree("Third Child", 0);
// Build_tree("Father", 3);
// Print_tree(ast_bu.top());

void Print_tree(Node *root)
{
  for (int i = 0; i < root->children.size(); i++)
  {
    Print_tree(root->children[i]);
  }

  cout << root->token << " : " << root->children.size() << endl;
}
