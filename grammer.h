#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void E();
void Ew();
void D();
void Vb();

void Read(string type, string value)
{
  if (value == "any")
  {
    if (tokens[0].type == type)
    {
      tokens.erase(tokens.begin());
    }
    else
      throw "Error";
  }
  else if (tokens[0].value == value && tokens[0].type == type)
  {
    tokens.erase(tokens.begin());
  }
  else
  {
    cout << "Expected \"" + type + "\" : \"" + value + "\", got \"" + tokens[0].type + "\" : \"" + tokens[0].value << "\"" << endl;
    throw "Error";
  }
}

bool NextToken(string type, string value)
{
  if (value == "any" && tokens[0].type == type)
  {
    return true;
  }
  else if (tokens[0].value == value && tokens[0].type == type)
  {
    return true;
  }
  else
    return false;
}

void E()
{
  if (NextToken("identifier", "let"))
  {
    Read("identifier", "let");
    D();
    Read("identifier", "in");
    E();
  }
  else if (NextToken("identifier", "fn"))
  {
    Read("identifier", "fn");
    do
    {
      Vb();
    } while (NextToken("identifier", "any") || NextToken("(", "("));
    Read("operator", ".");
    E();
  }
  else
  {
    Ew();
    Read(";", ";");
  }
}

//! ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//! ````````````````````````````````````````````````````````````````````````````
//! == DO NOT CROSS ===== DO NOT CROSS ===== DO NOT CROSS ===== DO NOT CROSS ===
//! ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//! ````````````````````````````````````````````````````````````````````````````

void D()
{
  cout << "Running D" << endl;
}

void Ew()
{
  cout << "Running Ew" << endl;
}

void Vl()
{
  cout << "Running Vl" << endl;
}

void Vb()
{
  cout << "Running Vb" << endl;
  Read("(", "(");
}