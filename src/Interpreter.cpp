
#include <Interpreter.hpp>
#include <stdexcept>


int Intepreter::visit(ASTNode* node) {
	if (node->t.get_type() == Token::type::plus) {
		return visit(node->left) + visit(node->right);
	} else if (node->t.get_type() == Token::type::minus) {
		return visit(node->left) - visit(node->right);
	} else if (node->t.get_type() == Token::type::multiplicate) {
		return visit(node->left) * visit(node->right);
	} else if (node->t.get_type() == Token::type::divide) {
		return visit(node->left) / visit(node->right);
	} else if (node->t.get_type() == Token::type::integer) {
		return std::stoi(node->t.get_value());
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}