#include "notesfile.hpp"
#include "configparser.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm>


// Inquires what to do from the user manually
void manualMode(ConfigParser &config, NotesFile &file) {
	std::cout << "ToDo manualMode()\n";
	std::cout << config.currentFile() << '\n';
	std::cout << file << '\n';
}

void processOption(std::vector<std::string> &args, ConfigParser &config, NotesFile &file) {
	auto findOptions { [](const std::string &arg) -> bool {
		return (arg[0] == '-');
	}};

	auto numberOfOptions{ std::count_if(args.begin(), args.end(), findOptions) };

	auto currentOption{ std::find_if(args.begin(), args.end(), findOptions) };

	while (numberOfOptions) {
		auto nextOption{ std::find_if(currentOption + 1, args.end(), findOptions) };

		// Current Method for parsing and processing the options
		// if more options are added this should move to a separate function
		if (*currentOption == "-n") {
			file.save();
			config.addNoteFile(currentOption + 1, nextOption);
			config.useNoteFile(currentOption + 1, nextOption);
			file.open(currentOption + 1, nextOption);
		}
		else if (*currentOption == "-a") {
			file.open(config.currentFile());
			file.add(currentOption + 1, nextOption);
			file.save();
		}
		else if (*currentOption == "-u") {
			config.useNoteFile(currentOption + 1, nextOption);
		}
		else if (*currentOption == "-ud") {
			config.useNoteFile(ConfigParser::DefaultNoteFile);
		}
		else if (*currentOption == "-r") {
			file.open(config.currentFile());
			std::cout << "Notes in " + config.currentFile() + " :\n";
			std::cout << file;
		}
		currentOption = nextOption;
		--numberOfOptions;
	}
}

// Default action for the program in automatic mode
void defaultAction(const std::vector<std::string>& args, NotesFile &file) {
	file.add(args.begin() + 1, args.end());
	file.save();
}

// Process the user's request via the arguments
void automaticMode(int argc, char* argv[], ConfigParser &config, NotesFile &file) {
	// Preallocate the vector with the size we need
	std::vector<std::string> argVec(static_cast<std::size_t>(argc));
	
	// Convert the cstring array into a std::string vector
	for (auto index{ 0 }; index < argc; ++index)
		argVec[static_cast<std::size_t>(index)] = argv[index];

	// Lambda for checking if a string is a option
	auto findOptions { [](const std::string &arg) -> bool {
		return (arg[0] == '-');
	}};
	
	if (std::find_if(argVec.begin(), argVec.end(), findOptions) != argVec.end())
		processOption(argVec, config, file);
	else
		defaultAction(argVec, file);
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
