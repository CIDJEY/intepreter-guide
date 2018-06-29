
#include <Interpreter.hpp>
#include <stdexcept>
#include <set>
#include <iostream>

void Intepreter::print_global_scope() {
	std::cout << "Printing global scope\n";
	for (auto& var: global_scope) {
		std::cout << var.first << " : " << var.second << std::endl;
	}
}

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

int Intepreter::visit_compound(CompoundNode* node) {
	for (auto node: node->children) {
		visit(node);
	}

	return 0;
}

int Intepreter::visit_assign(AssignNode* node) {
	auto var_name = node->var->t.get_value();
	global_scope[var_name] = visit(node->expr);
	return 0;
}

int Intepreter::visit_var(VarNode* node) {
	auto var_name = node->t.get_value();

	auto found = global_scope.find(var_name);
	if (found == global_scope.end()) {
		throw std::runtime_error("Undunsigned variable");
	}

	return found->second;
}


int Intepreter::visit(ASTNode* node) {
	if (node->get_type() == ASTNode::type::binop) {
		return visit_binop((BinOpNode*)node);
	} else if (node->get_type() == ASTNode::type::unop) {
		return visit_unop((UnOpNode*)node);
	} else if (node->get_type() == ASTNode::type::integer) {
		return visit_integer((IntegerNode*)node);
	} else if (node->get_type() == ASTNode::type::compound) {
		return visit_compound((CompoundNode*)node);
	} else if (node->get_type() == ASTNode::type::assign) {
		return visit_assign((AssignNode*)node);
	} else if (node->get_type() == ASTNode::type::var) {
		return visit_var((VarNode*)node);
	} else if (node->get_type() == ASTNode::type::noop) {
		return visit_noop((NoOpNode*)node);
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}
