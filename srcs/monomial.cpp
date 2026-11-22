#include "monomial.hpp"

Monomial::Monomial(void) {}

Monomial::Monomial(Monomial const &other)
{
	*this = other;
}

Monomial::~Monomial(void) {}

Monomial Monomial::operator=(Monomial const &other)
{
	if (this != &other)
	{
		_expr = other._expr;
		_coeff = other.get_coeff();
		_degree = other.get_degree();
	}
	return *this;
}

long Monomial::get_coeff(void) const
{
	return _coeff;
}

int Monomial::get_degree(void) const
{
	return _degree;
}

void Monomial::set_coeff(long const coeff)
{
	_coeff = coeff;
}

void Monomial::set_coeff(std::string const expr)
{
	(void)expr;
}

void Monomial::set_degree(int const degree)
{
	_degree = degree;
}
