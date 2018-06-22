
#pragma once

#include <Token.hpp>

struct ASTNode {
	enum type {
		binop,
		unop,
		integer
	};

	ASTNode(ASTNode* left, Token t, ASTNode* right, type type):
		left(left), t(t), right(right), _type(type) {}

	~ASTNode() {
		delete left;
		delete right;
	}

	static ASTNode* make_binop(ASTNode* left, Token t, ASTNode* right) {
		return new ASTNode(left, t, right, type::binop);
	}

	static ASTNode* make_unop(ASTNode* expr, Token t) {
		return new ASTNode(expr, t, nullptr, type::unop);
	}

	static ASTNode* make_integer(Token t) {
		return new ASTNode(nullptr, t, nullptr, type::integer);
	}

	type get_type() {
		return _type;
	}

	ASTNode* left = nullptr;
	ASTNode* right = nullptr;
	Token t;
	type _type;
};
