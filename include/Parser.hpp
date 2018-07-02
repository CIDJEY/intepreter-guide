
#pragma once

#include <Lexer.hpp>
#include <Node.hpp>

struct Parser {
	Parser(std::ifstream& input): lexer(input) {
		current_token = lexer.get_next_token();
	}

	ASTNode* parse();

private:
	void eat(const Token::type _type);

	ASTNode* compound_statement();
	std::vector<ASTNode*> statement_list();
	ASTNode* statement();
	ASTNode* assignment_statement();
	ASTNode* variable();
	ASTNode* empty();
	ASTNode* term();
	ASTNode* factor();
	ASTNode* expr();
	ASTNode* type_spec();
	std::vector<ASTNode*> variable_declarations();
	std::vector<ASTNode*> declarations();
	ASTNode* block();
	ASTNode* program();

	Lexer lexer;
	Token current_token;
};
