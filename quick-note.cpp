#include <iostream>
#include <string>
#include <vector>

void processArg(const std::string& arg) {
	std::cout << "Todo " << arg;
}

// Inquires what to do from the user manually
void manual_mode() {
	std::cout << "ToDo\n";
	std::exit(0);
}

// Process the user's request via the arguments
void automatic_mode(int argc, char* argv[]) {
	// Preallocate the array with the size we need
	// it is argc - 1 because we don't care
	// for the first string of argv
	std::vector<std::string> usefulArgs;
	usefulArgs.reserve(argc - 1);
	
	// Start processing the arguments from the second position of argv
	// because the first one is just how the program was launched
	for (std::size_t index{ 1 }; index < argc; ++index)
		usefulArgs[index - 1] = argv[index];

	for (const std::string& arg : usefulArgs) {
		processArg(arg);
	}
}

int main(int argc, char* argv[]) {
	// If user didn't pass any arguments, use manual mode and exit
	if (argc < 2)
		manual_mode();

	// Otherwise, use the automatic mode
	automatic_mode(argc, argv);
	
	return 0;
}
