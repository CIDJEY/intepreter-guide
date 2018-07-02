
#include <Intepreter.hpp>
#include <stdexcept>
#include <set>
#include <iostream>

void Intepreter::print_global_scope() {
	std::cout << "Printing global scope\n";
	for (auto& var: global_scope) {
		if (var.second.type() == typeid(double)) {
			std::cout << var.first << " : " << std::any_cast<double>(var.second) << std::endl;
		} else {
			std::cout << var.first << " : " << std::any_cast<int>(var.second) << std::endl;
		}

	}
}

template <typename t>
std::any do_visit_binop(BinOpNode* node, t left, t right) {
	if (node->t.get_type() == Token::type::plus) {
		return left + right;
	} else if (node->t.get_type() == Token::type::minus) {
		return left - right;
	} else if (node->t.get_type() == Token::type::multiplicate) {
		return left * right;
	} else if (node->t.get_type() == Token::type::integer_div) {
		return int(left) / int(right);
	} else if (node->t.get_type() == Token::type::real_div) {
		return double(left) / double(right);
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}

std::any Intepreter::visit_binop(BinOpNode* node) {

	std::any left = visit(node->left);
	std::any right = visit(node->right);

	if ((left.type() == typeid(double)) || (right.type() == typeid(double))) {
		double fleft, fright;
		if (left.type() == typeid(double)) {
			fleft = std::any_cast<double>(left);
		} else {
			fleft = (double) std::any_cast<int>(left);
		}
		if (right.type() == typeid(double)) {
			fright = std::any_cast<double>(right);
		} else {
			fright = (double) std::any_cast<int>(right);
		}
		return do_visit_binop(node, fleft, fright);
	} else {
		return do_visit_binop(node, std::any_cast<int>(left), std::any_cast<int>(right));
	}
}

std::any Intepreter::visit_number(NumberNode* node) {
	if (node->t.get_type() == Token::type::integer_const) {
		return std::stoi(node->t.get_value());
	} if (node->t.get_type() == Token::type::real_const) {
		return std::stod(node->t.get_value());
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}

template <typename t>
t do_visit_unop(UnOpNode* node, t expr) {
	if (node->t.get_type() == Token::type::plus) {
		return +expr;
	} else if (node->t.get_type() == Token::type::minus) {
		return -expr;
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}

std::any Intepreter::visit_unop(UnOpNode* node) {
	std::any expr = visit(node->expr);
	if (expr.type() == typeid(double)) {
		return do_visit_unop(node, std::any_cast<double>(expr));
	} else {
		return do_visit_unop(node, std::any_cast<int>(expr));
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

std::any Intepreter::visit_var(VarNode* node) {
	auto var_name = node->t.get_value();

	auto found = global_scope.find(var_name);
	if (found == global_scope.end()) {
		std::string error("unknown variable: ");
		error += var_name;
		throw std::runtime_error(error);
	}

	return found->second;
}

std::any Intepreter::visit_program(ProgramNode* node) {
	return visit(node->block);
}

std::any Intepreter::visit_block(BlockNode* node) {
	for (auto decl: node->declarations) {
		visit_declaration((VarDeclarationNode*)decl);
	}
	return visit(node->compound_statement);
}

std::any Intepreter::visit_declaration(VarDeclarationNode* node) {
	return 0;
}

std::any Intepreter::visit_type(TypeNode* node) {
	return 0;
}

std::any Intepreter::visit(ASTNode* node) {
	if (node->get_type() == ASTNode::type::binop) {
		return visit_binop((BinOpNode*)node);
	} else if (node->get_type() == ASTNode::type::unop) {
		return visit_unop((UnOpNode*)node);
	} else if (node->get_type() == ASTNode::type::number) {
		return visit_number((NumberNode*)node);
	} else if (node->get_type() == ASTNode::type::compound) {
		return visit_compound((CompoundNode*)node);
	} else if (node->get_type() == ASTNode::type::assign) {
		return visit_assign((AssignNode*)node);
	} else if (node->get_type() == ASTNode::type::var) {
		return visit_var((VarNode*)node);
	} else if (node->get_type() == ASTNode::type::program) {
		return visit_program((ProgramNode*)node);
	} else if (node->get_type() == ASTNode::type::block) {
		return visit_block((BlockNode*)node);
	} else if (node->get_type() == ASTNode::type::var_declaration) {
		return visit_declaration((VarDeclarationNode*)node);
	} else if (node->get_type() == ASTNode::type::var_type) {
		return visit_type((TypeNode*)node);
	} else if (node->get_type() == ASTNode::type::noop) {
		return visit_noop((NoOpNode*)node);
	} else {
		throw std::runtime_error(__PRETTY_FUNCTION__);
	}
}
