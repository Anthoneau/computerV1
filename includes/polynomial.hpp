#pragma once

#include <string>
#include <exception>
#include <iostream>

class Polynomial
{
private:
	std::string	_expr;
	int			_degree;
	int			_discriminant;
	int			_solutions[2];
	int			_a, _b, _c; // corresponding to ax^2 + bx + c = 0

	Polynomial(void);
	Polynomial(Polynomial const &src);
	Polynomial &operator=(Polynomial const &src);

public:
	Polynomial(std::string const &exp);
	~Polynomial();

	class ParseError: public std::exception
	{
		public:
			const char* what() const throw ();
	};

	class SyntaxError: public std::exception
	{
		public:
			const char* what() const throw ();
	};

	class DegreeError: public std::exception
	{
		public:
			const char* what() const throw ();
	};

	std::string const getExpression(void) const;

	void parse();
	void reduced_form();
	void solve();
};
