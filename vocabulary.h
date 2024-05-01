#include <iostream>
using namespace std;

bool isLetter(char newElement)
{
  int size = 52;
  char letter[size] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  for (int i = 0; i < size; ++i)
  {
    if (letter[i] == newElement)
    {
      return true;
    }
  }
  return false;
}

bool isDigit(char newElement)
{
  int size = 10;
  char digit[size] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for (int i = 0; i < size; ++i)
  {
    if (digit[i] == newElement)
    {
      return true;
    }
  }
  return false;
}

bool isSpace(char newElement)
{
  int size = 3;
  char space[size] = {' ', '\t', '\n'};
  for (int i = 0; i < size; ++i)
  {
    if (space[i] == newElement)
    {
      return true;
    }
  }
  return false;
}

bool isOperator(char newElement)
{
  int size = 26;
  char operator_symb[size] = {'+', '-', '*', '<', '>', '&', '.', '@', '/', ':', '=', '~', '|', '$', '!', '#', '%', '^', '_', '[', ']', '{', '}', '"', '`', '?'};
  for (int i = 0; i < size; ++i)
  {
    if (operator_symb[i] == newElement)
    {
      return true;
    }
  }
  return false;
}

bool isPunction(char newElement)
{
  int size = 4;
  char punction[size] = {'(', ')', ';', ','};
  for (int i = 0; i < size; ++i)
  {
    if (punction[i] == newElement)
    {
      return true;
    }
  }
  return false;
}

bool isReserved(string token)
{
  int size = 20;
  string reserved[size] = {"dummy", "nil", "within", "and", "rec", "false", "true", "ne", "eq", "le", "ls", "ge", "gr", "not", "or", "aug", "where", "fn", "let", "in"};
  for (int i = 0; i < size; ++i)
  {
    if (reserved[i] == token)
    {
      return true;
    }
  }
  return false;
}

bool isOp(string token)
{
  int size = 14;
  string op[size] = {"aug", "or", "&", "+", "-", "/", "**", "*", "gr", "ge", "le", "ls", "eq", "ne"};
  for (int i = 0; i < size; ++i)
  {
    if (op[i] == token)
    {
      return true;
    }
  }
  return false;
}