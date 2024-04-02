#include <iostream>
#include <stack>

int main()
{
  std::stack<int> myStack;

  // Push some elements onto the stack
  // myStack.push(20);
  // myStack.push(30);

  // Get the address of the lowest element
  int *lowestAddress = &myStack.top(); // Address of the lowest element
  std::cout << "Address of the lowest element: " << lowestAddress << std::endl;
  myStack.push(10);
  std::cout << "Address of the lowest element: " << lowestAddress << std::endl;

  // Print the address of the lowest element

  return 0;
}
