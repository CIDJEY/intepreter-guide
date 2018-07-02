
#pragma once

#include <Token.hpp>

#include <unordered_map>
#include <functional>

#include <fstream>
#include <string>

struct Lexer {
	Lexer(std::ifstream& input);

	Token get_next_token();

	Token number();
	Token integer_const();
	Token real_const();
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

	Token integer_div() {
		_pos += std::string("DIV").length();
		return Token::make_integer_div();
	}

	Token real_div() {
		_pos++;
		return Token::make_real_div();
	}

	Token lparen() {
		_pos++;
		return Token::make_lparen();
	}

	Token rparen() {
		_pos++;
		return Token::make_rparen();
	}

	Token program() {
		_pos += std::string("PROGRAM").length();
		return Token::make_program();
	}

	Token var() {
		_pos += std::string("VAR").length();
		return Token::make_var();
	}

	Token begin() {
		_pos += std::string("BEGIN").length();
		return Token::make_begin();
	}

	Token end() {
		_pos += std::string("END").length();
		return Token::make_end();
	}

	Token integer() {
		_pos += std::string("INTEGER").length();
		return Token::make_integer();
	}

	Token real() {
		_pos += std::string("REAL").length();
		return Token::make_real();
	}

	Token semi() {
		_pos++;
		return Token::make_semi();
	}

	Token colon() {
		_pos++;
		return Token::make_colon();
	}

	Token comma() {
		_pos++;
		return Token::make_comma();
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

	void skip_comments();

	std::unordered_map<std::string, std::function<Token()>> reserved_ids;
};
