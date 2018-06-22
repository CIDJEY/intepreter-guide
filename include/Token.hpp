
#pragma once

#include <string>

struct Token {
	enum type {
		plus,
		minus,
		multiplicate,
		divide,
		integer,
		lparen,
		rparen,
		eof
	};

	Token() = default;
	Token(const type type, const std::string& value): _type(type), _value(value) {}

	type get_type() {
		return _type;
	}

	std::string get_value() {
		return _value;
	}

	static Token make_integer(const std::string& value) {
		return Token(type::integer, value);
	}

	static Token make_plus() {
		return Token(type::plus, "+");
	}

	static Token make_minus() {
		return Token(type::minus, "-");
	}

	static Token make_multiplicate() {
		return Token(type::multiplicate, "*");
	}

	static Token make_divide() {
		return Token(type::divide, "/");
	}

	static Token make_lparen() {
		return Token(type::lparen, "(");
	}

	static Token make_rparen() {
		return Token(type::rparen, ")");
	}

	static Token make_eof() {
		return Token(type::eof, "");
	}

private:
	type _type;
	std::string _value;
};
