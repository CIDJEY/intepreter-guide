
#pragma once

#include <Parser.hpp>

struct Intepreter {

	Intepreter(std::ifstream& input): parser(input) {
		root = parser.parse();
	}

	~Intepreter() {
		delete root;
	}

	int interpret() {
		//Some DFS method to go over AST
		return visit(root);
	}

	void print_global_scope();

	std::string rpn_notation() {
		return visit_rpn(root);
	}

	std::string lisp_notation() {
		return visit_lisp(root);
	}

private:
	int visit(ASTNode* node);
	int visit_binop(BinOpNode* node);
	int visit_unop(UnOpNode* node);
	int visit_integer(IntegerNode* node);
	int visit_compound(CompoundNode* node);
	int visit_assign(AssignNode* node);
	int visit_var(VarNode* node);
	int visit_noop(NoOpNode* node) {}
	std::string visit_rpn(ASTNode* node);
	std::string visit_lisp(ASTNode* node);

	Parser parser;
	ASTNode* root = nullptr;

	std::unordered_map<std::string, int> global_scope;

};

