#pragma once

#include <string>
#include <exception>
#include <ostream>

class Polynomial
{
private:
	Polynomial(void);

	std::string	_expression;
	int			_degree;
	int			_discriminant;
	int			_solutions[2];
public:
	Polynomial(std::string const &exp);
	Polynomial(Polynomial const &src);
	Polynomial &operator=(Polynomial const &src);
	~Polynomial();

	class ParseError: public std::exception
	{
		public:
			const char* what() const throw ();
	};

	std::string const getExpression(void) const;

	int parse(void) const;
};

std::ostream &operator<<(std::ostream &o, Polynomial const &src);
