#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "struct.h"

vector<Token> tokens;

void Read()
{
}

void E(vector<Token> tokens) // Incomplete
{
  if (tokens.front().value == "let")
  {
  }
}

void Vl(vector<Token> tokens)
{
  if (tokens.front().type == "IDENTIFIER")
  {
    tokens.erase(tokens.begin());
    // TODO: wth is a list
  }
  else
    throw "Error";
}

void main()
{
}