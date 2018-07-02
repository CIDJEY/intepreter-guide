
#pragma once

#include <Token.hpp>
#include <vector>

struct ASTNode {
	enum type {
		binop,
		unop,
		number,
		compound,
		assign,
		var,
		var_type,
		var_declaration,
		block,
		program,
		noop,
	};

	ASTNode(Token t, type type): t(t), _type(type) {}

	type get_type() {
		return _type;
	}

	Token t;
	type _type;
};

struct BinOpNode: public ASTNode {
	~BinOpNode() {
		delete left;
		delete right;
	}

	BinOpNode(Token t, ASTNode* left, ASTNode* right):
		ASTNode(t, ASTNode::type::binop),
		left(left),
		right(right) {}

	ASTNode* left = nullptr;
	ASTNode* right = nullptr;

};


struct UnOpNode: public ASTNode {
	UnOpNode(Token t, ASTNode* expr):
		ASTNode(t, ASTNode::type::unop),
		expr(expr)  {}

	~UnOpNode() {
		delete expr;
	}

	ASTNode* expr = nullptr;
};

struct NumberNode: public ASTNode {
	NumberNode(Token t): ASTNode(t, ASTNode::type::number) {}
};

struct CompoundNode: public ASTNode {
	CompoundNode(): ASTNode(Token::make_empty(), ASTNode::type::compound) {}

	~CompoundNode() {
		for (auto node: children) {
			delete node;
		}
	}

	std::vector<ASTNode*> children;
};

struct VarNode: public ASTNode {
	VarNode(Token t): ASTNode(t, ASTNode::type::var) {}
};

struct AssignNode: public ASTNode {
	AssignNode(ASTNode* var, ASTNode* expr):
		ASTNode(Token::make_assign(), ASTNode::type::assign),
		var(var),
		expr(expr) {}

	~AssignNode() {
		delete var;
		delete expr;
	}

	ASTNode* var = nullptr;
	ASTNode* expr = nullptr;
};


struct TypeNode: public ASTNode {
	TypeNode(Token t): ASTNode(t, ASTNode::type::var_type) {}
};

struct VarDeclarationNode: public ASTNode {
	VarDeclarationNode(ASTNode* var, ASTNode* type):
		ASTNode(Token::make_var(), ASTNode::type::var_declaration),
		var(var),
		type(type) {}
	~VarDeclarationNode() {
		delete var;
		delete type;
	}

	ASTNode* var = nullptr;
	ASTNode* type = nullptr;
};

struct BlockNode: public ASTNode {
	BlockNode(const std::vector<ASTNode*> declarations, ASTNode* compound_statement):
		ASTNode(Token::make_empty(), ASTNode::type::block),
		declarations(declarations),
		compound_statement(compound_statement) {}

	~BlockNode() {
		for (auto decl: declarations) {
			delete decl;
		}
		delete compound_statement;
	}

	std::vector<ASTNode*> declarations;
	ASTNode* compound_statement = nullptr;

};

struct ProgramNode: public ASTNode {
	ProgramNode(ASTNode* name, ASTNode* block):
	ASTNode(Token::make_empty(), ASTNode::type::program),
	name(name),
	block(block) {}

	~ProgramNode() {
		delete name;
		delete block;
	}
	ASTNode* name = nullptr;
	ASTNode* block = nullptr;
};

struct NoOpNode: public ASTNode {
	NoOpNode(): ASTNode(Token::make_empty(), ASTNode::type::noop) {}
};
