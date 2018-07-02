
#pragma once

#include <string>

struct Token {
	enum type {
		plus,
		minus,
		multiplicate,
		integer_div,
		real_div,
		integer_const,
		real_const,
		lparen,
		rparen,
		program,
		var,
		begin,
		end,
		integer, //type integer, reserved word
		real, 	 //type real
		semi,
		colon,
		comma,
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

	static Token make_integer_const(const std::string& value) {
		return Token(type::integer_const, value);
	}

	static Token make_real_const(const std::string& value) {
		return Token(type::real_const, value);
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

	static Token make_integer_div() {
		return Token(type::integer_div, "DIV");
	}

	static Token make_real_div() {
		return Token(type::real_div, "/");
	}

	static Token make_lparen() {
		return Token(type::lparen, "(");
	}

	static Token make_rparen() {
		return Token(type::rparen, ")");
	}

	static Token make_program() {
		return Token(type::program, "PROGRAM");
	}

	static Token make_var() {
		return Token(type::var, "VAR");
	}

	static Token make_begin() {
		return Token(type::begin, "BEGIN");
	}

	static Token make_end() {
		return Token(type::end, "END");
	}

	static Token make_integer() {
		return Token(type::integer, "INTEGER");
	}

	static Token make_real() {
		return Token(type::real, "REAL");
	}

	static Token make_semi() {
		return Token(type::semi, ";");
	}

	static Token make_colon() {
		return Token(type::colon, ":");
	}

	static Token make_comma() {
		return Token(type::comma, ",");
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
