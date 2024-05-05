#include <iostream>

class MyClass
{
public:
  int data;

  // Default constructor
  MyClass()
  {
    data = 0;
  }

  // Parameterized constructor
  MyClass(int val)
  {
    data = val;
  }

  // Copy Constructor
  MyClass(const MyClass &other)
  {
    data = other.data;
  }

  // Assignment Operator Overload
  MyClass &operator=(const MyClass &other)
  {
    if (this != &other)
    {
      data = other.data;
    }
    return *this;
  }
};

int main()
{
  // Creating an object and initializing its data member
  MyClass obj1(10);

  // Creating a copy using the copy constructor
  MyClass obj2 = obj1;

  // Creating another object
  MyClass obj3;

  // Creating a copy using the assignment operator
  obj3 = obj1;

  // Altering an attribute of the copy
  obj2.data = 20;

  // Displaying data of all objects
  std::cout << "Data of obj1: " << obj1.data << std::endl;
  std::cout << "Data of obj2: " << obj2.data << std::endl;
  std::cout << "Data of obj3: " << obj3.data << std::endl;

  return 0;
}
