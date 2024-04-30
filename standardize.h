#include <iostream>
#include <stack>

using namespace std;

void standardize(Node *);

void standardize_tree(Node *node)
{
  for (auto child_node : node->children)
  {
    standardize_tree(child_node);
  }
  standardize(node);
}

void standardize(Node *node)
{
  if (node->token == "let")
  {
    if (node->children[0]->token == "=")
    {
      Node *X = node->children[0]->children[0];
      Node *E = node->children[0]->children[1];
      Node *P = node->children[1];
      Node *new_node = new Node("gamma");

      new_node->children.push_back(new Node("lambda"));
      new_node->children[0]->children.push_back(X);
      new_node->children[0]->children.push_back(P);
      new_node->children.push_back(E);

      *node = *new_node;
    }
    else
      throw "Error";
  }
  else if (node->token == "where")
  {
    if (node->children[1]->token == "=")
    {
      Node *P = node->children[0];
      Node *X = node->children[1]->children[0];
      Node *E = node->children[1]->children[1];
      Node *new_node = new Node("gamma");

      new_node->children.push_back(new Node("lambda"));
      new_node->children[0]->children.push_back(X);
      new_node->children[0]->children.push_back(P);
      new_node->children.push_back(E);

      *node = *new_node;
    }
    else
      throw "Error";
  }
  //! Complete below this line
}
