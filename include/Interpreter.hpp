
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
		visit(root);
	}

private:
	int visit(ASTNode* node);

	Parser parser;
	ASTNode* root = nullptr;

};

