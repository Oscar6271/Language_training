#pragma once

#include <string>
#include <vector>
#include <utility>

std::pair<std::string, std::string> readfile(std::string const& fileName,
    std::string const& folder, bool write_in_swedish, std::vector<std::string> & phrases,
    std::vector<std::string> & translations);

std::string match_any(std::string const& command);

std::pair<std::string, std::string> initialize(int argc, char* argv[],
    std::vector<std::string> & phrases, std::vector<std::string> & translation,
    bool clear);

void printfile(std::vector<std::string> const& phrases,
    std::vector<std::string> const& translation);

void checkCommands(std::string & fileName, bool & write_in_swedish, bool & printfile,
    std::string const& folder);