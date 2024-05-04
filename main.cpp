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
#include "standardize.h"
#include "cse.h"

vector<Token> tokens; // Token list

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
  // input = "let f x y z = x + y + z in f 1 2 3";
  // input = "let x  = 3 and y = 4 in x + y";

  // input = "(fn x . x + 1 ) 3";
  // input = "let x = 3 in x + 1";
  input = "3 + 2";
  // input = "(fn (x, y). x+y)(5,6)";

  try
  { //! Lex
    scanner(input);
    screener();

    //! Parser
    parser();
    standardizer();

    printAST();
    // cse();
  }
  catch (...)
  {
    return 0;
  }
}
