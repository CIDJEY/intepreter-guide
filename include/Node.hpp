
#pragma once

#include <Token.hpp>
#include <vector>

struct ASTNode {
	enum type {
		binop,
		unop,
		integer,
		compound,
		assign,
		var,
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

struct IntegerNode: public ASTNode {
	IntegerNode(Token t): ASTNode(t, ASTNode::type::integer) {}
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

struct VarNode: public ASTNode {
	VarNode(Token t): ASTNode(t, ASTNode::type::var) {}
};

struct NoOpNode: public ASTNode {
	NoOpNode(): ASTNode(Token::make_empty(), ASTNode::type::noop) {}
};
