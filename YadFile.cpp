#include "YadFile.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/regex.hpp>
#include <boost/spirit/include/qi.hpp>

YadFile::YadFile(
        std::string source_code,
        std::vector<std::string> history)
    : _source_code(source_code),
      _history(history)
{

}
static std::string history_start("//=========History========//");

std::string YadFile::getSourceCode() const
{
    return _source_code;
}


std::vector<std::string> YadFile::getHistory() const
{
    return _history;
}

void YadFile::saveToFile(std::string file_name) const
{
    if(OUTPUT) std::cout << "Saved to file: " << file_name;

	std::ofstream file(file_name, std::ios::out );
	if (!file.is_open())
    {
        std::string error("Can't open file for writing.");
        throw std::runtime_error(error.c_str());
    }

	file << _source_code << std::endl << std::endl << std::endl;

    file << history_start << std::endl;
    for(int i=0; i<_history.size(); ++i)
    {
		file << "//" << _history[i] << std::endl;
    }
}
//TODO.  File can start with // or #
std::string rstrip(const std::string& str)
{
    int n = str.size() - 1;
    for (; n >= 0; --n) {
		if (!std::isspace(str.at(n))){
			return str.substr(str.size() - (n + 1 ), n + 1);
		}
    }
    return "";
}


YadFile YadFile::readFromFile(std::string file_name)
{
	if (OUTPUT)  std::cout << "Details from test file: " << file_name << std::endl;

	std::ifstream file(file_name, std::ios::in);

    if(!file.good())
    {
        std::string error("File does not exists.");
        throw std::runtime_error(error.c_str());
    }

    if (!file.is_open())
    {
        std::string error("Can't open file.");
        throw std::runtime_error(error.c_str());
    }

	std::stringstream scontent;
	scontent << file.rdbuf();
	std::string content = scontent.str();

    int history_mark = content.find(history_start);
    if(history_mark < 0)
    {
        std::string error("File is corrupted.");
        throw std::runtime_error(error.c_str());
    }

    std::string source = rstrip(content.substr(0,history_mark));
    std::string history_line = content.substr(history_mark+history_start.size());

    if(OUTPUT) std::cout << "Source: " << source << std::endl;
	if (OUTPUT) std::cout << "History: " << history_line << std::endl << std::endl;

    std::vector<std::string> history;

	std::vector<std::string> lines;
	boost::split(lines, history_line, boost::is_any_of("\r\n]"), boost::token_compress_on);
    for(int i=0; i<lines.size(); ++i)
    {
        std::string line = lines[i];
		boost::trim(line);
        if(line.size() > 2 && line.substr(0,2)=="//")
        {
            history.push_back(line.substr(2));
        }
    }

    return YadFile(source, history);
}
