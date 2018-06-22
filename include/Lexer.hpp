
#pragma once

#include <Token.hpp>

struct Lexer {
	Lexer(const std::string& input): _input(input) {}

	Token get_next_token();

	Token integer();

	Token plus() {
		_pos++;
		return Token::make_plus();
	}

	Token minus() {
		_pos++;
		return Token::make_minus();
	}

	Token multiplicate() {
		_pos++;
		return Token::make_multiplicate();
	}

	Token divide() {
		_pos++;
		return Token::make_divide();
	}

	Token lparen() {
		_pos++;
		return Token::make_lparen();
	}

	Token rparen() {
		_pos++;
		return Token::make_rparen();
	}

private:
	const std::string _input;
	size_t _pos = 0;
};
