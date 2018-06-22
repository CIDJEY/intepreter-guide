
#pragma once

#include <Parser.hpp>

struct Intepreter {

	Intepreter(const std::string& input): parser(input) {
		root = parser.parse();
	}

	~Intepreter() {
		delete root;
	}

	int interpret() {
		//Some DFS method to go over AST
		return visit(root);
	}

	std::string rpn_notation() {
		return visit_rpn(root);
	}

	std::string lisp_notation() {
		return visit_lisp(root);
	}

private:
	int visit(ASTNode* node);
	int visit_binop(ASTNode* node);
	int visit_unop(ASTNode* node);
	int visit_integer(ASTNode* node);
	std::string visit_rpn(ASTNode* node);
	std::string visit_lisp(ASTNode* node);

	Parser parser;
	ASTNode* root = nullptr;

};

