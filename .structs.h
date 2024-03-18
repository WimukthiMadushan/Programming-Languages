#include <iostream>

using namespace std;

typedef struct Identifier
{
  string value;
  Identifier(string value) : value(value) {}
} Identifier;

typedef struct Operator
{
  string value;
  Operator(string value) : value(value) {}
} Operator;

typedef struct Space
{
  string value;
  Space(string value) : value(value) {}
} Space;

typedef struct Punction
{
  string value;
  Punction(string value) : value(value) {}
} Punction;

typedef struct Integer
{
  int value;
  Integer(int value) : value(value) {}
} Integer;

typedef struct Comment
{
  string value;
  Comment(string value) : value(value) {}
} Comment;