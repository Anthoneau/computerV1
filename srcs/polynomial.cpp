#include "polynomial.hpp"

// CONSTRUCTOR AND DESTRUCTOR /////////////////////////////////////////////////

Polynomial::Polynomial(std::string const &exp): _expr(exp) {}
Polynomial::~Polynomial() {}

// ERROR HANDLING /////////////////////////////////////////////////////////////

const char* Polynomial::ParseError::what() const throw() {
	return "Parsing Error"; //ameliorer
}

const char* Polynomial::SyntaxError::what() const throw() {
	return "Syntax error";
}

const char* Polynomial::DegreeError::what() const throw() {
	return "Degree too high or too low";
}

// FUNCTIONS //////////////////////////////////////////////////////////////////

void Polynomial::parse()
{
	//TODO check overflow en int
	for (std::string::iterator it = _expr.begin(); it != _expr.end(); it++) {
		if (*it == 'X' && it + 1 != _expr.end() && *(it + 1) == '^'
			&& it + 2 != _expr.end() && *(it + 2) != '0' && *(it + 2) != '1'
			&& *(it + 2) != '2') {
			throw Polynomial::DegreeError();
		}
	}
}

int is_number(char c)
{
	if (c == '+' || c == '-' || (c >= '0' && c <= '9'))
		return 1;
	return 0;
}

int ft_atoi_equation(std::string::iterator *begin, std::string::iterator end)
{
	long a = 0;
	int sign = 1;

	while ((**begin == '+' || **begin == '-') && *begin != end) {
		if (**begin == '-')
		{
			std::cout << "inversion de signe" << std::endl;
			sign *= -1;
		}
		(*begin)++;
	}

	while (*begin != end && is_number(**begin)) {
		if (**begin == '-' || **begin == '+')
			throw Polynomial::SyntaxError();
		a = a * 10 + (**begin - '0');
		(*begin)++;
	}
	a *= sign;
	std::cout << "a : " << a << std::endl;
	return a;
}

int get_degree(std::string::iterator *begin, std::string::iterator end) {
	while (**begin != '^' && *begin != end)
		(*begin)++;
	while (!is_number(**begin) && *begin != end)
		(*begin)++;
	return ft_atoi_equation(&*begin, end);
}

void Polynomial::reduced_form()
{
	int l_a = 0, l_b = 0, l_c = 0;
	//int r_a = 0, r_b = 0, r_c = 0;

	//std::string::iterator it_begin;
	//std::string::iterator it_end;

	//int is_coeff = 0;
	int temp = 0;
	int degree = 0;

	std::cout << "dans la fonction reduced form j'ai ceci : " << _expr << std::endl;

	for (std::string::iterator it = _expr.begin(); it != _expr.end(); it++) {
		std::cout << "it : " << *it << std::endl;
		if (is_number(*it))
		{
			//is_coeff = 1;
			temp = ft_atoi_equation(&it, _expr.end());
			std::cout << "je ressors ca : " << temp << std::endl;
		}
		if (*it == 'X')
		{
			//degree = get_degree(&it, _expr.end());
			while (*it != '^' && it != _expr.end())
				(it)++;
			while (!is_number(*it) && it != _expr.end())
				(it)++;
			degree = ft_atoi_equation(&it, _expr.end());
			(degree == 0) ? l_c = temp : (degree == 1) ? l_b = temp : l_a = temp;
			//std::cout << " ayant ce degre : " << degree << std::endl;
			std::cout << l_a << " X^2 " << l_b << " X^1 " << l_c << " X^0" << std::endl;
		}
	}
}

//void disriminant(int a, int b, int c) {}

void Polynomial::solve()
{
	try
	{
		parse();
		reduced_form();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
