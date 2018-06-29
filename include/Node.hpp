
#pragma once

#include <Token.hpp>

struct ASTNode {
	enum type {
		binop,
		unop,
		integer
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

struct IntegerNode: public ASTNode {
	IntegerNode(Token t): ASTNode(t, ASTNode::type::integer) {}
};
