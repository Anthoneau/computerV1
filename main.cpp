#include <iostream>
#include <string>
#include <stdio.h>

int main(int argc, char **argv)
{
	std::cout << argc << std::endl;
	std::string arg;
	if (argc == 1)
		std::cin >> arg;
	else if (argc == 2)
		arg = argv[1];
	else
		return 1;
	std::cout << arg << std::endl;
	return 0;
}
