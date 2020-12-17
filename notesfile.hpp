#ifndef NOTES_FILE_HPP
#define NOTES_FILE_HPP

#include "constants.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class NotesFile {
private:
	std::fstream m_dataFile;
	std::vector<std::string> m_notes{};
	std::string m_filename{};

	void read();
	void create();
	void resetFile();
public:
	NotesFile(const std::string &filename = Constants::defaultNoteFile);
	void add(const std::string &note);
	void add(const std::vector<std::string> &note);
	// NOT IMPLEMENTED
	void open(const std::string &filename);
	void save();

	// Print all the notes in the file to std::cout
	friend std::ostream& operator<<(std::ostream &out, NotesFile &file);
	// Add a note from std::cin
	friend std::istream& operator>>(std::istream &in, NotesFile &file);
};

#endif 
