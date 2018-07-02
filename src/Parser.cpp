
#include <Parser.hpp>
#include <stdexcept>

void Parser::eat(const Token::type _type) {
	if (current_token.get_type() == _type) {
		current_token = lexer.get_next_token();
	} else {
		std::string error("Error while eating, current token: ");
		error += current_token.get_type();
		throw std::runtime_error(error);
	}
}

ASTNode* Parser::parse() {
	ASTNode* result = program();
	if (current_token.get_type() != Token::type::eof) {
		throw std::runtime_error("Something after DOT");
	}

	return result;
}

ASTNode* Parser::compound_statement() {
	CompoundNode* result = new CompoundNode();
	eat(Token::type::begin);
	result->children = statement_list();
	eat(Token::type::end);

	return (ASTNode*)result;
}

std::vector<ASTNode*> Parser::statement_list() {
	std::vector<ASTNode*> result;

	result.push_back(statement());

	while (current_token.get_type() == Token::type::semi) {
		eat(Token::type::semi);
		result.push_back(statement());
	}

	if (current_token.get_type() == Token::type::id) {
		throw std::runtime_error("Last statement must be with a semi");
	}

	return result;
}

ASTNode* Parser::statement() {
	ASTNode* result = nullptr;

	if (current_token.get_type() == Token::type::begin) {
		result = compound_statement();
	} else if (current_token.get_type() == Token::type::id) {
		result = assignment_statement();
	} else {
		result = empty();
	}

	return result;
}

ASTNode* Parser::assignment_statement() {
	ASTNode* result = nullptr;
	ASTNode* left = variable();
	eat(Token::type::assign);
	ASTNode* right = expr();
	result = (ASTNode*)(new AssignNode(left, right));
	return result;
}

ASTNode* Parser::variable() {
	ASTNode* result = (ASTNode*)(new VarNode(current_token));
	eat(Token::type::id);
	return result;
}

ASTNode* Parser::empty() {
	return (ASTNode*)(new NoOpNode());
}

ASTNode* Parser::term() {
	ASTNode* result = nullptr;
	Token t = current_token;
	if (t.get_type() == Token::type::integer_const) {
		eat(Token::type::integer_const);
		result = (ASTNode*) (new NumberNode(t));
	} else if (t.get_type() == Token::type::real_const) {
		eat(Token::type::real_const);
		result = (ASTNode*) (new NumberNode(t));
	} else if (t.get_type() == Token::type::lparen) {
		eat(Token::type::lparen);
		result = expr();
		eat(Token::type::rparen);
	} else if (t.get_type() == Token::type::plus) {
		eat(Token::type::plus);
		result = (ASTNode*) (new UnOpNode(t, term()));
	} else if (t.get_type() == Token::type::minus) {
		eat(Token::type::minus);
		result = (ASTNode*) (new UnOpNode(t, term()));
	} else {
		result = variable();
	}
	return result;
}

ASTNode* Parser::factor() {
	ASTNode* result = term();
	while((current_token.get_type() == Token::type::multiplicate) ||
		(current_token.get_type() == Token::type::integer_div) ||
		(current_token.get_type() == Token::type::real_div))
	{
		Token t = current_token;
		if (t.get_type() == Token::type::multiplicate) {
			eat(Token::type::multiplicate);
		} else if (t.get_type() == Token::type::integer_div) {
			eat(Token::type::integer_div);
		} else if (t.get_type() == Token::type::real_div) {
			eat(Token::type::real_div);
		} else {
			throw std::runtime_error("Error in term");
		}

		result = (ASTNode*) (new BinOpNode(t, result, term()));
	}

	return result;
}

ASTNode* Parser::expr() {
	ASTNode* result = factor();
	while((current_token.get_type() == Token::type::plus) ||
		(current_token.get_type() == Token::type::minus))
	{
		Token t = current_token;
		if (t.get_type() == Token::type::plus) {
			eat(Token::type::plus);
		} else if (t.get_type() == Token::type::minus) {
			eat(Token::type::minus);
		} else {
			throw std::runtime_error("Error in term");
		}
		result = (ASTNode*) (new BinOpNode(t, result, factor()));
	}

	return result;
}

ASTNode* Parser::type_spec() {
	Token t = current_token;
	if (current_token.get_type() == Token::type::integer) {
		eat(Token::type::integer);
	} else if (current_token.get_type() == Token::type::real) {
		eat(Token::type::real);
	} else {
		throw std::runtime_error("Expected type specification");
	}

	return (ASTNode*) (new TypeNode(t));
}

std::vector<ASTNode*> Parser::variable_declarations() {
	std::vector<VarDeclarationNode*> vars;
	std::vector<ASTNode*> result;
	ASTNode* type = nullptr;

	vars.push_back((VarDeclarationNode*)variable());

	while (current_token.get_type() == Token::type::comma) {
		eat(Token::type::comma);
		result.push_back((VarDeclarationNode*)variable());
	}

	eat(Token::type::colon);

	type = type_spec();

	for (auto var: vars) {
		var->type = type;
		result.push_back((ASTNode*)var);
	}

	return result;
}

std::vector<ASTNode*> Parser::declarations() {
	std::vector<ASTNode*> result;

	if (current_token.get_type() == Token::type::var) {
		eat(Token::type::var);
		while (current_token.get_type() == Token::type::id) {
			auto new_declarations = variable_declarations();
			result.insert(result.end(), new_declarations.begin(), new_declarations.end());
			eat(Token::type::semi);
		}
	}

	return result;
}

ASTNode* Parser::block() {
	return (ASTNode*) new BlockNode(declarations(), compound_statement());
}

ASTNode* Parser::program() {
	eat(Token::type::program);
	ASTNode* name = variable();
	eat(Token::type::semi);
	ASTNode* block_node = block();
	eat(Token::type::dot);
	return (ASTNode*) (new ProgramNode(name, block_node));

}
