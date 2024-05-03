#include <iostream>
#include <vector>
#include <string>

enum class Type
{
  INTEGER,
  STRING
};

std::string typeToString(Type t)
{
  switch (t)
  {
  case Type::INTEGER:
    return "INTEGER";
  case Type::STRING:
    return "STRING";
  default:
    return "UNKNOWN";
  }
}

class Base
{
protected:
  Type type;

public:
  Base(Type t) : type(t) {}
  virtual ~Base() {}
  virtual void print() const = 0;
  Type getType() const { return type; }
};

class Integer : public Base
{
private:
  int value;

public:
  Integer(int val) : Base(Type::INTEGER), value(val) {}
  void print() const override
  {
    std::cout << "Type: " << typeToString(getType()) << ", Value: " << value << std::endl;
  }
};

class String : public Base
{
private:
  std::string value;

public:
  String(const std::string &val) : Base(Type::STRING), value(val) {}
  void print() const override
  {
    std::cout << "Type: " << typeToString(getType()) << ", Value: " << value << std::endl;
  }
};

int main()
{
  std::vector<Base *> objects;

  objects.push_back(new Integer(42));
  objects.push_back(new String("Hello, world!"));

  for (const auto &obj : objects)
  {
    obj->print();
  }

  // Clean up
  for (auto &obj : objects)
  {
    delete obj;
  }

  return 0;
}
