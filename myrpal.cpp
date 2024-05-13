#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <cstring>
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
    throw "Error opening file";
  }
  stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

int main(int argc, char *argv[])
{
  string input;
  string input_file;
  bool tree_flag = false;

  // Identifying the input file and flags.
  if (argc > 1)
  {
    input_file = argv[1];
    if (argc > 2)
    {
      if (strcmp(argv[2], "-ast") == 0)
      {
        tree_flag = true;
      }
    }
  }
  else
  {
    cout << "Please provide an input file." << endl;
    return 0;
  }

  try
  {
    input = readFileToString(input_file);

    //! Lexical Analyzer
    scanner(input);
    // printTokens();
    screener();

    //! Parser
    parser();
    if (tree_flag)
    {
      printAST();
      return 0;
    }
    standardizer();

    //! CSE
    cse();
  }
  catch (...)
  {
  }
  clear_stacks();
}
