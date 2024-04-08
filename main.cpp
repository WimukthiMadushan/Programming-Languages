#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

#include "struct.h"
#include "vocabulary.h"
#include "grammer.h"
#include "lex.h"

vector<Token> tokens; // Token list
vector<string> dt_td; // Derivation Tree Top Down for debugging
vector<string> dt_bu; // Derivation Tree Bottom Up for debugging

stack<Node *> ast_bu; // Abstract Syntax Tree Bottom Up stack

string readFileToString(const string &filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Error opening file: " << filename << endl;
    return "";
  }
  stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

int main()
{
  string input;
  string input_file = "input.txt";
  input = readFileToString(input_file);

  // TODO: Try different strings here. Comment all below to read the input_file.
  // input = "- true ;; @ hello false; ** true ;; @ hello false; ; ; * true ;; @ hello false; ** true ;; @ hello false; ; 'gr'  - true ;; @ hello false; ** true ;; @ hello false; ; ; * true ;; @ hello false; ** true ;; @ hello false; ; ;";
  // input = "let f x y z = x + y + z in f 1 2 3";
  // input = "let x  = 3 and y = 4 in x + y";

  scanner(input);
  screener();

  // Parser
  E();
  if (tokens[0].type == "EOF")
  {
    printAST();
  }
  else
  {
    cout << "Input is not valid" << endl;
  }
}
