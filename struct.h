#include <iostream>

using namespace std;

typedef struct Token
{
  string type;
  string value;

  Token(string type, string value) : type(type), value(value) {}
} Token;

extern vector<Token> tokens;