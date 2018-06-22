
#include <Lexer.hpp>
#include <stdexcept>

Token Lexer::integer() {
	uint32_t shift = 0;
	std::string value;
	while (isdigit(_input[_pos + shift])) {
		value += _input[_pos + shift];
		shift++;
	}
	_pos += shift;

	return Token::make_integer(value);
}

Token Lexer::get_next_token() {
	if (_pos == _input.length()) {
		return Token::make_eof();
	}

	char current_char = _input[_pos];

	if(isdigit(current_char)) {
		return integer();
	} else if (current_char == '+') {
		return plus();
	} else if (current_char == '-') {
		return minus();
	} else if (current_char == '*') {
		return multiplicate();
	} else if (current_char == '/') {
		return divide();
	} else if (current_char == '(') {
		return lparen();
	} else if (current_char == ')') {
		return rparen();
	} else if (current_char == ' ') {
		_pos++;
		return get_next_token();
	}
	throw std::runtime_error("Error while parsing input");
}
