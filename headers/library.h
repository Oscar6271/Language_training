#pragma once

#include <string>
#include <vector>

std::string to_lower(std::string const& word);

void clean_string(std::string & s);

void trim_white_space(std::string & phrase, std::string & translation);

void clear_terminal(bool clear);

bool end_of_file(size_t pos, int seperator, size_t max_seperator);