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

string addSpace(string buffer, char space_char)
{
  if (space_char == ' ')
    buffer += "\\s";
  else if (space_char == '\t')
    buffer += "\\t";
  else if (space_char == '\n')
    buffer += "\\n";
  return buffer;
}

vector<Token> scanner(string input);
void printTokens(vector<Token> tokens);
vector<Token> screener(vector<Token> tokens);
void printTree(vector<string> rule);

int main()
{
  string input_file = "input.txt";
  // string input = readFileToString(input_file);
  // string input = "- true ;; @ hello false; ** true ;; @ hello false; ; ; * true ;; @ hello false; ** true ;; @ hello false; ; 'gr'  - true ;; @ hello false; ** true ;; @ hello false; ; ; * true ;; @ hello false; ** true ;; @ hello false; ; ;";
  string input = "5 & hello or help";
  tokens = scanner(input);
  tokens = screener(tokens);
  printTokens(tokens);
  cout << endl;
  E();
  if (tokens[0].type == "EOF")
  {
    cout << "Grammer rules" << endl;
    printTree(dt_bu);
    cout << endl;

    cout << "AST" << endl;
    printAST(ast_bu.top());
    cout << endl;
  }
  else
  {
    cout << "Input is not valid" << endl;
  }
}

vector<Token> screener(vector<Token> tokens)
{
  vector<Token> new_tokens;
  for (const auto &i : tokens)
  {
    if (i.type == "EOF")
    {
      new_tokens.push_back(i);
      break;
    }
    else if ((i.type != "comment") && (i.type != "space"))
    {
      new_tokens.push_back(i);
    }
  }
  return new_tokens;
}

vector<Token> scanner(string input)
{
  vector<Token> tokens;

  input = input + '\n';

  string buffer = "";
  int index = 0;

  while (index < input.length())
  {
    char c = input[index++];
    if (isLetter(c))
    {
      buffer += c;
      while (true)
      {
        c = input[index++];
        if (isLetter(c) || isDigit(c) || (c == '_'))
        {
          buffer += c;
        }
        else
        {
          // TODO: Add bufffer to something
          tokens.push_back(Token("identifier", buffer));
          // cout << "Identifier : " << buffer << endl;
          buffer = "";
          index--;
          break;
        }
      }
    }
    else if (isDigit(c))
    {
      buffer += c;
      while (true)
      {
        c = input[index++];
        if (isDigit(c))
        {
          buffer += c;
        }
        else
        {
          // TODO: Add bufffer to something
          tokens.push_back(Token("integer", buffer));
          // cout << "Integer : " << buffer << endl;
          buffer = "";
          index--;
          break;
        }
      }
    }
    else if ((c == '\'') && (input[index] == '\''))
    {
      index++;
      buffer = "\'\'";
      while (true)
      {
        c = input[index++];
        if (c == '\\')
        {
          buffer += c;
          c = input[index++];
          if ((c == 't') || (c == 'n') || (c == '\\'))
          {
            buffer += c;
            continue;
          }
          else if ((c == '\'') && (input[index] == '\''))
          {
            buffer += "\'\'";
            index++;
            continue;
          }
          else
          {
            throw "Unkown escape sequence: " + c; // ? This doesn't accept "\a"? YES
          }
        }
        else if ((c == ' ' || isDigit(c) || isLetter(c) || isOperator(c) || isPunction(c)))
        {
          buffer += c;
        }
        else if ((c == '\'') && (input[index] == '\''))
        {
          buffer += "\'\'";
          index++;
          // TODO: Add bufffer to something
          tokens.push_back(Token("string", buffer));
          // cout << "String : " << buffer << endl;
          buffer = "";
          break;
        }
      }
    }
    else if (isSpace(c))
    {
      buffer = addSpace("", c);
      while (true)
      {
        c = input[index++];
        if (isSpace(c))
        {
          buffer = addSpace(buffer, c);
        }
        else
        {
          // TODO: Add bufffer to something
          tokens.push_back(Token("space", buffer));
          // cout << "Space : " << buffer << endl;
          buffer = "";
          index--;
          break;
        }
      }
    }
    else if (isOperator(c))
    {
      if ((c == '/') && (input[index] == '/'))
      {
        index++;
        buffer = "//";
        while (input[index] != '\n' && index < input.length())
        {
          buffer += input[index++];
        }
        buffer += "\\n";
        index++;
        // TODO: Add bufffer to something
        tokens.push_back(Token("comment", buffer));
        // cout << "Comment : " << buffer << endl;
        buffer = "";
      }
      else
      {
        buffer += c;
        while (true)
        {
          c = input[index++];
          if (isOperator(c))
          {
            buffer += c;
          }
          else
          {
            // TODO: Add bufffer to something
            tokens.push_back(Token("operator", buffer));
            // cout << "Operator : " << buffer << endl;
            buffer = "";
            index--;
            break;
          }
        }
      }
    }
    else if (isPunction(c))
    {
      buffer += c;
      // TODO: Add bufffer to something
      tokens.push_back(Token(buffer, buffer));
      // cout << "Punction : " << buffer << endl;
      buffer = "";
    }
  }
  tokens.push_back(Token("EOF", "EOF"));
  return tokens;
}

void printTokens(vector<Token> tokens)
{
  for (const auto &i : tokens)
  {
    if (i.type == "EOF")
    {
      cout << i.type << " : " << i.value << endl;
      break;
    }
    else
    {
      cout << i.type << " : " << i.value << std::endl;
    }
  }
}

void printTree(vector<string> rule)
{
  for (const auto &i : rule)
  {
    cout << i << endl;
  }
}