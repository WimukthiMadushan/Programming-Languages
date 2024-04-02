#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void E();
void Ew();
void T();
void Ta();
void Tc();
void B();
void Bt();
void Bs();
void Bp();
void A();
void At();
void Af();
void Ap();
void R();
void Rn();
void D();
void Da();
void Dr();
void Db();
void Vb();
void Vl();

void Read(string type, string value)
{
  if (value == "any")
  {
    if (tokens[0].type == type)
    {
      tokens.erase(tokens.begin());
    }
    else
    {
      cout << "Expected \"" + type + "\" : \"" + value + "\", got \"" + tokens[0].type + "\" : \"" + tokens[0].value << "\"" << endl;
      throw "Error";
    }
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
    dt_bu.push_back("E -> 'let' D 'in' E");
  }
  else if (NextToken("identifier", "fn"))
  {
    int n = 0;
    dt_td.push_back("E -> 'fn' Vb+ '.' E");
    Read("identifier", "fn");
    do
    {
      Vb();
      n++;
    } while (NextToken("identifier", "any") || NextToken("(", "("));
    Read("operator", ".");
    E();
    dt_bu.push_back("E -> 'fn' Vb+ '.' E");
  }
  else
  {
    Ew();
    Read(";", ";");
    dt_bu.push_back("E -> Ew");
  }
}

void Ew()
{
  T();
  if (NextToken("identifier", "where"))
  {
    Read("identifier", "where");
    Dr();
  }
  else
  {
    Read(";", ";");
  }
}

void T()
{
  Ta();
  Read(";", ";");
  do
  {
    Read("operator", ",");
    Ta();
  } while (NextToken("operator", ","));
}

void Ta()
{
  Tc();
  Read(";", ";");
  while (NextToken("identifier", "aug"))
  {
    Read("identifier", "aug");
    Tc();
  }
}

void Tc()
{
  B();
  if (NextToken(";", ";"))
  {
    Read(";", ";");
  }
  else
  {
    Read("opeartor", "->");
    Tc();
    Read("opeartor", "|");
    Tc();
  }
}

void B()
{
  Bt();
  Read(";", ";");
  while (NextToken("identifier", "or"))
  {
    Read("identifier", "or");
    Bt();
  }
}

void Bt()
{
  Bs();
  while (NextToken("operator", "&"))
  {
    Read("operator", "&");
    Bs();
  }
}

void Bs()
{
  if (NextToken("operator", "not"))
  {
    Read("operator", "not");
    Bp();
  }
  else
  {
    Bp();
  }
}

void Bp()
{
  A();
  if (NextToken("identifier", "gr"))
  {
    Read("identifier", "gr");
    A();
  }
  else if (NextToken("operator", ">"))
  {
    Read("operator", ">");
    A();
  }
  else if (NextToken("identifier", "ge"))
  {
    Read("identifier", "ge");
    A();
  }
  else if (NextToken("operator", ">="))
  {
    Read("operator", ">=");
    A();
  }
  else if (NextToken("identifier", "ls"))
  {
    Read("identifier", "ls");
    A();
  }
  else if (NextToken("operator", ">="))
  {
    Read("operator", "<");
  }
  else if (NextToken("identifier", "le"))
  {
    Read("identifier", "le");
    A();
  }
  else if (NextToken("operator", "<="))
  {
    Read("operator", "<=");
    A();
  }
  else if (NextToken("identifier", "eq"))
  {
    Read("identifier", "eq");
    A();
  }
  else if (NextToken("identifier", "ne"))
  {
    Read("identifier", "ne");
    A();
  }
  else
  {
    Read(";", ";");
  }
}

void A()
{
  if (NextToken("operator", "+"))
  {
    Read("operator", "+");
    At();
  }
  else if (NextToken("operator", "-"))
  {
    Read("operator", "-");
    At();
  }
  else
  {
    At();
    Read(";", ";");
    while (NextToken("operator", "+") || NextToken("operator", "-"))
    {
      if (NextToken("operator", "+"))
      {
        Read("operator", "+");
        At();
      }
      else
      {
        Read("operator", "-");
        At();
      }
    }
  }
}

void At()
{
  Af();
  Read(";", ";");
  while (NextToken("operator", "*") || NextToken("identifier", "/"))
  {
    if (NextToken("operator", "*"))
    {
      Read("operator", "*");
      Af();
    }
    else
    {
      Read("operator", "/");
      Af();
    }
  }
}

void Af()
{
  Ap();
  if (NextToken("operator", "**"))
  {
    Read("operator", "**");
    Af();
  }
  else
  {
    Read(";", ";");
  }
}

void Ap()
{
  R();
  Read(";", ";");
  while (NextToken("operator", "@"))
  {
    Read("operator", "@");
    Read("identifier", "any");
    R();
  };
}

void R()
{
  Rn();
  while (NextToken("identifier", "any") || NextToken("integer", "any") || NextToken("string", "any") || NextToken("identifier", "true") || NextToken("identifier", "false") || NextToken("identifier", "nil") || NextToken("(", "(") || NextToken("identifier", "dummy"))
  {
    Rn();
  }
}

void Rn()
{
  if (NextToken("identifier", "true"))
  {
    Read("identifier", "true");
  }
  else if (NextToken("identifier", "false"))
  {
    Read("identifier", "false");
  }
  else if (NextToken("identifier", "nil"))
  {
    Read("identifier", "nil");
  }
  else if (NextToken("identifier", "dummy"))
  {
    Read("identifier", "dummy");
  }
  else if (NextToken("(", "("))
  {
    Read("(", "(");
    E();
    Read(")", ")");
  }
  else if (NextToken("identifier", "any"))
  {
    Read("identifier", "any");
  }
  else if (NextToken("integer", "any"))
  {
    Read("integer", "any");
  }
  else if (NextToken("string", "any"))
  {
    Read("string", "any");
  }
}

void D()
{
  Da();
  if (NextToken("identifier", "within"))
  {
    Read("identifier", "within");
    D();
  }
  else
  {
    Read(";", ";");
  }
}

void Da()
{
  Dr();
  if (NextToken(";", ";"))
  {
    Read(";", ";");
  }
  else
  {
    do
    {
      Read("identifier", "and");
      Dr();
    } while (NextToken("identifier", "and"));
  }
}

void Dr()
{
  if (NextToken("identifier", "rec"))
  {
    Read("identifier", "rec");
    Db();
  }
  else
  {
    Db();
    Read(";", ";");
  }
}

void Db()
{ // TODO: complete this, How is this LL(1)
  cout << "Running Db" << endl;
}

void Vb()
{
  if (NextToken("identifier", "any"))
  {
    Read("identifier", "any");
  }
  else if (NextToken("(", "("))
  {
    Read("(", "(");
    if (NextToken("identifier", "any"))
    {
      Vl();
      Read(")", ")");
    }
    else
    {
      Read(")", ")");
    }
  }
}

void Vl()
{
  Read("identifier", "any");
  while (NextToken(",", ","))
  {
    Read(",", ",");
    Read("identifier", "any");
  }
}