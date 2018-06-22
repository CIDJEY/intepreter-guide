
#include <Interpreter.hpp>
#include <iostream>
#include <string>


int main(int argc, char** argv) {
	try {
		if (argc != 2) {
			throw std::runtime_error("invalid argument args");
		}
		std::string input = argv[1];
		std::cout << "Input: " << input << std::endl;
		Intepreter inter(input);
		std::cout << "Calculated expr: " << inter.interpret() << std::endl;
		std::cout << "RPN: " << inter.rpn() << std::endl;
		return 0;
	} catch (std::exception& err) {
		std::cout << err.what() << std::endl;
		return -1;
	}
}