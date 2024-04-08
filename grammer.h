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
      if (tokens[0].type == "identifier")
      {
        string token = "<ID:" + tokens[0].value + ">";
        Build_tree(token, 0);
      }
      else if (tokens[0].type == "integer")
      {
        string token = "<INT:" + tokens[0].value + ">";
        Build_tree(token, 0);
      }
      else if (tokens[0].type == "string")
      {
        string token = "<STR:" + tokens[0].value + ">";
        Build_tree(token, 0);
      }
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
    string val = tokens[0].value;
    if (isReserved(val))
    {
      return false;
    }
    else
    {
      return true;
    }
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
    Build_tree("let", 2);
  }
  else if (NextToken("identifier", "fn"))
  {
    int n = 1;
    Read("identifier", "fn");
    do
    {
      Vb();
      n++;
    } while (NextToken("identifier", "any") || NextToken("(", "("));
    Read("operator", ".");
    E();
    dt_bu.push_back("E -> 'fn' Vb+ '.' E");
    Build_tree("lambda", n);
  }
  else
  {
    Ew();
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
    dt_bu.push_back("Ew -> T 'where' Dr");
    Build_tree("where", 2);
  }
  else
  {
    dt_bu.push_back("Ew -> T");
  }
}

void T()
{
  Ta();
  if (NextToken(",", ","))
  {
    int n = 1;
    do
    {
      Read(",", ",");
      Ta();
      n++;
    } while (NextToken(",", ","));
    dt_bu.push_back("T -> Ta ( ',' Ta )+");
    Build_tree("tau", n);
  }
  else
  {
    dt_bu.push_back("T -> Ta");
  }
}

void Ta()
{
  Tc();
  dt_bu.push_back("Ta -> Tc");
  while (NextToken("identifier", "aug"))
  {
    Read("identifier", "aug");
    Tc();
    dt_bu.push_back("Ta -> Ta 'aug' Tc");
    Build_tree("aug", 2);
  }
}

void Tc()
{
  B();
  if (NextToken("operator", "->"))
  {
    Read("operator", "->");
    Tc();
    Read("operator", "|");
    Tc();
    dt_bu.push_back("Tc -> B '->' Tc '|' Tc");
    Build_tree("->", 3);
  }
  else
  {
    dt_bu.push_back("Tc -> B");
  }
}

void B()
{
  Bt();
  dt_bu.push_back("B -> Bt");
  while (NextToken("identifier", "or"))
  {
    Read("identifier", "or");
    Bt();
    dt_bu.push_back("B -> B 'or' Bt");
    Build_tree("or", 2);
  }
}

void Bt()
{
  Bs();
  dt_bu.push_back("Bt -> Bs");
  while (NextToken("operator", "&"))
  {
    Read("operator", "&");
    Bs();
    dt_bu.push_back("Bt -> Bt '&' Bs");
    Build_tree("&", 2);
  }
}

void Bs()
{
  if (NextToken("identifier", "not"))
  {
    Read("identifier", "not");
    Bp();
    dt_bu.push_back("Bs -> 'not' Bp");
    Build_tree("not", 1);
  }
  else
  {
    Bp();
    dt_bu.push_back("Bs -> Bp");
  }
}

void Bp()
{
  A();
  if (NextToken("identifier", "gr"))
  {
    Read("identifier", "gr");
    A();
    dt_bu.push_back("Bp -> A ('gr'|'>') A");
    Build_tree("gr", 2);
  }
  else if (NextToken("operator", ">"))
  {
    Read("operator", ">");
    A();
    dt_bu.push_back("Bp -> A ('gr'|'>') A");
    Build_tree("gr", 2);
  }
  else if (NextToken("identifier", "ge"))
  {
    Read("identifier", "ge");
    A();
    dt_bu.push_back("Bp -> A ('ge'|'>=') A");
    Build_tree("ge", 2);
  }
  else if (NextToken("operator", ">="))
  {
    Read("operator", ">=");
    A();
    dt_bu.push_back("Bp -> A ('ge'|'>=') A");
    Build_tree("ge", 2);
  }
  else if (NextToken("identifier", "ls"))
  {
    Read("identifier", "ls");
    A();
    dt_bu.push_back("Bp -> A ('ls'|'<') A");
    Build_tree("ls", 2);
  }
  else if (NextToken("operator", ">="))
  {
    Read("operator", "<");
    A();
    dt_bu.push_back("Bp -> A ('ls'|'<') A");
    Build_tree("ls", 2);
  }
  else if (NextToken("identifier", "le"))
  {
    Read("identifier", "le");
    A();
    dt_bu.push_back("Bp -> A ('le'|'<=') A");
    Build_tree("le", 2);
  }
  else if (NextToken("operator", "<="))
  {
    Read("operator", "<=");
    A();
    dt_bu.push_back("Bp -> A ('le'|'<=') A");
    Build_tree("le", 2);
  }
  else if (NextToken("identifier", "eq"))
  {
    Read("identifier", "eq");
    A();
    dt_bu.push_back("Bp -> A 'eq' A");
    Build_tree("eq", 2);
  }
  else if (NextToken("identifier", "ne"))
  {
    Read("identifier", "ne");
    A();
    dt_bu.push_back("Bp -> A 'ne' A");
    Build_tree("ne", 2);
  }
  else
  {
    dt_bu.push_back("Bp -> A");
  }
}

