#include "notesfile.hpp"

NotesFile::NotesFile(const std::string &filename)
	: m_dataFile{ filename }, m_filename{ filename } {
	// Check if the file exists
	if (m_dataFile.is_open())
		read();
	else
		create();
}

void NotesFile::read() {
	std::cout << "TODO read()\n";
}

void NotesFile::create() {
	// Clears the buffer
	m_dataFile.clear();
	// Creates the file
	m_dataFile.open(m_filename, std::ios::out);
	m_dataFile << "0\n";
	m_dataFile.close();
	// Opens the created file in write and read mode
	m_dataFile.open(m_filename);
}

void NotesFile::save() {
	m_dataFile.seekp(0);
	// Save the number of notes
	m_dataFile << m_notes.size() << '\n';
	// Insert the notes into the file
	for (const auto note : m_notes)
		m_dataFile << note << '\n';
}

void NotesFile::add(const std::string &note) {
	m_notes.push_back(note);
}

std::ostream& operator<<(std::ostream &out, NotesFile &file) {
	for (const auto &note : file.m_notes)
		out << note << '\n';

	return out;
}

std::istream& operator>>(std::istream &in, NotesFile &file) {
	std::string note{};
	in >> note;
	file.add(note);

	return in;
}
