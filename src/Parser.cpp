
#include <Parser.hpp>
#include <stdexcept>

void Parser::eat(const Token::type _type) {
	if (current_token.get_type() == _type) {
		current_token = lexer.get_next_token();
	} else {
		throw std::runtime_error("Error while eating");
	}
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
		throw std::runtime_error(__PRETTY_FUNCTION__);
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