void A()
{
  if (NextToken("operator", "+"))
  {
    Read("operator", "+");
    At();
    dt_bu.push_back("A -> '+' At");
  }
  else if (NextToken("operator", "-"))
  {
    Read("operator", "-");
    At();
    dt_bu.push_back("A -> '-' At");
    Build_tree("neg", 1);
  }
  else
  {
    At();
    dt_bu.push_back("A -> At");
    while (NextToken("operator", "+") || NextToken("operator", "-"))
    {
      if (NextToken("operator", "+"))
      {
        Read("operator", "+");
        At();
        dt_bu.push_back("A -> A '+' At");
        Build_tree("+", 2);
      }
      else
      {
        Read("operator", "-");
        At();
        dt_bu.push_back("A -> A '-' At");
        Build_tree("-", 2);
      }
    }
  }
}

void At()
{
  Af();
  dt_bu.push_back("At -> Af");
  while (NextToken("operator", "*") || NextToken("identifier", "/"))
  {
    if (NextToken("operator", "*"))
    {
      Read("operator", "*");
      Af();
      dt_bu.push_back("At -> At '*' Af");
      Build_tree("*", 2);
    }
    else
    {
      Read("operator", "/");
      Af();
      dt_bu.push_back("At -> At '/' Af");
      Build_tree("/", 2);
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
    dt_bu.push_back("Af -> Ap '**' Af");
    Build_tree("**", 2);
  }
  else
  {
    dt_bu.push_back("Af -> Ap");
  }
}

void Ap()
{
  R();
  dt_bu.push_back("Ap -> R");
  while (NextToken("operator", "@"))
  {
    Read("operator", "@");
    Read("identifier", "any");
    R();
    dt_bu.push_back("Ap -> Ap '@' '<identifier>' R");
    Build_tree("@", 3);
  };
}

void R()
{
  Rn();
  dt_bu.push_back("R -> Rn");
  while (NextToken("identifier", "any") || NextToken("integer", "any") || NextToken("string", "any") || NextToken("identifier", "true") || NextToken("identifier", "false") || NextToken("identifier", "nil") || NextToken("(", "(") || NextToken("identifier", "dummy"))
  {
    Rn();
    dt_bu.push_back("R -> R Rn");
    Build_tree("gamma", 2);
  }
}

void Rn()
{
  if (NextToken("identifier", "true"))
  {
    Read("identifier", "true");
    dt_bu.push_back("Rn -> 'true'");
    Build_tree("true", 0);
  }
  else if (NextToken("identifier", "false"))
  {
    Read("identifier", "false");
    dt_bu.push_back("Rn -> 'false'");
    Build_tree("false", 0);
  }
  else if (NextToken("identifier", "nil"))
  {
    Read("identifier", "nil");
    dt_bu.push_back("Rn -> 'nil'");
    Build_tree("nil", 0);
  }
  else if (NextToken("identifier", "dummy"))
  {
    Read("identifier", "dummy");
    dt_bu.push_back("Rn -> 'dummy'");
    Build_tree("dummy", 0);
  }
  else if (NextToken("(", "("))
  {
    Read("(", "(");
    E();
    Read(")", ")");
    dt_bu.push_back("Rn -> '(' E ')'");
  }
  else if (NextToken("identifier", "any"))
  {
    Read("identifier", "any");
    dt_bu.push_back("Rn -> '<identifier>'");
  }
  else if (NextToken("integer", "any"))
  {
    Read("integer", "any");
    dt_bu.push_back("Rn -> '<integer>'");
  }
  else if (NextToken("string", "any"))
  {
    Read("string", "any");
    dt_bu.push_back("Rn -> '<string>'");
  }
}

void D()
{
  Da();
  if (NextToken("identifier", "within"))
  {
    Read("identifier", "within");
    D();
    dt_bu.push_back("D -> Da 'within' D");
    Build_tree("within", 2);
  }
  else
  {
    dt_bu.push_back("D -> Da");
  }
}

void Da()
{
  Dr();
  if (NextToken("identifier", "and"))
  {
    int n = 1;
    do
    {
      Read("identifier", "and");
      Dr();
      n++;
    } while (NextToken("identifier", "and"));
    dt_bu.push_back("Da -> Dr ( 'and' Dr )+");
    Build_tree("and", n);
  }
  else
  {
    dt_bu.push_back("Da -> Dr");
  }
}

void Dr()
{
  if (NextToken("identifier", "rec"))
  {
    Read("identifier", "rec");
    Db();
    dt_bu.push_back("Dr -> 'rec' Db");
    Build_tree("rec", 1);
  }
  else
  {
    Db();
    dt_bu.push_back("Dr -> Db");
  }
}

void Vb()
{
  if (NextToken("identifier", "any"))
  {
    Read("identifier", "any");
    dt_bu.push_back("Vb -> '<identifier>'");
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
      dt_bu.push_back("Vb -> '(' ')'");
      Build_tree("()", 0);
    }
  }
}

void Db()
{
  if (NextToken("(", "("))
  {
    Read("(", "(");
    D();
    Read(")", ")");
    dt_bu.push_back("Db -> '(' D ')'");
  }
  else if ((tokens[1].type == "," && tokens[1].value == ",") || (tokens[1].type == "operator" && tokens[1].value == "="))
  {
    Vl();
    Read("operator", "=");
    E();
    dt_bu.push_back("Db -> Vl '=' E");
    Build_tree("=", 2);
  }
  else
  {
    Read("identifier", "any");
    int n = 2;
    do
    {
      Vb();
      n++;
    } while (NextToken("identifier", "any") || NextToken("(", "("));
    Read("operator", "=");
    E();
    dt_bu.push_back("Db -> '<identifier>' Vb+ '=' E");
    Build_tree("fcn_form", n);
  }
}

void Vl()
{
  int n = 1;
  Read("identifier", "any");
  while (NextToken(",", ","))
  {
    Read(",", ",");
    Read("identifier", "any");
    n++;
  }
  dt_bu.push_back("Vl -> '<identifier>' list ','");
  if (n > 1)
  {
    Build_tree(",", n);
  }
}