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
  else if(node->token == "fcn_form"){
      Node *P = node->children[0];
      Node *V = node->children[1];
      Node *E = node->children[1];
      Node *new_node = new Node("=");

      new_node->children.push_back(new Node("lambda"));
      new_node->children[0]->children.push_back(P);
      new_node->children[0]->children.push_back(V);
      new_node->children[0]->children.push_back(E);

      *node = *new_node;

  }
  else if(node->token == "tau"){
      Node *E = node->children[0];
      Node *new_node = new Node("gamma");
      new_node->children.push_back(new Node("gamma"));
      new_node->children.push_back(E);
      new_node->children[0]->children.push_back(new Node("aug"));
      new_node->children[0]->children.push_back(new Node("nill"));

      *node = *new_node;

  }
  else if(node->token == "within"){
      if(node->children[0]->token == "=" && node->children[1]->token == "="){
          Node *X1 = node->children[0]->children[0];
          Node *E1 = node->children[0]->children[1];
          Node *X2 = node->children[1]->children[0];
          Node *E2 = node->children[1]->children[1];

          Node *new_node = new Node("=");
          new_node->children.push_back(X2);
          new_node->children.push_back(new Node("gamma"));
          new_node->children[1]->children.push_back(new Node("lambda"));
          new_node->children[1]->children.push_back(E1);
          new_node->children[1]->children[0]->children.push_back(X1);
          new_node->children[1]->children[0]->children.push_back(E2);

          *node = *new_node;

      } else{
          throw "Error";
      }
  }
  else if(node->token == "@"){
      Node *E1 = node->children[0];
      Node *N = node->children[1];
      Node *E2 = node->children[2];

      Node *new_node = new Node("gamma");
      new_node->children.push_back(new Node("gamma"));
      new_node->children.push_back(E2);
      new_node->children[0]->children.push_back(N);
      new_node->children[0]->children.push_back(E1);

      *node = *new_node;

  }
  else if(node->token == "->"){
      Node *B = node->children[0];
      Node *T = node->children[1];
      Node *F = node->children[2];

      Node *new_node = new Node("gamma");
      new_node->children.push_back(new Node("gamma"));
      new_node->children.push_back(new Node("nill"));
      new_node->children[0]->children.push_back(new Node("gamma"));
      new_node->children[0]->children.push_back(new Node("lambda"));

      new_node->children[0]->children[1]->children.push_back(new Node("()"));
      new_node->children[0]->children[1]->children.push_back(F);

      new_node->children[0]->children[0]->children.push_back(new Node("gamma"));
      new_node->children[0]->children[0]->children.push_back(new Node("lambda"));

      new_node->children[0]->children[0]->children[0]->children.push_back(new Node("Cond"));
      new_node->children[0]->children[0]->children[0]->children.push_back(B);

      new_node->children[0]->children[0]->children[1]->children.push_back(new Node("()"));
      new_node->children[0]->children[0]->children[1]->children.push_back(T);

      *node = *new_node;

  }

}
