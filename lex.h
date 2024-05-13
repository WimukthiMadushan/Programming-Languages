#include <iostream>
#include <stack>

using namespace std;

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

// screener removes unnecessary spaces, tabs, newlines and comments from the code
void screener()
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
  tokens = new_tokens;
}

// Scans the input file and creates tokens
void scanner(string input)
{

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
    else if (c == '\'')
    {
      buffer += c;
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
        else if (c == '\'')
        {
          buffer += c;
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
}
