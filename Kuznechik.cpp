#include <iostream>
#include <string>
#include <vector>



int main()
{
	std::string name = "";
	std::cout << "Enter your name: \n";
	std::cin >> name;
	std::cout << "Hello, " + name +'\n';
	return 0;
}

