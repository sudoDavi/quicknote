#include "notesfile.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstddef> // for std::size_t

void processArg(const std::string &arg) {
	NotesFile notes{ "test-notes" };
	notes.add(arg);
	notes.save();
	std::cout << notes;
}

// Inquires what to do from the user manually
void manualMode() {
	std::cout << "ToDo\n";
	std::exit(0);
}

// Process the user's request via the arguments
void automaticMode(int argc, char* argv[]) {
	// Preallocate the array with the size we need
	// it is argc - 1 because we don't care
	// for the first string of argv
	std::vector<std::string> usefulArgs;
	usefulArgs.resize(static_cast<std::size_t>(argc - 1));
	
	// Start processing the arguments from the second position of argv
	// because the first one is just how the program was launched
	for (std::size_t index{ 1 }; index < static_cast<std::size_t>(argc); ++index)
		usefulArgs[index - 1] = argv[index];

	for (const std::string& arg : usefulArgs) {
		processArg(arg);
	}
}

int main(int argc, char* argv[]) {
	// If user didn't pass any arguments, use manual mode and exit
	if (argc < 2)
		manualMode();

	// Otherwise, use the automatic mode
	automaticMode(argc, argv);
	
	return 0;
}
