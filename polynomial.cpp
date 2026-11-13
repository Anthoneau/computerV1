#include "polynomial.hpp"

// CONSTRUCTOR, DESTRUCTOR AND OPERATOR(=, <<) OVERLOAD ///////////////////////

Polynomial::Polynomial(std::string const &exp) : _expression(exp) {}

Polynomial::Polynomial(Polynomial const &src) {
	*this = src;
}

Polynomial &Polynomial::operator=(Polynomial const &src) {
	if (this != &src)
	{
		this->_expression = src._expression;
	}
	return *this;
}

Polynomial::~Polynomial() {}

std::ostream &operator<<(std::ostream &o, Polynomial const &src) {
	o << src.getExpression();
	return o;
}

// ERROR HANDLING /////////////////////////////////////////////////////////////

const char* Polynomial::ParseError::what() const throw() {
	return "Parsing Error"; //ameliorer
}

// GETTER /////////////////////////////////////////////////////////////////////

std::string const Polynomial::getExpression(void) const {
	return this->_expression;
}


// FUNCTIONS //////////////////////////////////////////////////////////////////

int Polynomial::parse(void) const {
	for (std::string::iterator it = this._expression.begin(); it )
}