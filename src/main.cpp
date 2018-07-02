
#include <Intepreter.hpp>
#include <iostream>
#include <string>


int main(int argc, char** argv) {
	try {
		if (argc != 2) {
			throw std::runtime_error("invalid argument args");
		}

		std::ifstream input(argv[1]);
		if (!input) {
			throw std::runtime_error("Failed to open source file");
		}

		Intepreter inter(input);
		inter.interpret();
	//		std::cout << "Calculated expr: " << inter.interpret() << std::endl;

		inter.print_global_scope();
		return 0;
	} catch (std::exception& err) {
		std::cout << err.what() << std::endl;
		return -1;
	}
}