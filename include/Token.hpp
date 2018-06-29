
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
		begin,
		end,
		semi,
		assign,
		dot,
		id,
		eof,
		empty
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
		return Token(type::divide, "DIV");
	}

	static Token make_lparen() {
		return Token(type::lparen, "(");
	}

	static Token make_rparen() {
		return Token(type::rparen, ")");
	}

	static Token make_begin() {
		return Token(type::begin, "BEGIN");
	}

	static Token make_end() {
		return Token(type::end, "END");
	}

	static Token make_semi() {
		return Token(type::semi, ";");
	}

	static Token make_assign() {
		return Token(type::assign, ":=");
	}

	static Token make_dot() {
		return Token(type::dot, ".");
	}

	static Token make_id(const std::string& id) {
		return Token(type::id, id);
	}

	static Token make_eof() {
		return Token(type::eof, "");
	}

	static Token make_empty() {
		return Token(type::empty, "");
	}

private:
	type _type;
	std::string _value;
};
