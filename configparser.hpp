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
	static constexpr auto version{ "0.1" };
	std::fstream m_dataFile;
	std::vector<std::string> m_notefiles{};
	std::string m_filename{};
	std::string m_currentNoteFile{};

	void resetFile();
	void createDefault();
	void read();
	void save();
public:
	ConfigParser(const std::string &filename = Constants::defaultConfigFile);
	void addNoteFile(const std::string &notefile);
	std::vector<std::string>& getNoteFiles();
	const std::vector<std::string>& getNoteFiles() const;
	const std::string& currentFile() const;
	void useNoteFile(const std::string &name);
	
	
};

#endif 
