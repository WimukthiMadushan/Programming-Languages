#include <iostream>

struct NodeB; // Forward declaration of NodeB

struct NodeA
{
  int data;
  NodeB *nextB; // Pointer to NodeB

  // Constructor
  NodeA(int d) : data(d), nextB(nullptr) {}
};

struct NodeB
{
  float value;
  NodeA *prevA; // Pointer to NodeA

  // Constructor
  NodeB(float v) : value(v), prevA(nullptr) {}
};

int main()
{
  // Creating nodes
  NodeA a(10);
  NodeB b(3.14);

  // Establishing connections
  a.nextB = &b;
  b.prevA = &a;

  // Accessing data
  std::cout << "Node A data: " << a.data << std::endl;
  std::cout << "Node B value: " << b.value << std::endl;

  return 0;
}
