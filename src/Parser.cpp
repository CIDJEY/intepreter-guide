
#include <Parser.hpp>
#include <stdexcept>

void Parser::eat(const Token::type _type) {
	if (current_token.get_type() == _type) {
		current_token = lexer.get_next_token();
	} else {
		throw std::runtime_error("Error while eating");
	}
}

ASTNode* Parser::parse() {
	ASTNode* result = program();
	if (current_token.get_type() != Token::type::eof) {
		throw std::runtime_error("Something after DOT");
	}

	return result;
}

ASTNode* Parser::program() {
	ASTNode* result = compound_statement();
	eat(Token::type::dot);
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
	if (t.get_type() == Token::type::integer) {
		eat(Token::type::integer);
		result = (ASTNode*) (new IntegerNode(t));
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
		(current_token.get_type() == Token::type::divide))
	{
		Token t = current_token;
		if (t.get_type() == Token::type::multiplicate) {
			eat(Token::type::multiplicate);
		} else if (t.get_type() == Token::type::divide) {
			eat(Token::type::divide);
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