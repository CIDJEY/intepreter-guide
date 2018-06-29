
#include <Interpreter.hpp>
#include <stdexcept>
#include <set>

int Intepreter::visit_binop(BinOpNode* node) {
	if (node->t.get_type() == Token::type::plus) {
		return visit(node->left) + visit(node->right);
	} else if (node->t.get_type() == Token::type::minus) {
		return visit(node->left) - visit(node->right);
	} else if (node->t.get_type() == Token::type::multiplicate) {
		return visit(node->left) * visit(node->right);
	} else if (node->t.get_type() == Token::type::divide) {
		return visit(node->left) / visit(node->right);
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}

int Intepreter::visit_integer(IntegerNode* node) {
	if (node->t.get_type() == Token::type::integer) {
		return std::stoi(node->t.get_value());
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}

int Intepreter::visit_unop(UnOpNode* node) {
	if (node->t.get_type() == Token::type::plus) {
		return +visit(node->expr);
	} else if (node->t.get_type() == Token::type::minus) {
		return -visit(node->expr);
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}

int Intepreter::visit(ASTNode* node) {
	if (node->get_type() == ASTNode::type::binop) {
		return visit_binop((BinOpNode*)node);
	} else if (node->get_type() == ASTNode::type::unop) {
		return visit_unop((UnOpNode*)node);
	} else if (node->get_type() == ASTNode::type::integer) {
		return visit_integer((IntegerNode*)node);
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}
