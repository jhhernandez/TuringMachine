#include "src/Machine.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	if (argc < 3) {
		cout << "Usage: turingmachine <description> <content>" << endl;
		return EXIT_SUCCESS;
	}
	Machine machine(argv[1]);
	
	machine.run(argv[2], true);
	return EXIT_SUCCESS;
}
