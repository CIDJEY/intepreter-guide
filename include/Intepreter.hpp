
#pragma once

#include <Parser.hpp>
#include <any>

struct Intepreter {

	Intepreter(std::ifstream& input): parser(input) {
		root = parser.parse();
	}

	~Intepreter() {
		delete root;
	}

	std::any interpret() {
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
	std::any visit(ASTNode* node);
	std::any visit_binop(BinOpNode* node);
	std::any visit_unop(UnOpNode* node);
	std::any visit_number(NumberNode* node);
	int visit_compound(CompoundNode* node);
	int visit_assign(AssignNode* node);
	std::any visit_var(VarNode* node);
	int visit_noop(NoOpNode* node) {}
	std::any visit_program(ProgramNode* node);
	std::any visit_block(BlockNode* node);
	std::any visit_declaration(VarDeclarationNode* node);
	std::any visit_type(TypeNode* node);
	std::string visit_rpn(ASTNode* node);
	std::string visit_lisp(ASTNode* node);

	Parser parser;
	ASTNode* root = nullptr;

	std::unordered_map<std::string, std::any> global_scope;

};

