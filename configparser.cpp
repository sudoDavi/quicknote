#include "configparser.hpp"

ConfigParser::ConfigParser(const std::string &filename)
	: m_dataFile{ filename }, m_filename{ filename } {
	// Check if the file exists
	if (m_dataFile.is_open())
		read();
	else
		createDefault();
}

// Resets the file stream to the start of the file
// and also cleans any error state flags
void ConfigParser::resetFile() {
	m_dataFile.clear();
	m_dataFile.seekg(0);
}

void ConfigParser::read() {
	resetFile();

	// First line of the config file tells the version
	// of the config file and the number of note files
	// aswell as the current notefile selected
	std::string configVersion{};
	m_dataFile >> configVersion;

	if (configVersion != version) {
		std::cout << "THIS IS TEMPORARY\nERROR: CONFIG FILE VERSION MISMATCH\n";
		std::exit(1);
	}

	std::string numberOfNoteFiles{};
	m_dataFile >> numberOfNoteFiles;

	m_dataFile >> m_currentNoteFile;

	// Skip to the next line
	m_dataFile.ignore(32767, '\n');

	m_notefiles.resize(std::stoul(numberOfNoteFiles));

	for (auto index{ 0 }; static_cast<std::size_t>(index) < m_notefiles.size(); ++index) {
		std::string line{};
		if (!m_dataFile.eof())
			std::getline(m_dataFile, line);
		else
			break;

		m_notefiles[static_cast<std::size_t>(index)] = line;
	}
}


void ConfigParser::createDefault() {
	// Creates the file
	m_dataFile.open(m_filename, std::ios::out);

	// Saves the file with default parameters
	m_currentNoteFile = Constants::DefaultNoteFile;
	m_notefiles.push_back(m_currentNoteFile);
	save();

	m_dataFile.close();
	
	// Opens the created file in write and read mode
	m_dataFile.open(m_filename);

}

// Serializes and save the in memory config file
void ConfigParser::save() {
	resetFile();

	// This saves the in memory config to a file
	m_dataFile << version << ' ' << m_notefiles.size()
		<< ' ' << m_currentNoteFile << '\n';
	// This adds the name of the notefiles to the file
	for (const auto &notefile : m_notefiles)
		m_dataFile << notefile << '\n';
}

// Adds a new notefile to the in memory config
void ConfigParser::addNoteFile(const std::string &notefile) {
	m_notefiles.push_back(notefile);
	save();
}

void ConfigParser::addNoteFile(const std::vector<std::string>::const_iterator &begin, const std::vector<std::string>::const_iterator &end) {
	std::string wholeFileName{};
	for (auto currentIt{begin}; currentIt < end; ++currentIt)
		wholeFileName.append(*currentIt + ' ');

	m_notefiles.push_back(wholeFileName);
	save();
}

std::vector<std::string>& ConfigParser::getNoteFiles() {
	return m_notefiles;
}

const std::vector<std::string>& ConfigParser::getNoteFiles() const{
	return m_notefiles;
}

const std::string& ConfigParser::currentFile() const {
	return m_currentNoteFile;
}

void ConfigParser::useNoteFile(const std::string &name) {
	m_currentNoteFile = name;
	save();
}

void ConfigParser::useNoteFile(const std::vector<std::string>::const_iterator &begin, const std::vector<std::string>::const_iterator &end) {
	std::string wholeFileName{};
	for (auto currentIt{begin}; currentIt < end; ++currentIt)
		wholeFileName.append(*currentIt + ' ');

	// To remove the tralling space
	wholeFileName.pop_back();

	m_currentNoteFile = wholeFileName;
	save();
}
