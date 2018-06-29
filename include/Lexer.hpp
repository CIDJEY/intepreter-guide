
#pragma once

#include <Token.hpp>

#include <unordered_map>
#include <functional>

#include <fstream>
#include <string>

struct Lexer {
	Lexer(std::ifstream& input);

	Token get_next_token();

	Token integer();
	Token id();

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

	Token begin() {
		_pos += std::string("BEGIN").length();
		return Token::make_begin();
	}

	Token end() {
		_pos += std::string("END").length();
		return Token::make_end();
	}

	Token semi() {
		_pos++;
		return Token::make_semi();
	}

	Token assign() {
		_pos += 2;
		return Token::make_assign();
	}

	Token dot() {
		_pos++;
		return Token::make_dot();
	}

private:
	std::string _input;
	size_t _pos = 0;


	std::unordered_map<std::string, std::function<Token()>> reserved_ids;
};
