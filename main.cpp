#include "src/Machine.h"

#include <iostream>

using namespace std;

int main(int argc, const char **argv) {
	if (argc != 3) {
		cout << "Usage: turingmachine <description> <content>" << endl;
		return EXIT_SUCCESS;
	}
	Machine machine(argv[1]);
	
	if (machine.run(argv[2], false))
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}
