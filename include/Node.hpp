
#pragma once

#include <Token.hpp>

struct ASTNode {
	ASTNode(ASTNode* left, Token t, ASTNode* right):
		left(left), t(t), right(right) {}

	~ASTNode() {
		delete left;
		delete right;
	}

	static ASTNode* make_integer_node(Token t) {
		return new ASTNode(nullptr, t, nullptr);
	}

	static ASTNode* make_binop_node(ASTNode* left, Token t, ASTNode* right) {
		return new ASTNode(left, t, right);
	}

	ASTNode* left = nullptr;
	ASTNode* right = nullptr;
	Token t;
};
