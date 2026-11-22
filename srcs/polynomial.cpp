#include "polynomial.hpp"

// CONSTRUCTOR AND DESTRUCTOR /////////////////////////////////////////////////

Polynomial::Polynomial(std::string const &exp): _expr(exp) {
	_lh_side.reserve(3);
	_rh_side.reserve(3);

	for (int i = 0; i != 3; i++)
	{
		_lh_side[i].set_degree(i);
		_rh_side[i].set_degree(i);
	}
}
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

//int monomial_end(char c)
//{
//	if (c == '+' || c == '-' || c == '=')
//	{
//		std::cout << "*it : " << c << std::endl;
//		return 1;
//	}
//	return 0;
//}

int find_sequence(char c, const char *sequence)
{
	if (!sequence)
		return 0;
	for (int i = 0; sequence[i]; i++)
		if (c == sequence[i])
			return 1;
	return 0;
}

void find_parasite(std::string monomial)
{
	int var = 0;
	int power = 0;
	int star = 0;
	for (std::string::iterator it = monomial.begin(); it != monomial.end(); it++)
	{
		if (!find_sequence(*it, " +-=0123456789X^*"))
		{
			std::cout << "caractere parasite : " << *it << std::endl;
			throw Polynomial::SyntaxError();
		}

		if (*it == 'X')
			var++;
		else if (*it == '^')
			power++;
		else if (*it == '*')
			star++;
		if (var > 1 || power > 1 || star > 1)
			throw Polynomial::SyntaxError();
	}
}

void extract_and_check_monomial(std::string monomial)
{
	//int f_coeff = 0;
	//int f_x = 0;
	//int f_var = 0;
	std::cout << "monomial : " << monomial << std::endl;
	if (monomial.empty())
	{
		std::cout << "monome vide" << std::endl;
		throw Polynomial::SyntaxError();
	}
	find_parasite(monomial);
}

void Polynomial::parse()
{
	/*
		TODO
		check overflow en int (2147483647)
		check "2 147 483 647X^2", ca fonctionne pourtant il y a erreur de syntax
		erreur de syntax 
		erreur avec "1 + 19348X^2=0X^0", le second monome ne prend que "19348X^"
	 */

	size_t begin_pos = 0;
	size_t end_pos = 0;

	if (_expr.length() == std::string::npos)
	{
		std::cout << "expression trop longue" << std::endl;
		throw SyntaxError();
	}

	for (std::string::iterator it = _expr.begin(); it != _expr.end(); it++)
	{
		end_pos++;
		//if (monomial_end(*it) || it + 1 == _expr.end())
		if (find_sequence(*it, "+-=") || it + 1 == _expr.end())
		{
			std::cout << "begin : " << begin_pos << std::endl;
			std::cout << "end : " << end_pos << std::endl;
			size_t len = end_pos - begin_pos - 1;
			if (it + 1 == _expr.end())
				len = std::string::npos;
			extract_and_check_monomial(_expr.substr(begin_pos, len));
			begin_pos = end_pos - 1;
		}
	}
	if (begin_pos == 0 && end_pos == _expr.length())
	{
		std::cout << "only one monomial or syntax error" << std::endl;
		throw SyntaxError();
	}
}

//int is_number(char c)
//{
//	if (c == '+' || c == '-' || (c >= '0' && c <= '9'))
//		return 1;
//	return 0;
//}

int ft_atoi_equation(std::string::iterator *begin, std::string::iterator end)
{
	long a = 0;
	int sign = 1;

	while (*begin != end && (**begin == '+' || **begin == '-' || **begin == ' ')) {
		if (**begin == '-')
		{
			//std::cout << "inversion de signe" << std::endl;
			sign *= -1;
		}
		(*begin)++;
	}

	//while (*begin != end && is_number(**begin))
	while (*begin != end && find_sequence(**begin, "+-0123456789"))
	{
		//std::cout << "boucle 2 atoi" << std::endl;
		//if (**begin == '-' || **begin == '+')
		//	throw Polynomial::SyntaxError();
		a = a * 10 + (**begin - '0');
		if (*begin + 1 != end)
			(*begin)++;
		else
			break ;
	}
	a *= sign;
	//std::cout << "a : " << a << std::endl;
	return a;
}

int get_degree(std::string::iterator *begin, std::string::iterator end) {
	//pas encore correct, il faut d'abord avoir toute la reduced form avant 
	//determiner le degree d'une expr
	while (*begin != end && **begin != '^')
	{
		(*begin)++;
		//std::cout << "boucle 1 get degree" << std::endl;
	}
	//while (*begin != end && !is_number(**begin))
	while (*begin != end && !find_sequence(**begin, "+-0123456789"))
	{
		(*begin)++;
		//std::cout << "boucle 2 get degree" << std::endl;
	}
	return ft_atoi_equation(&*begin, end);
}

void Polynomial::reduced_form()
{
	int l_a = 0, l_b = 0, l_c = 0;
	int r_a = 0, r_b = 0, r_c = 0;
	int temp = 0;
	int degree = 0;
	int left = 1;

	for (std::string::iterator it = _expr.begin(); it != _expr.end(); it++) {
		if (*it == '=')
			left = 0;
		//std::cout << "it : " << *it << std::endl;
		//if (is_number(*it))
		if (find_sequence(*it, "+-0123456789"))
		{
			temp = ft_atoi_equation(&it, _expr.end());
			//std::cout << "je ressors ca : " << temp << std::endl;
		}
		if (*it == 'X')
		{
			degree = get_degree(&it, _expr.end());
			//std::cout << "je ressors ce degré : " << degree << std::endl;
			//while (it != _expr.end() && *it != '^')
			//	it++;
			//while (it != _expr.end() && !is_number(*it))
			//	it++;
			//degree = ft_atoi_equation(&it, _expr.end());
			(left)
			? (degree == 0) ? l_c = temp : (degree == 1) ? l_b = temp : l_a = temp
			: (degree == 0) ? r_c = temp : (degree == 1) ? r_b = temp : r_a = temp;
			//std::cout << " ayant ce degre : " << degree << std::endl;
		}
		if (it == _expr.end())
			break ;
	}
	std::cout << l_a << " X^2 +" << l_b << " X^1 +" << l_c << " X^0 = ";
	std::cout << r_a << " X^2 +" << r_b << " X^1 +" << r_c << " X^0 " << std::endl;
}

//void disriminant(int a, int b, int c) {}

void Polynomial::solve()
{
	try
	{
		parse();
		//reduced_form();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
