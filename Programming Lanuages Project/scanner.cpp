#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <variant>

using  namespace std;

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
  int size = 25;
  char operator_symb[size] = {'+', '-', '*', '<', '>', '&', '.', '@', '/', ':', '=', '~', '|', '$', '!', '#', '%', '^', '_', '[', ']', '{', '}', '\'', '?'};
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

int main(){

  string input_file = "input.txt";
  //string input = readFileToString(input_file);
  string input = "hello I can Help 234 34 is not 2343 her234))  fwer)43 2323there ++= +23+  \"this is a string\" before_comment //this is a comment\n after_comment hello again";
  input = input + '\n';

  //token container.....
  using MyVariant = variant<int, double, string, char>;
  vector<MyVariant> tokens;
  
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
          tokens.push_back(buffer);
          cout << "Identifier : " << buffer << endl;
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
           tokens.push_back(buffer);
          cout << "Integer : " << buffer << endl;
          buffer = "";
          index--;
          break;
        }
      }
    }
    else if (c == '"')
    {
      buffer += c;
      while (true)
      {
        c = input[index++];
        if (c == '\\')
        {
          buffer += c;
          c = input[index++];
          if ((c == 't') || (c == 'n') || (c == '\\') || (c == '\"'))
          {
            buffer += c;
            continue;
          }
          else
          {
            throw "Unkown escape sequence: " + c;
          }
        }
        else if ((c == ' ' || isDigit(c) || isLetter(c) || isOperator(c) || isPunction(c)))
        {
          buffer += c;
        }
        else if (c == '"')
        {
          buffer += c;
          cout << "String : " << buffer << endl;
           tokens.push_back(buffer);
          buffer = "";
          break;
        }
      }
    }
    else if (isSpace(c))
    {
      continue;
    }
    else if (isOperator(c))
    {
      if ((c == '/') && (input[index] == '/'))
      {
        index++;
        while (input[index] != '\n')
        {
          // cout << input[index];
          index += 1;
        }
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
             tokens.push_back(buffer);
            cout << "Operator : " << buffer << endl;
            buffer = "";
            index--;
            break;
          }
        }
      }
    }
    else if (isPunction(c))
    {
      cout << "Punction : " << c << endl;
      tokens.push_back(c);
    }
  }
  //print all tokens......(optional)
  for (const auto& item : tokens) {
        visit([](const auto& value) {
            cout << value << std::endl;
        }, item);
    }

}
