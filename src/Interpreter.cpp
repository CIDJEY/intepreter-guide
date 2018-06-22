
#include <Interpreter.hpp>
#include <stdexcept>
#include <set>


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


std::string Intepreter::visit_rpn(ASTNode* node) {
	auto type = node->t.get_type();

	std::set<Token::type> binops = {
		Token::type::plus,
		Token::type::minus,
		Token::type::multiplicate,
		Token::type::divide
	};

	if (binops.find(node->t.get_type()) != binops.end()) {
		return visit_rpn(node->left) + " " + visit_rpn(node->right) + " " + node->t.get_value();
	} else if (node->t.get_type() == Token::type::integer) {
		return node->t.get_value();
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}

std::string Intepreter::visit_lisp(ASTNode* node) {
	auto type = node->t.get_type();

	std::set<Token::type> binops = {
		Token::type::plus,
		Token::type::minus,
		Token::type::multiplicate,
		Token::type::divide
	};

	std::string result = "";

	if (binops.find(node->t.get_type()) != binops.end()) {
		result += "(" + node->t.get_value() + " " + visit_lisp(node->left) + " " + visit_lisp(node->right) + ")";
	} else if (node->t.get_type() == Token::type::integer) {
		result = node->t.get_value();
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}

	return result;
}