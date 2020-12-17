#include "notesfile.hpp"
#include "configparser.hpp"
#include "constants.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstddef> // for std::size_t


// Inquires what to do from the user manually
void manualMode(ConfigParser &config, NotesFile &file) {
	std::cout << "ToDo manualMode()\n";
	std::cout << config.currentFile() << '\n';
	std::cout << file << '\n';
}

void processOption(const std::vector<std::string> &args, ConfigParser &config) {
	std::cout << "ToDo processOption\n";
	std::cout << config.currentFile() << '\n';
	for (const auto &arg : args)
		std::cout << arg << '\n';
}

// Process the user's request via the arguments
void automaticMode(int argc, char* argv[], ConfigParser &config, NotesFile &file) {
	// Preallocate the array with the size we need
	// it is argc - 1 because we don't care
	// for the first string of argv
	std::vector<std::string> usefulArgs;
	usefulArgs.resize(static_cast<std::size_t>(argc - 1));
	
	// Start processing the arguments from the second position of argv
	// because the first one is just how the program was launched
	for (std::size_t index{ 1 }; index < static_cast<std::size_t>(argc); ++index)
		usefulArgs[index - 1] = argv[index];

	//Check if the first argument is a option
	if (usefulArgs[0][0] == '-')
		processOption(usefulArgs, config);
	else {
		file.add(usefulArgs);
		file.save();

		std::cout << "Notes:\n";
		std::cout << file << '\n';
	}	
}

int main(int argc, char* argv[]) {
	ConfigParser config{};
	NotesFile currentFile{ config.currentFile() };

	// If user didn't pass any options, use manual mode and exit
	if (argc < 2)
		manualMode(config, currentFile);
	else
	// Otherwise, use the automatic mode
		automaticMode(argc, argv, config, currentFile);
	
	return 0;
}
