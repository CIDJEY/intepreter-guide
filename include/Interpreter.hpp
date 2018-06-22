
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

	std::string rpn() {
		return visit_rpn(root);
	}

private:
	int visit(ASTNode* node);
	std::string visit_rpn(ASTNode* node);

	Parser parser;
	ASTNode* root = nullptr;

};

