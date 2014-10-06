#include "src/Machine.h"

int main(int argc, char **argv) {
	Machine machine("../maquina.json");
	
	machine.run("abab", true);
	return EXIT_SUCCESS;
}
