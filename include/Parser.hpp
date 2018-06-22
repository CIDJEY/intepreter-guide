
#pragma once

#include <Lexer.hpp>
#include <Node.hpp>

struct Parser {
	Parser(const std::string& input): lexer(input) {
		current_token = lexer.get_next_token();
	}

	ASTNode* parse() {
		return expr();
	}

private:
	void eat(const Token::type _type);

	ASTNode* term();
	ASTNode* factor();
	ASTNode* expr();

	Lexer lexer;
	Token current_token;
};
