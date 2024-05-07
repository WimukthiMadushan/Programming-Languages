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

  // TODO: try saving different text files in the test.txt file. Comment the below line to read the "input.txt".
  input_file = "test.txt";

  input = readFileToString(input_file);

  // TODO: Try different strings here. Comment all below to read the input_file.
  // input = "let f x y z = x + y + z in f 1 2 3";
  // input = "let x  = 3 and y = 4 in x + y";
  // input = "Print((fn x . x + 1 )4 * 6)";
  // input = "(fn x. Print(x))pi";
  // input = "let x = 3 in x + 1";
  // input = "3 ge 6 -> 1 | (4*2)";
  // input = "(fn n . n ls 0 -> -n | n)(-3)";
  // input = "(fn x. fn w . x + w) 5 6";
  // input = "(fn x .(1 + (fn w . -w)x))((fn z. 2 * z )7)";
  // input = "Print(Conc ''not '' (Conc ''help'' ''ing''))";
  // input = "let rec f n = n eq 1 -> 1 | n*f(n-1) in Print(f 4)";
  // input = "(fn x. Print(x)) 5 ";
  // input = "Print(hundred*2)";
  // input = "Print((2,3,''4''))";
  // input = "Print(''help'' ne ''help'')";
  // input = "Print(Null nil)";
  // input = "Print((2,3,4) 4)";
  // input = "let Greater x y = x ls y -> y | x in let Check(a, b, c) = Print(a @Greater b @Greater c) in Check(8, 23, 2) ";

  try
  { //! Lex
    scanner(input);
    screener();
    // printTokens();

    //! Parser
    parser();
    standardizer();

    // printAST();
    cse();
  }
  catch (...)
  {
    return 0;
  }
}
