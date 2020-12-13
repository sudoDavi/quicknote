#ifndef NOTES_FILE_HPP
#define NOTES_FILE_HPP

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
public:
	NotesFile(const std::string &filename = "notes");
	// ~NotesFile();
	void add(const std::string &note);
	void save();

	friend std::ostream& operator<<(std::ostream &out, NotesFile &file);
	friend std::istream& operator>>(std::istream &in, NotesFile &file);
};

#endif 
