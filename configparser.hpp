#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include "constants.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstddef> // std::size_t
#include <algorithm>

class ConfigParser {
private:
	static constexpr auto version{ Constants::ConfigFileVersion };
	std::fstream m_dataFile;
	std::vector<std::string> m_notefiles{};
	std::string m_filename{};
	std::string m_currentNoteFile{};

	void resetFile();
	void createDefault();
	void read();
	void save();
public:
	static constexpr auto DefaultNoteFile{ Constants::DefaultNoteFile };
	ConfigParser(const std::string &filename = Constants::DefaultConfigFile);
	void addNoteFile(const std::string &notefile);
	void addNoteFile(const std::vector<std::string>::const_iterator &begin, const std::vector<std::string>::const_iterator &end);
	std::vector<std::string>& getNoteFiles();
	const std::vector<std::string>& getNoteFiles() const;
	const std::string& currentFile() const;
	void useNoteFile(const std::string &name);
	void useNoteFile(const std::vector<std::string>::const_iterator &begin, const std::vector<std::string>::const_iterator &end);
	
	
};

#endif 
