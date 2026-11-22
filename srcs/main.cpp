#include <iostream>
#include <string>
#include <stdio.h>
#include "polynomial.hpp"

int main(int argc, char **argv)
{
	std::string arg;
	if (argc == 1)
		std::cin >> arg;
	else if (argc == 2)
		arg = argv[1];
	else
		return 1;	

	//std::cout << arg << std::endl;

	Polynomial polynomial(arg);
	try
	{
		polynomial.solve();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
