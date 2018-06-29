
#include <Lexer.hpp>
#include <stdexcept>

#include <iostream>
#include <algorithm>

Lexer::Lexer(std::ifstream& input) {
	_input = std::string((std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));

	reserved_ids.insert({std::string("BEGIN"), [&]() {
		return begin();
	}});
	reserved_ids.insert({std::string("END"), [&]() {
		return end();
	}});
	reserved_ids.insert({std::string("DIV"), [&]() {
		return divide();
	}});
}

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

Token Lexer::id() {
	uint32_t shift = 0;
	std::string value;
	while (isalpha(_input[_pos + shift]) || (_input[_pos + shift] == '_')) {
		value += _input[_pos + shift];
		shift++;
	}

	std::transform(value.begin(), value.end(), value.begin(), ::toupper);

	auto found = reserved_ids.find(value);
	if (found != reserved_ids.end()) {
		return found->second();
	}

	_pos += shift;
	return Token::make_id(value);
}

Token Lexer::get_next_token() {
	if (_pos == _input.length()) {
		return Token::make_eof();
	}

	char current_char = _input[_pos];

	if(isdigit(current_char)) {
		return integer();
	} else if (isalpha(current_char) || (current_char == '_')) {
		return id();
	} else if (current_char == '+') {
		return plus();
	} else if (current_char == '-') {
		return minus();
	} else if (current_char == '*') {
		return multiplicate();
	} else if (current_char == '(') {
		return lparen();
	} else if (current_char == ')') {
		return rparen();
	} else if (current_char == ';') {
		return semi();
	} else if (current_char == ':' && _input[_pos + 1] == '=') {
		return assign();
	} else if (current_char == '.') {
		return dot();
	} else if (isspace(current_char)) {
		_pos++;
		return get_next_token();
	}
	std::string error("Error while parsing input, current char: ");
	error += current_char;
	throw std::runtime_error(error);
}
