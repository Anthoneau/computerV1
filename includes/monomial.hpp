#pragma once

#include <string>

class Monomial
{
	private:
		std::string	_expr;
		long		_coeff;
		int			_degree;
	public:
		Monomial(void);
		Monomial(Monomial const &other);
		
		~Monomial(void);

		Monomial operator=(Monomial const &other);

		long get_coeff(void) const;
		int get_degree(void) const;

		void set_coeff(long const coeff);
		void set_coeff(std::string const expr);
		void set_degree(int const degree);
};
