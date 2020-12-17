#include "notesfile.hpp"

NotesFile::NotesFile(const std::string &filename)
	: m_dataFile{ filename }, m_filename{ filename } {
	// Check if the file exists
	if (m_dataFile.is_open())
		read();
	else
		create();
}

// Clears error state flags and also moves the extractor to the start
void NotesFile::resetFile() {
	m_dataFile.clear();
	m_dataFile.seekg(0);
}

void NotesFile::read() {
	resetFile();
	// Get information about the number of notes
	std::string numberOfNotes{};
	m_dataFile >> numberOfNotes;
	m_notes.resize(std::stoul(numberOfNotes));

	// Skip the first line
	m_dataFile.ignore(32767, '\n');

	// Read the notes and add them
	for (std::size_t index{ 0 }; index < m_notes.size(); ++index) {
		std::string note{};
		std::getline(m_dataFile, note);
		m_notes[index] = note;
	}
}

void NotesFile::open(const std::string &filename) {
	std::cout << "TODO open()\n";
	std::cout << filename << '\n';
}

void NotesFile::create() {
	resetFile();

	// Creates the default file
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

void NotesFile::add(const std::vector<std::string> &note) {
	std::string wholeNote{};
	for (const auto &snippet : note)
		wholeNote.append(snippet + ' ');

	m_notes.push_back(wholeNote);
}

std::ostream& operator<<(std::ostream &out, NotesFile &file) {
	for (const auto &note : file.m_notes)
		out << note << '\n';

	return out;
}

std::istream& operator>>(std::istream &in, NotesFile &file) {
	std::string note{};
	std::getline(in, note);
	file.add(note);

	return in;
}
