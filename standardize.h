#include <iostream>
#include <stack>

using namespace std;

void standardize(Node *);
void standardize_list(Node *);
void standardize_tree(Node *);
void standardize_tree_list(Node *);

void standardizer()
{
  standardize_tree(ast_bu.top());
  // standardize_tree_list(ast_bu.top());
}

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
    {
      cout << "Syntax error caught during standardizing" << endl;
      throw "Error";
    }
  }
  else if (node->token == "fcn_form")
  {
    int size = node->children.size();
    Node *temp_head = node->children[size - 1];
    for (int i = size - 2; i > 0; i--)
    {
      Node *new_node = new Node("lambda");
      new_node->children.push_back(node->children[i]);
      new_node->children.push_back(temp_head);
      temp_head = new_node;
    }
    Node *equal = new Node("=");
    equal->children.push_back(node->children[0]);
    equal->children.push_back(temp_head);

    *node = *equal;
  }
  // else if (node->token == "tau")
  // {
  //   Node *temp_head = new Node("nil");
  //   for (auto E : node->children)
  //   {
  //     Node *gamma = new Node("gamma");
  //     gamma->children.push_back(new Node("gamma"));
  //     gamma->children[0]->children.push_back(new Node("aug"));
  //     gamma->children[0]->children.push_back(temp_head);
  //     gamma->children.push_back(E);
  //     temp_head = gamma;
  //   }
  //   *node = *temp_head;
  // }
  // else if (node->token == "->")
  // {
  //   Node *B = node->children[0];
  //   Node *T = node->children[1];
  //   Node *F = node->children[2];

  //   Node *new_node = new Node("gamma");
  //   new_node->children.push_back(new Node("gamma"));
  //   new_node->children.push_back(new Node("nil"));
  //   new_node->children[0]->children.push_back(new Node("gamma"));
  //   new_node->children[0]->children.push_back(new Node("lambda"));

  //   new_node->children[0]->children[1]->children.push_back(new Node("()"));
  //   new_node->children[0]->children[1]->children.push_back(F);

  //   new_node->children[0]->children[0]->children.push_back(new Node("gamma"));
  //   new_node->children[0]->children[0]->children.push_back(new Node("lambda"));

  //   new_node->children[0]->children[0]->children[0]->children.push_back(new Node("Cond"));
  //   new_node->children[0]->children[0]->children[0]->children.push_back(B);

  //   new_node->children[0]->children[0]->children[1]->children.push_back(new Node("()"));
  //   new_node->children[0]->children[0]->children[1]->children.push_back(T);

  //   *node = *new_node;
  // }
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
    {
      cout << "Syntax error caught during standardizing" << endl;
      throw "Error";
    }
  }
  else if (node->token == "within")
  {
    if (node->children[0]->token == "=" && node->children[1]->token == "=")
    {
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
    }
    else
    {
      cout << "Syntax error caught during standardizing" << endl;
      throw "Error";
    }
  }
  else if (node->token == "@")
  {
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
  // else if (node->token == "not")
  // {
  //   Node *E = node->children[0];
  //   Node *new_node = new Node("gamma");
  //   new_node->children.push_back(new Node("not"));
  //   new_node->children.push_back(E);

  //   *node = *new_node;
  // }
  // else if (node->token == "neg")
  // {
  //   Node *E = node->children[0];
  //   Node *new_node = new Node("gamma");
  //   new_node->children.push_back(new Node("neg"));
  //   new_node->children.push_back(E);

  //   *node = *new_node;
  // }
  else if (node->token == "rec")
  {
    if (node->children[0]->token == "=")
    {
      Node *X = node->children[0]->children[0];
      Node *E = node->children[0]->children[1];
      Node *equal = new Node("=");
      equal->children.push_back(X);
      equal->children.push_back(new Node("gamma"));
      equal->children[1]->children.push_back(new Node("Ystar"));
      equal->children[1]->children.push_back(new Node("lambda"));
      equal->children[1]->children[1]->children.push_back(X);
      equal->children[1]->children[1]->children.push_back(E);
      *node = *equal;
    }
    else
    {
      cout << "Syntax error caught during standardizing" << endl;
      throw "Error";
    }
  }
  // else if (isBOp(node->token))
  // {
  //   Node *gamma = new Node("gamma");
  //   gamma->children.push_back(new Node("gamma"));
  //   gamma->children.push_back(node->children[1]);
  //   gamma->children[0]->children.push_back(new Node(node->token));
  //   gamma->children[0]->children.push_back(node->children[0]);

  //   *node = *gamma;
  // }
  else if (node->token == "lambda")
  {
    int size = node->children.size();
    Node *temp_head = node->children[size - 1];
    for (int i = 0; i < size - 1; i++)
    {
      Node *lambda = new Node("lambda");
      lambda->children.push_back(node->children[i]);
      lambda->children.push_back(temp_head);
      temp_head = lambda;
    }
    *node = *temp_head;
  }
  else if (node->token == "and")
  {
    int size = node->children.size();
    Node *equal = new Node("=");
    equal->children.push_back(new Node(","));
    equal->children.push_back(new Node("tau"));
    for (int i = 0; i < size; i++)
    {
      equal->children[0]->children.push_back(node->children[i]->children[0]);
      equal->children[1]->children.push_back(node->children[i]->children[1]);
    }
    standardize_tree(equal->children[1]);
    *node = *equal;
  }
}

void standardize_tree_list(Node *node)
{
  for (auto child_node : node->children)
  {
    standardize_tree_list(child_node);
  }
  if (node->children.size() > 0)
  {
    if (node->children[0]->token == ",")
    {
      standardize_list(node);
    }
  }
}

void standardize_list(Node *node)
{
  Node *temp_head = node->children[1];
  for (int i = 0; i < node->children[0]->children.size(); i++)
  {
    Node *gamma = new Node("gamma");
    gamma->children.push_back(new Node("lambda"));
    gamma->children.push_back(new Node("gamma"));
    gamma->children[0]->children.push_back(new Node(to_string(i + 1)));
    gamma->children[0]->children.push_back(temp_head);
    gamma->children[1]->children.push_back(new Node("Temp"));
    gamma->children[1]->children.push_back(node->children[0]->children[i]);
    temp_head = gamma;
  };
  Node *new_node = new Node("lambda");
  new_node->children.push_back(new Node("Temp"));
  new_node->children.push_back(temp_head);

  *node = *new_node;
}