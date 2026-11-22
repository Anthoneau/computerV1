#include <iostream>
#include <string>
#include <stdio.h>
#include "polynomial.hpp"

void run(std::string line)
{
	if (line.empty())
		return ;
	Polynomial polynomial(line);
	try
	{
		polynomial.solve();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

int main(int argc, char **argv)
{
	if (argc == 1)
		for (std::string line; std::getline(std::cin, line);)
			run(line);
	else if (argc == 2)
		run(argv[1]);
	else
		return 1;
	return 0;
}
